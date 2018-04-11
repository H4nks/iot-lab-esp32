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
#include "cJSON.h"

#include "transmission.h"

/**
 * @brief constructs a json object tree from a given reading. It constructs the
 * necessary elements and then glues them together.
 *
 * @param json      a reference to the constructed object.
 * @param reading   a constant reference to a reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t json_of_reading(cJSON *json, const struct a_reading *reading);


/**
 * @brief constructs a json object tree from a list of readings. The only
 * difference with json_of_reading is the number of readings that are passed to
 * it. The readings are assembled in the form of an array in the final json
 * object tree.
 *
 * @param json      a reference to the constructed object.
 * @param readings  a constant reference to an array of readings.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t json_of_readings(cJSON *json, const struct a_reading **readings);


/**
 * @brief constructs the string representation buff from a given json object
 * tree. This function makes the necessary checks and ensures that the json
 * object is correctly filled before creating the string representation, it
 * fails otherwise.
 * Note that this function is just a wrapper around the corresponding function
 * provided in cJSON library.
 *
 * @param buff  a reference to the constructed string.
 * @param json  a constant reference to a json object.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t string_of_json(char *buff, cJSON *json);


/**
 * @brief constructs a string representation from a given reading after
 * formatting it. This is the entry point to the formatting library, in other
 * words, here you can specify the way your readings are formatted in order to
 * be sent in the right format agreed upon with the receiver.
 * Note that the default representation is json, but you can implement the
 * whatever format you want.
 *
 * @param representation    a string representation of the formatted reading.
 * @param reading           a constant reference to a reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t reading_formatting(char *representation, const struct a_reading *reading);

