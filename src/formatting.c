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


#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>

#include "formatting.h"

int8_t
json_of_reading(cJSON *json, const struct a_reading *reading)
{
    int8_t rc = 0;
    cJSON *bme280_reading;

    printf("[json_of_reading] ##########################\n");
    // print_a_reading(reading);

    /* create root node */
    json = cJSON_CreateObject();

    if (cJSON_AddNumberToObject(json, "timestamp", reading->timestamp) == NULL)
    {
        goto end;
    }

    bme280_reading = cJSON_CreateObject();

    if (cJSON_AddNumberToObject(bme280_reading, "temperature", reading->data.temperature) == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(bme280_reading, "pressure", reading->data.pressure) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(bme280_reading, "humidity", reading->data.humidity) == NULL)
    {
        goto end;
    }

    cJSON_AddItemToObject(json, "reading", bme280_reading);

    /* debug */
    printf("%s\n", cJSON_Print(json)); // json actually contains smthg but it can't figure
    // why i'm not able to read it afterwards.

    return rc;

end:
    cJSON_Delete(json);
    return -1;
}

/* Assemble multiple readings in a unique json object */
int8_t
json_of_readings(cJSON *json, const struct a_reading **readings)
{
    int8_t rc;
    rc = ENOSYS;
    // TODO
    return rc;
}

int8_t
string_of_json(char *buff, cJSON *json)
{
    int8_t rc;

    // FIXME :
    // There seems to be a problem here : *json doesn't seem
    // to refer to actual proper value. Thus, buff is not correctly allocated
    // memcpy(buff, json, sizeof(*json));
    buff = cJSON_Print(json);
    printf("[string_of_json] json address: %p\n", (void*)json);
    if (buff == NULL) {

        // FIXME : this is somehow a workaround because I can't manage to properly
        // format the JSON to a string. Although, I suspect this is not the right
        // way to do it. I only want to have a proper JSON message to send over HTTP
        // in order not to be stuck too long here
        buff = (char*)malloc(200 * sizeof(char));
        buff = "{'error': 'no json could be formatted'}";

        rc = -1;
    }

    return rc;
}

int8_t
reading_formatting(char *representation, const struct a_reading *reading)
{
    int8_t rc;
    cJSON json;

    // make a json object from dequeued reading
    rc = json_of_reading(&json, reading);
    if (rc < 0) {
        printf("[IoT-Labs] Error while making json from a reading\n");
        return rc;
    }

    // get string representation of json object
    rc = string_of_json(representation, &json);
    if (rc < 0) {
        printf("[IoT-Labs] Error while getting string repr. from json\n");
        return rc;
    }

    return rc;
}
