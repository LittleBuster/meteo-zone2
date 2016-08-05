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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <mysql/mysql.h>
#include <stdbool.h>


struct database {
	MYSQL *base;
};


/**
 * Connecting to database
 * @db: database pointer
 * @ip: ip address of database
 * @user: database username
 * @passwd: password of user
 * @base: database name
 *
 * returns false: if fail connection
 * returns true: if connection ok
 */
bool database_connect(struct database *db, const char *ip, const char *user, const char *passwd, const char *base);

/**
 * Checking new user id and key
 * @db: database pointer
 * @id: id of device
 * @key: authentication key of client
 *
 * returns false: if bad user id or key
 * returns true: if authentication ok
 */
bool database_check_user(struct database *db, unsigned id, const char *key);

/**
 * Adding new meteo data in base
 * @db: database pointer
 * @id: id of device
 * @temp: inside temperature
 * @hum: inside humidity
 *
 * returns false: if fail adding to base
 * returns true: if adding ok
 */
bool database_add_meteo(struct database *db, unsigned id, float temp, float hum);

/*
 * Closing connection
 */
void database_close(struct database *db);


#endif