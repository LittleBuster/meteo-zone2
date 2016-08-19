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
#include "database.h"
#include <stdio.h>
#include <string.h>


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

static struct {
	pthread_mutex_t mutex;
	struct tcp_server server;
	struct database db;
} mserver;


static void exit_fail(const char *message)
{
	pthread_mutex_lock(&mserver.mutex);
	printf("%s\n", "FAIL!");
	log_local(message, LOG_ERROR);
	pthread_mutex_unlock(&mserver.mutex);
}

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
		exit_fail("Fail receiving key data.");
		return;
	}
	/*
	 * Checking ID && KEY
	 */
	struct database_cfg *db = configs_get_database();

	if (!database_connect(&mserver.db, db->ip, db->user, db->passwd, db->base)) {
		pthread_mutex_lock(&mserver.mutex);
		log_local("Fail connecting to database.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		return;
	}
	if (!database_check_user(&mserver.db, ldata.id, ldata.key)) {
		char msg[255];
		char num[20];

		sprintf(num, "%u", ldata.id);
		strcpy(msg, "Fail user authentication. ID: ");
		strcat(msg, num);
		pthread_mutex_lock(&mserver.mutex);
		log_local(msg, LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
		answ.code = KEY_FAIL;
	}
	answ.code = KEY_OK;

	if (!tcp_client_send(s_client, (const void *)&answ, sizeof(answ))) {
		exit_fail("Fail sending key checking answare.");
		database_close(&mserver.db);
		return;
	}
	if (answ.code != KEY_OK) {
		char msg[255];
		char id[9];

		sprintf(msg, "%u", ldata.id);
		strcpy(msg, "Fail client authentication. ID:");
		strcat(msg, id);

		exit_fail(msg);
		database_close(&mserver.db);
		return;
	}
	pthread_mutex_lock(&mserver.mutex);
	printf("%s\n", "OK.");
	pthread_mutex_unlock(&mserver.mutex);

	printf("%s", "Receiving meteo data...");
	if (!tcp_client_recv(s_client, (void *)&mdata, sizeof(mdata))) {
		exit_fail("Fail receiving meteo answare.");
		answ.code = DATA_FAIL;
		database_close(&mserver.db);
		return;
	}
	answ.code = DATA_OK;

	if (!tcp_client_send(s_client, (const void *)&answ, sizeof(answ))) {
		exit_fail("Fail sending meteo answare.");
		database_close(&mserver.db);
		return;
	}
	if (answ.code != DATA_OK) {
		exit_fail("Fail meteo data.");
		database_close(&mserver.db);
		return;
	}
	pthread_mutex_lock(&mserver.mutex);
	printf("%s\n", "OK.");

	puts("================================");
	printf("ID: %u\n", ldata.id);
	printf("Temp: %.2f Hum: %.2f\n", mdata.temp, mdata.hum);
	puts("================================");
	pthread_mutex_unlock(&mserver.mutex);

	if (!database_add_meteo(&mserver.db, ldata.id, mdata.temp, mdata.hum)) {
		pthread_mutex_lock(&mserver.mutex);
		log_local("Fail adding meteo data to database.", LOG_ERROR);
		pthread_mutex_unlock(&mserver.mutex);
	}
	database_close(&mserver.db);
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
