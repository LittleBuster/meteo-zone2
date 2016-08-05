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
	return true;
}

bool database_add_meteo(struct database *db, unsigned id, float temp, float hum)
{
	int ret_val;
	char query[512];

	strcpy(query, "INSERT INTO meteo(id_usr, temp, hum, time) VALUES (\"");

	ret_val = mysql_query(db->base, query);
	if (ret_val != 0)
		return false;
	return true;
}

void database_close(struct database *db)
{
	mysql_close(db->base);
}