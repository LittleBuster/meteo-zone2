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

#include "meteoserver.h"
#include "tcpserver.h"
#include "log.h"
#include "configs.h"
#include <stdio.h>
#include <string.h>


static struct {
	pthread_mutex_t mutex;
	struct tcp_server server;
} mserver;


static void new_session(struct tcp_client *s_client, void *data)
{
	struct login_data ldata;
	struct meteo_data mdata;
	struct server_answ answ;

	pthread_mutex_lock(&mserver.mutex);
	puts("New client connected.");
	printf("%s", "Client login...");
	pthread_mutex_unlock(&mserver.mutex);

	if (!tcp_client_recv(s_client, (void *)&ldata, sizeof(ldata))) {
		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local("Fail receiving key data.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}

	//Checking ID && KEY

	if (!tcp_client_send(s_client, (const void *)&answ, sizeof(answ))) {
		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local("Fail sending key checking answare.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}
	if (answ.code != KEY_OK) {
		char msg[255];
		char id[9];

		sprintf(msg, "%d", (int)ldata.id);
		strcpy(msg, "Fail client authentication. ID:");
		strcat(msg, id);

		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local(msg, LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}
	pthread_mutex_lock(&mserver.mutex);
	printf("%s\n", "OK.");
	pthread_mutex_unlock(&mserver.mutex);

	printf("%s", "Receiving meteo data...");
	if (!tcp_client_recv(s_client, (void *)&mdata, sizeof(mdata))) {
		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local("Fail receiving meteo answare.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		answ.code = DATA_FAIL;
		return;
	}
	answ.code = DATA_OK;

	if (!tcp_client_send(s_client, (const void *)&answ, sizeof(answ))) {
		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local("Fail sending meteo answare.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}
	if (answ.code != DATA_OK) {
		pthread_mutex_lock(&mserver.mutex);
		printf("%s\n", "FAIL!");
		log_local("Fail meteo data.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}
	pthread_mutex_lock(&mserver.mutex);
	printf("%s\n", "OK.");

	puts("================================");
	printf("ID: %d\n", (int)ldata.id);
	printf("Inside: Temp: %.2f Hum: %.2f\n", mdata.temp_in, mdata.hum_in);
	printf("Outside: Temp: %.2f Hum: %.2f\n", mdata.temp_out, mdata.hum_out);
	puts("================================");
	pthread_mutex_unlock(&mserver.mutex);

	//Add to database
}

bool meteo_server_start()
{
	struct server_cfg *sc = configs_get_server();

	puts("Starting server...");
	pthread_mutex_init(&mserver.mutex, NULL);

	tcp_server_set_newsession_cb(&mserver.server, new_session, NULL);
	if (!tcp_server_bind(&mserver.server, sc->port, sc->max_users)) {
		log_local("Fail binding tcp server.", LOG_ERROR);
		return false;
	}
	pthread_mutex_destroy(&mserver.mutex);
	return true;
}