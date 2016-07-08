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

#include "checker.h"
#include "configs.h"
#include "dht22.h"
#include "tcpclient.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>


static struct {
	struct dht22 dht_in;
	struct dht22 dht_out;
	struct tcp_client client;
} checker;


static void checker_handle()
{
	struct server_cfg *sc = configs_get_server();
}

void checker_start(void)
{
	struct checker_cfg *cc = configs_get_checker();
	
    for (;;) {
        struct timeval tv = {cc->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        checker_handle();
    }
}