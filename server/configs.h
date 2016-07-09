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

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <stdbool.h>

struct server_cfg {
	unsigned port;
	unsigned max_users;
};

struct database_cfg {
	char ip[16];
	char user[20];
	char passwd[20];
	char base[20];
};


/*
 * Database server configs
 */
struct database_cfg *configs_get_database();

/*
 * Server configs
 */
struct server_cfg *configs_get_server();

/**
 * Loading configs from file to RAM
 * @filename: name of json configs file
 *
 * returns false: if fail loading
 * returns true: if succeful loading
 */
bool configs_load(const char *filename);


#endif