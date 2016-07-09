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
#include "log.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

struct send_data
{
	unsigned device_id;
	float temp_in;
	float temp_out;
	float hum_in;
	float hum_out;
};

static struct {
	struct dht22 dht_in;
	struct dht22 dht_out;
	struct tcp_client client;
} checker;


static void checker_handle()
{
	struct error err;
	struct send_data sdata;
	struct server_cfg *sc = configs_get_server();
	struct device_cfg *dc = configs_get_device();

	for (size_t i = 0; i < 50; i++) {
		bool s_in = false;
		bool s_out = false;

		s_in = dht22_read_data(&checker.dht_in, &sdata.temp_in, &sdata.hum_in, &err);
		if (!s_in) {
			log_local("Fail reading data from inside sensor.", LOG_WARNING);
			log_local(err.message, LOG_ERROR);
		}

		s_out = dht22_read_data(&checker.dht_out, &sdata.temp_out, &sdata.hum_out, &err);
		if (!s_out) {
			log_local("Fail reading data from outside sensor.", LOG_WARNING);
			log_local(err.message, LOG_ERROR);
		}

		if (s_in && s_out)
			break;
		else
			sleep(1000);
		printf("Retry reading sensors... %d\n", (int)i);
	}

	puts("Sending data to server.");
	sdata.device_id = dc->id;
	if (!tcp_client_connect(&checker.client, sc->ip, sc->port)) {
		log_local("Fail connecting to server!", LOG_ERROR);
		return;
	}
	if (!tcp_client_send(&checker.client, (const void *)&sdata, sizeof(sdata))) {
		tcp_client_close(&checker.client);
		return;
	}
	tcp_client_close(&checker.client);
	puts("Complete.");
}

bool checker_start(void)
{
	struct checker_cfg *cc = configs_get_checker();
	struct sensors_cfg *ss = configs_get_sensors();

	if (!dht22_init(&checker.dht_in, ss->dht_in)) {
		log_local("Fail init inside sensor.", LOG_ERROR);
		return false;
	}
	dht22_init(&checker.dht_out, ss->dht_out);

    for (;;) {
        struct timeval tv = {cc->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        checker_handle();
    }
    return true;
}