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


/*static struct {
} cfg = {
};*/

bool json_configs_load(const char *filename)
{
    json_t *root;

    root = json_load_file(filename, 0, NULL);
    if (root == NULL) {
        puts("Fail reading configs file.");
        return -1;
    }
    json_t *jdata = json_object_get(root, "Server");
    if (jdata == NULL) {
        json_decref(root);
        return -1;
    }
    json_t *jsobj = json_object_get(jdata, "Ip");
    if (jsobj != NULL) {
        puts(json_string_value(jsobj));
        json_decref(jsobj);
    }
    jsobj = json_object_get(jdata, "Port");
    if (jsobj != NULL) {
        puts(json_string_value(jsobj));
        json_decref(jsobj);
    }
    json_decref(jdata);

    json_decref(root);
    return true;
}