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
 
#ifndef __METEOSERVER_H__
#define __METEOSERVER_H__

#include <stdbool.h>

enum {
	KEY_OK,
	KEY_FAIL,
	DATA_OK,
	DATA_FAIL
};

struct server_answ {
	unsigned code;
};

struct login_data {
	unsigned id;
	char key[65];
};

struct meteo_data {	
	float temp;
	float hum;
};



/*
 * Starting meteo server
 */
bool meteo_server_start();


#endif