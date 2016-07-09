/* Meteo-zone 2 project
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "configs.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>


static struct {
    struct server_cfg sc;
    struct database_cfg dbc;
} cfg;


static bool get_string_value(json_t *root, json_t *object, const char *value, char *out_str, unsigned size)
{
	json_t *jsobj;

	jsobj = json_object_get(object, value);
    if (jsobj == NULL) {
        json_decref(jsobj);
        json_decref(object);
        json_decref(root);
        return false;
    }
    strncpy(out_str, json_string_value(jsobj), size);
    json_decref(jsobj);
    return true;
}

static bool get_integer_value(json_t *root, json_t *object, const char *value, int *out_val)
{
	json_t *jsobj;

	jsobj = json_object_get(object, value);
    if (jsobj == NULL) {
        json_decref(jsobj);
        json_decref(object);
        json_decref(root);
        return false;
    }
    *out_val = json_integer_value(jsobj);
    json_decref(jsobj);
    return true;
}

bool configs_load(const char *filename)
{
    json_t *root;
    json_t *jdata;

    root = json_load_file(filename, 0, NULL);
    if (root == NULL) 
        return false;

    /*
     * Server cfg
     */
    jdata = json_object_get(root, "Server");
    if (jdata == NULL) {
        json_decref(root);
        return false;
    }
    if (!get_integer_value(root, jdata, "Port", (int *)&cfg.sc.port))
    	return false;
    if (!get_integer_value(root, jdata, "MaxUsers", (int *)&cfg.sc.max_users))
    	return false;
    json_decref(jdata);

    /*
     * Database cfg
     */
    jdata = json_object_get(root, "Database");
    if (jdata == NULL) {
        json_decref(root);
        return false;
    }
    if (!get_string_value(root, jdata, "Ip", cfg.dbc.ip, 15))
    	return false;
    if (!get_string_value(root, jdata, "User", cfg.dbc.user, 19))
    	return false;
    if (!get_string_value(root, jdata, "Passwd", cfg.dbc.passwd, 19))
    	return false;
    if (!get_string_value(root, jdata, "Base", cfg.dbc.base, 19))
    	return false;
    json_decref(jdata);

    json_decref(root);
    return true;
}

struct server_cfg *configs_get_server()
{
    return &cfg.sc;
}

struct database_cfg *configs_get_database()
{
    return &cfg.dbc;
}