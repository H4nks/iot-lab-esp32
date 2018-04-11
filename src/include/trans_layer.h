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
 * @brief enumeration of the available transport protocols.
 */
enum trans_protocols {
    TCP,
    UDP,
};


/**
 * @brief starts the transport layer. It establishes a connection, in the case
 * of TCP, with a remote server. In the case where ssl flag is set to 1, the
 * transmissions are encrypted via an additional layer (SSL/TLS) before being
 * passed to the socket and then transmitted.
 *
 * @param app_proto     the chosen transport layer protocol.
 * @param ssl           flag specifying whereas to encrypt data or not.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t transport_layer_start(enum trans_protocols app_proto, int ssl);


/**
 * @brief this function is called from the application layer (*_send functions)
 * in order to send application data over the transport layer. In the case of
 * TCP transport protocol, it sends data through a previously created socket.
 *
 * @param data  a constant reference to data to be sent.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t trans_send(const void *data);

