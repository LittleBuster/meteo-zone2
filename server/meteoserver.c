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


static struct {
	struct tcp_server server;
} mserver;


void new_session(struct tcp_client *s_client, void *data, pthread_mutex_t *mutex)
{
}

bool meteo_server_start()
{
	tcp_server_set_cb(&mserver.server, new_session, NULL);
	if (!tcp_server_bind(&mserver.server, 5000, 1000)) {
		log_local("Fail binding tcp server.", LOG_ERROR);
		return false;
	}
	return true;
}