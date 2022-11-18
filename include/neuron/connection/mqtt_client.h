/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2022 EMQ Technologies Co., Ltd All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **/

#ifndef NEURON_CONNECTION_MQTT_CLIENT_H
#define NEURON_CONNECTION_MQTT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils/zlog.h"

typedef void (*neu_mqtt_client_cb_t)(void *data);
typedef void (*neu_mqtt_client_subscribe_cb_t)(const uint8_t *payload,
                                               uint32_t len, void *data);

typedef enum {
    NEU_MQTT_VERSION_V31  = 3,
    NEU_MQTT_VERSION_V311 = 4,
    NEU_MQTT_VERSION_V5   = 5,
} neu_mqtt_version_e;

typedef enum {
    NEU_MQTT_QOS0,
    NEU_MQTT_QOS1,
    NEU_MQTT_QOS2,
} neu_mqtt_qos_e;

typedef struct neu_mqtt_client_s neu_mqtt_client_t;

neu_mqtt_client_t *neu_mqtt_client_new(neu_mqtt_version_e version);
neu_mqtt_client_t *neu_mqtt_client_from_addr(const char *host, uint16_t port,
                                             neu_mqtt_version_e version);
void               neu_mqtt_client_free(neu_mqtt_client_t *client);

bool neu_mqtt_client_is_opened(neu_mqtt_client_t *client);
bool neu_mqtt_client_is_connected(neu_mqtt_client_t *client);

int neu_mqtt_client_set_addr(neu_mqtt_client_t *client, const char *host,
                             uint16_t port);
int neu_mqtt_client_set_user(neu_mqtt_client_t *client, const char *username,
                             const char *password);
int neu_mqtt_client_set_connect_cb(neu_mqtt_client_t *  client,
                                   neu_mqtt_client_cb_t cb, void *data);
int neu_mqtt_client_set_disconnect_cb(neu_mqtt_client_t *  client,
                                      neu_mqtt_client_cb_t cb, void *data);
int neu_mqtt_client_set_tls(neu_mqtt_client_t *client, const char *ca,
                            const char *cert, const char *key,
                            const char *keypass);
int neu_mqtt_client_set_msg_cache_limit(neu_mqtt_client_t *client,
                                        size_t             cache_limit);
int neu_mqtt_client_set_zlog_category(neu_mqtt_client_t *client,
                                      zlog_category_t *  cat);

int neu_mqtt_client_open(neu_mqtt_client_t *client);
int neu_mqtt_client_close(neu_mqtt_client_t *client);

int neu_mqtt_client_publish(neu_mqtt_client_t *client, neu_mqtt_qos_e qos,
                            const char *topic, const char *payload, size_t len);
int neu_mqtt_client_subscribe(neu_mqtt_client_t *client, neu_mqtt_qos_e qos,
                              const char *                   topic,
                              neu_mqtt_client_subscribe_cb_t cb, void *data);

#ifdef __cplusplus
}
#endif

#endif