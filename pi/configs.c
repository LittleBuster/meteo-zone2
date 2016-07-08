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
    struct checker_cfg cc;
    struct server_cfg sc;
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
     * Checker timer cfg
     */
    jdata = json_object_get(root, "Checker");
    if (jdata == NULL) {
        json_decref(root);
        return false;
    }
    jsobj = json_object_get(jdata, "Interval");
    if (jsobj == NULL) {
        json_decref(jsobj);
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    cfg.cc.interval = json_integer_value(jsobj);
    json_decref(jsobj);
    json_decref(jdata);

    /*
     * Server cfg
     */
    jdata = json_object_get(root, "Server");
    if (jdata == NULL) {
        json_decref(root);
        return false;
    }
    jsobj = json_object_get(jdata, "Ip");
    if (jsobj == NULL) {        
        json_decref(jdata);
        json_decref(root);
        return false;
    }
    strcpy(cfg.sc.ip, json_string_value(jsobj));
    json_decref(jsobj);

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

    json_decref(root);
    return true;
}

struct checker_cfg *configs_get_checker()
{
    return &cfg.cc;
}

struct server_cfg *configs_get_server()
{
    return &cfg.sc;
}