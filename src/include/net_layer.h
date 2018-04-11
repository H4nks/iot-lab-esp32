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


/**
 * @brief enumeration of the available network protocols.
 */
enum net_protocols {
    IPv4,
    IPv6,
    _6LowPAN
};


/**
 * @brief sets up the configuration parameters for the network interface
 * responsible for relaying IPv4 packets over the network.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t setup_ipv4(void);


/**
 * @brief sets up the configuration parameters for the network interface
 * reponsible for relaying IPv6 packets over the network.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t setup_ipv6(void);


/**
 * @brief sets up the configuration parameters for the network interface
 * responsible for relaying 6LowPAN packets over the network. This is actually
 * an adaptation layer which implement compression mechanism in order to make
 * IPv6 packets able to be transferred over constrained physical interfaces
 * like 802.15.4 (ZigBee).
 * Note that compression mechanisms for transmitting IPv6 packets over BLE are
 * specified by the IETF's RFC7668 and has its own implementation available in
 * the LwIP source tree.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t setup_lowpan6(void);


/**
 * @brief sets up the configuration parameters for the network interface
 * responsible for relaying 6LowPAN packets over the BLE physical interface.
 * Note that compression mechanisms for transmitting IPv6 packets over BLE are
 * specified by the IETF's RFC7668 and has its own implementation available in
 * the LwIP source tree.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t setup_lowpan6_ble(void);


/**
 * @brief starts the network layer of the communication stack. It switches
 * between the available network protocols and calls the corresponding setup_*
 * function which will be responsible for setting the right configuration
 * parameters for the network interface.
 * Note that the configurations are based on the netif structure provided by
 * the LwIP TCP/IP stack, take a look at the source tree of LwIP
 * http://git.savannah.nongnu.org/cgit/lwip.git/tree/src/include/netif/
 *
 * @param net_proto     chosen network protocol among available ones.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t network_layer_start(enum net_protocols net_proto);

