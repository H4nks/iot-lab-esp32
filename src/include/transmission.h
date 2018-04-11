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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "bme280.h"

#define MAX_READINGS    100


/**
 * @brief global queue that serves as a buffer/tampon for transmissions.
 * The task responsible for sensor readings writes readings to this queue and
 * the one responsible for transmissions reads readings from it and sends them
 * through the communication stack.
 * It is thread safe and simultaneous read/write are handled by freeRTOS.
 * for more information take a look at freeRTOS documentation.
 */
extern QueueHandle_t sensor_readings_queue;


/**
 * @brief structure defining the atomic unit of data that is collected and
 * then exchanged.
 * Note that this definition is specifically designed for bme280. Keep it like
 * this for the moment, but if you want to extend your program, please feel
 * free to make the necessary changes.
 */
struct a_reading {
    TickType_t timestamp;
    struct bme280_data data;
};


/**
 * @brief initializes the global transmission queue.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t transmission_init(void);


/**
 * @brief writes the given reading into the global transmission queue. The
 * current underlying implementation makes it block until there is available
 * free place to put the given reading in, in the case where the global queue
 * is full.
 *
 * @param reading   a reference to a reading.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t transmission_enqueue(struct a_reading *reading);


/**
 * @brief reads a reading from the global transmission queue and is made
 * available in the reference reading. The current underlying implementation
 * makes the call to this function block until a reading is available, in the
 * case where queue is empty.
 *
 * @param reading   a reference to the reading to put in the global queue.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t transmission_dequeue(struct a_reading *reading);


/**
 * @brief fills the provided reference to a reading with data contained in the
 * reference to the given bme280_data structure.
 * Note that this function does not allocate memory for reading. The momory
 * should be allocated prior to the call to this function.
 *
 * @param reading   a reference to an allocated reading.
 * @param data      a reference to a bme280 data structure.
 *
 * @return  0 on success and -1 on failure.
 */
int8_t make_a_reading(struct a_reading *reading, struct bme280_data *data);


/**
 * @brief prints a reading given a reference to it. This function is useful for
 * debugging your program.
 *
 * @param reading   a constant reference to a reading.
 */
void print_a_reading(const struct a_reading *reading);


/**
 * @brief this function is launched as a freeRTOS task. It runs for ever (while
 * it does not encounter errors). It reads a reading from the global
 * transmission queue, formats the reading, and then sends the representation
 * corresponding to it.
 *
 * @param pvParameters  freeRTOS parameters.
 */
void perform_transmissions(void *pvParameters);

