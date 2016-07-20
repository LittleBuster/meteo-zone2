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

#include "log.h"
#include "configs.h"
#include "meteoserver.h"
#include <stdio.h>
#include <string.h>


int main()
{
	if (!log_set_path("/var/log/meteosrv.log")) {
		puts("Fail setting log path. Path is to long.");
		return -1;
	}
	if (!configs_load("/etc/meteosrv.conf")) {
		log_local("Fail reading configs file.", LOG_ERROR);
		return -1;
	}
	if (!meteo_server_start()) {
		log_local("Fail starting meteo server.", LOG_ERROR);
		return -1;
	}
	return 0;
}