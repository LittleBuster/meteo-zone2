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
	log_set_path("/var/log/meteo.log");
	if (!configs_load("/etc/meteo.cfg")) {
		log_local("Fail reading configs file.", LOG_ERROR);
		return -1;
	}
	if (!checker_start())
		return -1;
	return 0;
}