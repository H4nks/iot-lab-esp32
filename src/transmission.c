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
#include <string.h>

#include "formatting.h"
#include "app_layer.h"

#define REPR_MAX    200

QueueHandle_t sensor_readings_queue;

int8_t
transmission_init()
{
    int8_t rc;

    sensor_readings_queue = xQueueCreate(MAX_READINGS, sizeof(struct a_reading));
    if (sensor_readings_queue == NULL) {
        printf("[IoT-Labs] Error while creating transmission queue\n");
        return ENOMEM;
    }

    return rc;
}

int8_t
transmission_enqueue(struct a_reading *reading)
{
    int8_t rc;

    rc = xQueueSendToBack(sensor_readings_queue, (void*)reading, portMAX_DELAY);
    if (rc != pdPASS) {
        printf("[IoT-Labs] Error while enqueuing a reading\n");
        return rc;
    }

    return rc;
}

int8_t
transmission_dequeue(struct a_reading *reading)
{
    int8_t rc;

    rc = xQueueReceive(sensor_readings_queue, reading, portMAX_DELAY);
    if (rc != pdTRUE) {
        printf("[IoT-Labs] Error while dequeuing a reading\n");
        return rc;
    }

    return rc;
}

int8_t
make_a_reading(struct a_reading *reading, struct bme280_data *data)
{
    int8_t rc = 0;

    reading->timestamp = xTaskGetTickCount();
    memcpy(&reading->data, data, sizeof(*data));

    /* debug */
    /*
    printf("[make_a_reading] reading->timestamp = %d\n", reading->timestamp);
    printf("[make_a_reading] reading->data->temperature = %d\n",
            reading->data.temperature);

    */

    return rc;
}

void
print_a_reading(const struct a_reading *reading)
{
    assert(reading != NULL);
    printf("[print_a_reading] timestamp = %d\n", reading->timestamp);
    printf("[print_a_reading] temperature = %f\n",
            (float)reading->data.temperature);
}

void
perform_transmissions(void *pvParameters)
{
    int8_t rc;
    struct a_reading reading;
    char representation[REPR_MAX];
    cJSON json; // FIXME very bad! very, very bad! make code modular! get rid of porosity

    // TODO make this function wait for the connection event
    while (1) {
        /* get a reading from transmission queue */

        rc = transmission_dequeue(&reading);

        /* debug */
        // print_a_reading(&reading);

        /* format the dequeued reading and get the string representation
         * corresponding to it
         */
        rc = json_of_reading(&json, &reading);



        /* send the formatted reading */
        rc = ENOSYS; 
    }

// end:
    vTaskDelete(NULL);
}
