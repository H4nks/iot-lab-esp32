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
 * @brief enumeration of the available types of sensors.
 */
enum sensors {
    BME280,
    DHT11,
};


/**
 * @brief used to specify a bunch of configuration parameters intended to be
 * used for setting up the considered sensors.
 * Note that for now, it is kept to the strict minimum, i.e. only the field
 * used to specify which sensor to consider is implemented.
 */
struct sensors_config_t {
    enum sensors device;
};


/**
 * @brief this function is launched as a freeRTOS task and is responsible for
 * setting up each sensor provided in the sensors_config_t struct.
 * As soon as setup is done, the function triggers a new freeRTOS task, also for
 * each provided sensor, which will perform readings from the sensor.
 *
 * @param pvParameters  freeRTOS parameters.
 */
void setup_sensors(void *pvParameters);


/**
 * @brief this function is launched as a freeRTOS task upon sensor setup. It
 * will be responsible for getting measures from its assigned sensor and making
 * it available for transmissions (For now, the measures are put in a global
 * transmission queue. See transmission.h).
 *
 * @param pvParameters  freeRTOS parameters.
 */
void perform_sensor_readings(void *pvParameters);

