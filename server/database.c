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

#include "database.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"


bool database_connect(struct database *db, const char *ip, const char *user, const char *passwd, const char *base)
{
	db->base = mysql_init(NULL);

    mysql_options(db->base, MYSQL_SET_CHARSET_NAME, "utf8");
    db->base = mysql_real_connect(db->base, ip, user, passwd, base, 3306, NULL, 0);
    if (db->base == NULL)
    	return false;
    return true;
}

bool database_check_user(struct database *db, unsigned id, const char *key)
{
	int ret_val;
    size_t count;
    char num[20];
    char query[255];
    MYSQL_RES *result;

    strcpy(query, "SELECT * FROM keys WHERE user=");

    sprintf(num, "%u", id);
    strcat(query, num);

    strcat(query, " AND key=\"");
    strcat(query, key);
    strcat(query, "\"");

    ret_val = mysql_query(db->base, query);
    if (ret_val != 0)
        return false;

    result = mysql_store_result(db->base);
    count = mysql_num_rows(result);

    if (count != 0) {
        mysql_free_result(result);
        return true;
    }
	return false;
}

bool database_add_meteo(struct database *db, unsigned id, float temp, float hum)
{
	int ret_val;
	char num[20];
	char query[512];
	char dtime[DATETIME_SIZE];

	date_time_now(dtime);
	sprintf(num, "%u", id);

	strcpy(query, "INSERT INTO meteo(user, temp, hum, time) VALUES (\"");
	strcat(query, num);
	strcat(query, "\", ");

	sprintf(num, "%.2f", temp);
	strcat(query, num);
	strcat(query, ", ");

	sprintf(num, "%.2f", hum);
	strcat(query, num);
	strcat(query, ", \"");
	strcat(query, dtime);
	strcat(query, "\")");

	ret_val = mysql_query(db->base, query);
	if (ret_val != 0)
		return false;
	return true;
}

void database_close(struct database *db)
{
	mysql_close(db->base);
}