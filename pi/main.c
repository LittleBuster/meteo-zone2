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
 
#include "log.h"
#include "configs.h"
#include "checker.h"


int main(void)
{
	uint8_t ret_val;

	log_set_path("/var/log/meteo.log");

	ret_val = configs_load("/etc/meteo.cfg");
	if (ret_val != CFG_OK) {
		char msg[512];

		strcpy(msg, "Fail loading configs file: ");
		switch(ret_val) {
			case CFG_FILE_NOT_FOUND: {
				strcat(msg, "file not found.");
				break;
			}
			case CFG_CC_INTERVAL_ERR: {
				strcat(msg, "checker interval reading error.");
				break;
			}
			case CFG_SC_IP_ERR: {
				strcat(msg, "server ip reading error.");
				break;
			}
			case CFG_SC_PORT_ERR: {
				strcat(msg, "server port reading error.");
				break;
			}
			case CFG_DC_ID_ERR: {
				strcat(msg, "device ID reading error.");
				break;
			}
			case CFG_DC_KEY_ERR: {
				strcat(msg, "device key reading error.");
				break;
			}
			case CFG_SS_IN_ERR: {
				strcat(msg, "sensor in reading error.");
				break;
			}
			case CFG_SS_OUT_ERR: {
				strcat(msg, "sensor out reading error.");
				break;
			}
		}
		log_local(msg, LOG_ERROR);
		return -1;
	}
	if (!checker_start())
		return -1;
	return 0;
}