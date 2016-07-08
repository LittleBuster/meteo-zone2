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


bool configs_load(const char *filename)
{
    json_t *root;
    json_t *jdata;
    json_t *jsobj;

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
    jsobj = json_object_get(jdata, "Port");
    if (jsobj == NULL) {        
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    cfg.sc.port = json_integer_value(jsobj);
    json_decref(jsobj);
    json_decref(jdata);

    /*
     * Database cfg
     */
    jdata = json_object_get(root, "Database");
    if (jdata == NULL) {
        json_decref(root);
        return false;
    }
    jsobj = json_object_get(jdata, "Ip");
    if (jsobj == NULL) {        
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    strcpy(cfg.dbc.ip, json_string_value(jsobj));
    json_decref(jsobj);
    json_decref(jdata);

    jsobj = json_object_get(jdata, "User");
    if (jsobj == NULL) {        
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    cfg.sc.port = json_integer_value(jsobj);
    json_decref(jsobj);
    json_decref(jdata);

    jsobj = json_object_get(jdata, "Passwd");
    if (jsobj == NULL) {        
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    cfg.sc.port = json_integer_value(jsobj);
    json_decref(jsobj);
    json_decref(jdata);

    jsobj = json_object_get(jdata, "Base");
    if (jsobj == NULL) {        
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    cfg.sc.port = json_integer_value(jsobj);
    json_decref(jsobj);
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