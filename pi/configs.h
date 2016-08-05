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


enum error_codes {
    CFG_FILE_NOT_FOUND,
    CFG_CC_INTERVAL_ERR,
    CFG_SC_IP_ERR,
    CFG_SC_PORT_ERR,
    CFG_DC_ID_ERR,
    CFG_DC_KEY_ERR,
    CFG_SS_IN_ERR,
    CFG_SS_OUT_ERR,
    CFG_OK
};

/**
 * Loading configs from file to RAM
 * @filename: name of json configs file
 *
 * returns error codes: if fail loading
 * returns CFG_OK: if succefful loading
 */
uint8_t configs_load(const char *filename);


struct checker_cfg {
	unsigned interval;	
};

/*
 * Checker timer configs
 */
struct checker_cfg *configs_get_checker();


struct server_cfg {
	char ip[25];
	unsigned port;
};

/*
 * Remote tcp server configs
 */
struct server_cfg *configs_get_server();


struct device_cfg {
	unsigned id;
	char key[65];
};

/*
 * Device configs
 */
struct device_cfg *configs_get_device();


struct sensors_cfg {
	unsigned dht_in;
	unsigned dht_out;
};

/*
 * Sensors configs
 */
struct sensors_cfg *configs_get_sensors();


#endif