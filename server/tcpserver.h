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

#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "tcpclient.h"

#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#define SOCKET int


struct tcp_server {
    /* Socket id */
    SOCKET s;
    pthread_mutex_t mutex;

    /* User data */
    void *data;

    /**
     * Client accept error signal
     * @data: user data
     */
    void (*accept_error)(void *data);

    /*
     * New client session
     */
    void (*new_session)(struct tcp_client *s_client, void *data, pthread_mutex_t *mutex);
};


/*
 * Socket initialization
 */
void tcp_server_init(struct tcp_server *restrict sock);

/**
 * Bind ip address and starting socket server
 * @sock: socket struct
 * @ip: ip address of server
 * @port: tcp port of server
 * @max_clients: maximum connected clients
 * @data: user data
 *
 * Returns true if succeful starting
 * Returns false if fail binding ip address or port
 */
bool tcp_server_bind(struct tcp_server *sock, const unsigned short port, const unsigned max_clients, void *data);


#endif