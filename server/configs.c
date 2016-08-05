/* Meteo-zone 2 project
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "configs.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


enum {
	POS_COMMENT = -2,
	POS_NOT_FOUND = -1
};

static struct {
    struct server_cfg sc;
    struct database_cfg dbc;
} cfg;


/*
 * Local funcs
 */
static int pos(const char *str, const char symb)
{
    int p = 0;

    while (*str) {
        /*
         * Line is comment
         */
        if (*str == '#')
            return POS_COMMENT;

        if (*str == symb)
            return p;
        str++;
        p++;
    }
    return POS_NOT_FOUND;
}

static bool parse_string(const char *str, char *out, size_t sz)
{
	int p;
    bool is_num = false;
    bool found = false;
    size_t len = 0;

    p = pos(str, '\"');
    if (p == POS_COMMENT)
        return false;
    if (p == POS_NOT_FOUND) {
        p = pos(str, '=');
        if (p == POS_NOT_FOUND)
            return false;
        is_num = true;
    }
    str += p + 1;

    while (*str) {
        if (*str == ' ' && !found) {
            str++;
            continue;
        }
        if (*str == '\"')
            break;
        if (len > sz)
            return false;

        found = true;
        *out = *str;
        out++;
        str++;
        len++;
    }
    if (is_num)
        *out = '\0';
    else
        *out = '\0';
    return true;
}

static bool parse_unsigned(const char *str, unsigned *out)
{
    char outs[50];

    if (!parse_string(str, outs, 50))
        return false;

    sscanf(outs, "%u", out); 
    return true;
}

static bool configs_read_string(FILE *restrict file, char *out, size_t sz)
{
    bool is_ok = false;
    char data[255];

    while (!feof(file)) {
        if (fgets(data, 255, file) == NULL)
            return false;
        if (parse_string(data, out, sz))
            return true;
    }
    if (!is_ok)
        return false;
    return true;
}

static bool configs_read_unsigned(FILE *restrict file, unsigned *out)
{
    bool is_ok = false;
    char data[50];

    while (!feof(file)) {
        if (fgets(data, 50, file) == NULL)
            return false;
        if (parse_unsigned(data, out))
            return true;
    }

    if (!is_ok)
        return false;
    return true;
}

/*
 * Loading configs from file
 */
uint8_t configs_load(const char *filename)
{
    FILE *file;

    file = fopen(filename, "r");
    if (file == NULL)
        return CFG_FILE_NOT_FOUND;

    if (!configs_read_unsigned(file, &cfg.sc.port)) {
        fclose(file);
        return CFG_SC_PORT_ERR;
    }
    if (!configs_read_unsigned(file, &cfg.sc.max_users)) {
        fclose(file);
        return CFG_SC_MAX_ERR;
    }
    if (!configs_read_string(file, cfg.dbc.ip, 15)) {
        fclose(file);
        return CFG_DB_IP_ERR;
    }
    if (!configs_read_string(file, cfg.dbc.user, 19)) {
        fclose(file);
        return CFG_DB_USER_ERR;
    }
    if (!configs_read_string(file, cfg.dbc.passwd, 19)) {
        fclose(file);
        return CFG_DB_PASSWD_ERR;
    }
    if (!configs_read_string(file, cfg.dbc.base, 19)) {
        fclose(file);
        return CFG_DB_BASE_ERR;
    }
    fclose(file);
    return CFG_OK;
}

struct server_cfg *configs_get_server(void)
{
    return &cfg.sc;
}

struct database_cfg *configs_get_database(void)
{
    return &cfg.dbc;
}