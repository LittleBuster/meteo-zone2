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


int main(void)
{
	uint8_t ret_val;

	if (!log_set_path("/var/log/meteosrv.log")) {
		puts("Fail setting log path. Path is to long.");
		return -1;
	}
	ret_val = configs_load("/etc/meteosrv.conf");
	if (ret_val != CFG_OK) {
		char msg[512];
		
		strcpy(msg, "Fail loading configs file: ");
		switch(ret_val) {
			case CFG_FILE_NOT_FOUND: {
				strcat(msg, "file not found.");
				break;
			}
			case CFG_SC_PORT_ERR: {
				strcat(msg, "server port reading error.");
				break;
			}
			case CFG_SC_MAX_ERR: {
				strcat(msg, "server max users reading error.");
				break;
			}
			case CFG_DB_IP_ERR: {
				strcat(msg, "database IP reading error.");
				break;
			}
			case CFG_DB_USER_ERR: {
				strcat(msg, "database user reading error.");
				break;
			}
			case CFG_DB_PASSWD_ERR: {
				strcat(msg, "database passwd reading error.");
				break;
			}
			case CFG_DB_BASE_ERR: {
				strcat(msg, "database base reading error.");
				break;
			}
		}
		log_local(msg, LOG_ERROR);
		return -1;
	}
	if (!meteo_server_start()) {
		log_local("Fail starting meteo server.", LOG_ERROR);
		return -1;
	}
	return 0;
}