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

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <stdbool.h>
#include <stdint.h>


enum error_codes {
	CFG_FILE_NOT_FOUND,
	CFG_SC_PORT_ERR,
	CFG_SC_MAX_ERR,
	CFG_DB_IP_ERR,
	CFG_DB_USER_ERR,
	CFG_DB_PASSWD_ERR,
	CFG_DB_BASE_ERR,
	CFG_OK
};

/**
 * Loading configs from file to RAM
 * @filename: name of json configs file
 *
 * returns error codes: if fail loading
 * returns CFG_OK: if succeful loading
 */
uint8_t configs_load(const char *filename);


struct database_cfg {
	char ip[16];
	char user[255];
	char passwd[255];
	char base[255];
};

/*
 * Database server configs
 */
struct database_cfg *configs_get_database(void);


struct server_cfg {
	unsigned port;
	unsigned max_users;
};

/*
 * Get server configs
 */
struct server_cfg *configs_get_server(void);


#endif
