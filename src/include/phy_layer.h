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


#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

extern EventGroupHandle_t wifi_event_group;
extern const int IPv4_CONNECTED_BIT;
extern const int IPv6_CONNECTED_BIT;

/**
 * @brief enumeration of the available physical interfaces.
 */
enum MAC_PHY_interfaces {
    WIFI,
    BLE,
    ZIGBEE
};



/**
 * @brief starts the physical layer according to the phy_proto argument.
 *
 * @param phy_proto     the chosen physical interface to run the communication
 * stack upon.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t physical_layer_start(enum MAC_PHY_interfaces phy_proto);

