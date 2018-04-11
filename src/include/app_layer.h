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
 * @brief enumeration of the available application protocols.
 */
enum app_protocols {
    HTTP,
    CoAP,
    MQTT
};


/**
 * @brief starts the application layer of the communication stack. It switches
 * between available application protocols
 *
 * @param app_proto
 *
 * @return 
 */
int8_t application_layer_start(enum app_protocols app_proto);


/**
 * @brief sends a given reading that has been previously formatted. This
 * function is called by the part that is responsible for transmission logic.
 * What it does is, according to the chosen application protocol, calls the
 * corresponding function *_send which will carry the transmission in the
 * right channel.
 *
 * @param formatted_reading     a constant reference to a formatted reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t send_a_reading(const char *formatted_reading);


/**
 * @brief sends a given formatted reading via HTTP application protocol.
 *
 * @param formatted_reading     a constant reference to a formatted reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t http_send(const char *formatted_reading);


/**
 * @brief sends a given formatted reading via CoAP application protocol.
 *
 * @param formatted_reading     a constant reference to a formatted reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t coap_send(const char *formatted_reading);


/**
 * @brief sends a given formatted reading via MQTT application protocol.
 *
 * @param formatted_reading     a constant reference to a formatted reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t mqtt_send(const char *formatted_reading);


