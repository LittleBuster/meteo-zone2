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

struct recv_data
{
	unsigned device_id;
	float temp_in;
	float temp_out;
	float hum_in;
	float hum_out;
};


/*
 * Starting meteo server
 */
bool meteo_server_start();


#endif