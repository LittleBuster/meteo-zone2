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
	struct tcp_server server;
} mserver;


static void new_session(struct tcp_client *s_client, void *data, pthread_mutex_t *mutex, void *user_data)
{
	struct recv_data rdata;

	if (!tcp_client_recv(s_client, (void *)&rdata, sizeof(rdata))) {
		pthread_mutex_lock(mutex);
		log_local("Fail receiving data.", LOG_ERROR);
		pthread_mutex_unlock(mutex);
		return;
	}

	printf("ID: %d\n", (int)rdata.device_id);
	printf("Inside: Temp: %.2f Hum: %.2f\n", rdata.temp_in, rdata.hum_in);
	printf("Outside: Temp: %.2f Hum: %.2f\n", rdata.temp_out, rdata.hum_out);
	puts("================================");
}

bool meteo_server_start()
{
	struct server_cfg *sc = configs_get_server();

	puts("Starting server...");
	tcp_server_set_newsession_cb(&mserver.server, new_session, NULL);
	if (!tcp_server_bind(&mserver.server, sc->port, sc->max_users)) {
		log_local("Fail binding tcp server.", LOG_ERROR);
		return false;
	}
	return true;
}