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

struct checker_cfg {
	unsigned interval;	
};

struct server_cfg {
	char ip[16];
	unsigned port;
};

struct device_cfg {
	unsigned id;	
};

struct sensors_cfg {
	unsigned dht_in;
	unsigned dht_out;
};


/*
 * Checker timer configs
 */
struct checker_cfg *configs_get_checker();

/*
 * Remote tcp server configs
 */
struct server_cfg *configs_get_server();

/*
 * Device configs
 */
struct device_cfg *configs_get_device();

/*
 * Sensors configs
 */
struct sensors_cfg *configs_get_sensors();

/**
 * Loading configs from file to RAM
 * @filename: name of json configs file
 *
 * returns false: if fail loading
 * returns true: if succeful loading
 */
bool configs_load(const char *filename);


#endif