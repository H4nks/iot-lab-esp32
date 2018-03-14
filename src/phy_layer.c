/*
 * IoT-Labs-2018 
 * Copyright (C) 2018 Massinissa Hamidi 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <errno.h>

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"

#include "phy_layer.h"

#define WIFI_SSID   "HanksDroid"
#define WIFI_PASS   "alpine123"

EventGroupHandle_t wifi_event_group;
const int IPv4_CONNECTED_BIT = BIT0;
const int IPv6_CONNECTED_BIT = BIT1;

static esp_err_t event_handler(void *ctx, system_event_t *event);
int8_t wifi_init();
int8_t ble_init();

// Wifi event handler
static esp_err_t
event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {

        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            break;

        case SYSTEM_EVENT_STA_GOT_IP:
            xEventGroupSetBits(wifi_event_group, IPv4_CONNECTED_BIT);
            break;

        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            esp_wifi_connect();
            xEventGroupSetBits(wifi_event_group, IPv6_CONNECTED_BIT);
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            // TODO failwith "Student, this is your job!"
            // FIXME when disconnected, try to reconnect by making a call to initialize_wifi()
            break;

        default:
            break;
    }

    return ESP_OK;
}

// FIXME add documentation
/* default: STAtion mode */
int8_t
_wifi_init()
{
    int8_t rc = ESP_OK;

    // create the event group to handle wifi events
    wifi_event_group = xEventGroupCreate();

    // initialize the wifi event handler
    esp_event_loop_init(event_handler, NULL);
    if (rc < 0) {
        printf("[IoT-Labs] Error while initializing the wifi event handler");
        return rc;
    }

    // initialize the wifi stack in STAtion mode with config in RAM
    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&init_config);
    if (rc < 0) {
        printf("[IoT-Labs] Error configuring wifi");
        return rc;
    }

    // FIXME de we absolutely need this one?
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    if (rc < 0) {
        printf("[IoT-Labs] Error configuring wifi");
        return rc;
    }

    esp_wifi_set_mode(WIFI_MODE_STA);
    if (rc < 0) {
        printf("[IoT-Labs] Error configuring wifi");
        return rc;
    }

    // configure the wifi connection and start the interface
    wifi_config_t config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        }
        // TODO failwith "Student, this is your job!"
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA, &config);

    return rc;
}

int8_t
ble_init()
{
    // TODO failwith "Student, this is your job!"
    int8_t rc;
    rc = ENOSYS;
    return rc;
}

int8_t
ble_start()
{
    // TODO failwith "Student, this is your job!"
    int8_t rc;
    rc = ENOSYS;
    return rc;
}

int8_t
physical_layer_start(enum MAC_PHY_interfaces phy_proto)
{
    int8_t rc;
	
    switch (phy_proto) {
        case WIFI:
            rc = _wifi_init();
            if (rc < 0) {
                printf("[IoT-Labs] Error while initializing WiFi interface\n");
                return rc;
            }

            printf("[physical_layer_start] launching esp_wifi_start %d\n", phy_proto);
            rc = esp_wifi_start();
            if (rc < 0) {
                printf("[IoT-Labs] Error while starting WiFi interface\n");
                return rc;
            }

            break;

        case BLE:
            rc = ble_init();
            rc = ble_start();
            // TODO what esp32 function do we need to call in order to start
            // BLE communication?
            // Probably this one:
            // `esp_err_t esp_ble_gap_start_scanning(uint32_t duration)`
            return ENOSYS;
            break;

        case ZIGBEE:
            printf("[IoT-Labs] Not yet supported\n");
            return ENOSYS;
            //break;

        default:
            rc = ENOSYS;
            break;
    }

    return rc;
}

