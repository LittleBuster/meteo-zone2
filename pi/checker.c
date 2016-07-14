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

#include "checker.h"
#include "configs.h"
#include "dht22.h"
#include "tcpclient.h"
#include "log.h"
#include "gpio.h"
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
	struct error err;	
	struct login_data ldata;
	struct meteo_data mdata;
	struct server_answ answ;
	struct server_cfg *sc = configs_get_server();
	struct device_cfg *dc = configs_get_device();

	for (size_t i = 0; i < 50; i++) {
		bool s_in = false;
		bool s_out = false;

		s_in = dht22_read_data(&checker.dht_in, &mdata.temp_in, &mdata.hum_in, &err);
		if (!s_in) {
			log_local("Fail reading data from inside sensor.", LOG_WARNING);
			log_local(err.message, LOG_ERROR);
		}

		s_out = dht22_read_data(&checker.dht_out, &mdata.temp_out, &mdata.hum_out, &err);
		if (!s_out) {
			log_local("Fail reading data from outside sensor.", LOG_WARNING);
			log_local(err.message, LOG_ERROR);
		}

		if (s_in && s_out) {
			printf("Inside sensor: Temp: %.2f Hum: %.2f\n", mdata.temp_in, mdata.hum_in);
			printf("Outside sensor: Temp: %.2f Hum: %.2f\n", mdata.temp_out, mdata.hum_out);
			break;
		}
		else
			sleep(1);
		printf("Retry reading sensors... %d\n", (int)i);
	}

	puts("Sending data to server.");
	if (!tcp_client_connect(&checker.client, sc->ip, sc->port)) {
		log_local("Fail connecting to server!", LOG_ERROR);
		return;
	}
	ldata.id = dc->id;
	strncmp(ldata.key, dc->key, 64);
	printf("%s", "Login...");

	if (!tcp_client_send(&checker.client, (const void *)&ldata, sizeof(ldata))) {
		tcp_client_close(&checker.client);
		printf("%s\n", "FAIL!");
		log_local("Fail sending key data.", LOG_ERROR);
		return;
	}
	if (!tcp_client_recv(&checker.client, (void *)&answ, sizeof(answ))) {
		tcp_client_close(&checker.client);
		printf("%s\n", "FAIL!");
		log_local("Fail receiving key checking answare.", LOG_ERROR);
		return;
	}
	if (answ.code != KEY_OK) {
		printf("%s\n", "FAIL!");
		log_local("Fail authentication.", LOG_ERROR);
		tcp_client_close(&checker.client);
		return;
	}
	printf("%s\n", "OK.");

	printf("%s", "Sending meteo data...");
	if (!tcp_client_send(&checker.client, (const void *)&mdata, sizeof(mdata))) {
		tcp_client_close(&checker.client);
		printf("%s\n", "FAIL!");
		log_local("Fail sending meteo answare.", LOG_ERROR);
		return;
	}
	if (!tcp_client_recv(&checker.client, (void *)&answ, sizeof(answ))) {
		tcp_client_close(&checker.client);
		printf("%s\n", "FAIL!");
		log_local("Fail receiving meteo answare.", LOG_ERROR);
		return;
	}
	if (answ.code != DATA_OK) {
		printf("%s\n", "FAIL!");
		log_local("Server: Fail meteo data.", LOG_ERROR);
		tcp_client_close(&checker.client);
		return;
	}
	printf("%s\n", "OK.");
	tcp_client_close(&checker.client);
}

bool checker_start(void)
{
	struct checker_cfg *cc = configs_get_checker();
	struct sensors_cfg *sc = configs_get_sensors();

	if (!gpio_init) {
		log_local("Fail init GPIOs.", LOG_ERROR);
		return false;
	}
	dht22_init(&checker.dht_in, sc->dht_in);
	dht22_init(&checker.dht_out, sc->dht_out);

    for (;;) {
        struct timeval tv = {cc->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        checker_handle();
    }
    return true;
}