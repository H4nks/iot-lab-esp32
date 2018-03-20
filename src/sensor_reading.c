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


#include <string.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"

#include "bme280.h"

#include "sensor_reading.h"
#include "transmission.h"

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 3
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

int8_t initialize_spi_communication();
int8_t initialize_i2c_communication();
int8_t initialize_bme_device(struct bme280_dev *dev);
int8_t _perform_sensor_reading(struct bme280_dev *dev, struct bme280_data *data);

/* Implementation of stubs specefic to ESP32 required by BME280 driver  */
int8_t read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void delay_ms(uint32_t period);

spi_device_handle_t spi;

int8_t
initialize_spi_sensor()
{
    int8_t rc;

    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,     //Clock out at 10 MHz
        .mode = 0,                              //SPI mode 0
        .spics_io_num = PIN_NUM_CS,             //CS pin
        .queue_size = 7,                        //We want to be able to queue 7 transactions at a time
        .address_bits = 8,
    };

    //Initialize the SPI bus
    rc = spi_bus_initialize(VSPI_HOST, &buscfg, 1);
    if (rc < 0) {
        printf("[IoT-Labs] Error while initializing SPI bus\n");
        return rc;
    }

    //Attach the device to the SPI bus
    rc = spi_bus_add_device(VSPI_HOST, &devcfg, &spi);
    if (rc < 0) {
        printf("[IoT-Labs] Error while adding device to SPI bus\n");
        return rc;
    }

    return rc;
}

int8_t
initialize_i2c_communication()
{
    // failwith "Students, this is your job!
    int8_t rc;
    rc = ENOSYS;
    return rc;
}

// FIXME maybe these functions should go into a file specefic to bme280?
int8_t
initialize_bme_device(struct bme280_dev *dev)
{
    int8_t rc;

    dev->intf = BME280_SPI_INTF;
    dev->read = &read;
    dev->write = &write;
    dev->delay_ms = &delay_ms;

    //Initialize the BME280
    rc = bme280_init(dev);
    printf("[initialize_bme_device] rc = %d\n", rc);
    if (rc < 0) {
        printf("[IoT-Labs] Error: bme280 device initialization failled\n");
        return rc;
    }

    return rc;
}

int8_t
read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int rc;
    static struct spi_transaction_t trans;

    trans.tx_buffer = heap_caps_malloc(1, MALLOC_CAP_DMA);
    trans.rx_buffer = heap_caps_malloc(len, MALLOC_CAP_DMA);

    /* debug */
    printf("length = %d\n", len);
    printf("reg_addr = %x\n", reg_addr);

    trans.flags = 0;
    trans.addr = reg_addr;
    trans.length = len * 8; // transaction length is in bits

    rc = spi_device_transmit(spi, &trans);
    if (rc < 0) {
        printf("[IoT-Labs] Error: transaction transmission failled\n");
        return rc;
    }

    memcpy(data, trans.rx_buffer, len);

    /* debug */
    for (int i = 0; i < len; i++)
        printf("rx_buffer[%d] = %d\n", i, ((uint8_t*)trans.rx_buffer)[i]);
    vTaskDelay(1000 / portTICK_RATE_MS);

    return rc;
}

int8_t
write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t rc;
    static struct spi_transaction_t trans;

    trans.tx_buffer = heap_caps_malloc(len, MALLOC_CAP_DMA);
    // FIXME do we need to allocate memory for rx_buffer for write stub?
    // Answer -> NO.
    // trans.rx_buffer = heap_caps_malloc(len, MALLOC_CAP_DMA);

    trans.flags = 0;
    trans.addr = reg_addr;
    trans.length = len * 8;

    memcpy(trans.tx_buffer, data, len);

    rc = spi_device_transmit(spi, &trans);
    if (rc < 0) {
        printf("[IoT-Labs] Error: transaction transmission failled\n");
        return rc;
    }

    return rc;
}

void
delay_ms(uint32_t period)
{
    vTaskDelay(period / portTICK_RATE_MS);
}

int8_t
_perform_sensor_readings(struct bme280_dev *dev, struct bme280_data *data)
{
    int8_t rc;

    rc = bme280_get_sensor_data(BME280_ALL, data, dev);

    /* debug */
    printf("temperature = %f DegC\n", (float)data->temperature / 100);
    printf("humidity = %f %%RH\n", (float)data->humidity / 1024);
    printf("pressure = %f Pa\n", (float)data->pressure / 256);

    return rc;
}

void
perform_sensor_readings(void *pvParameters)
{
    int8_t rc;
    struct bme280_dev *dev;
    struct bme280_data *data;

    dev = (struct bme280_dev*) pvParameters;
    data = (struct bme280_data*) malloc(sizeof(struct bme280_data));

    while (1) {
        /* get sensor reading */
        rc = ENOSYS;
        rc = _perform_sensor_readings(dev, data);

        /* struct for storing reading */
        struct a_reading reading;
        rc = make_a_reading(&reading, data);

        /* debug */
        // print_a_reading(&reading);

        /* save obtained reading in transmission queue */
        rc = transmission_enqueue(&reading);
        if (rc < 0) {
            // No need to break here! or TODO break after a given number of
            // trials
            printf("[IoT-Lab] Error while enqueuing a reading for\
                    transmission\n");
            goto end;
        }

        vTaskDelay(1000 / portTICK_RATE_MS);
    }

end:
    vTaskDelete(NULL);
}

void
setup_sensors(void *pvParameters)
{
    // TODO handle multiple sensors at a time
    // TODO perform, then, sensor fusion, etc.

    int8_t rc;
    struct sensors_config_t *cfg;
    cfg = (struct sensors_config_t*) pvParameters;

    // TODO iterate over provided devices, in case we implement multiple
    //      sensors handling!
    switch (cfg->device) {
    case BME280:
        rc = ENOSYS;
        if (rc < 0) {
            printf("[IoT-Labs] Error while initializing spi bus\n");
            break;
        }

        struct bme280_dev dev;
        rc = ENOSYS;
        if (rc < 0) {
            printf("[IoT-Labs] Error while initializing bme280\n");
            break;
        }

        /* each time a sensor is setup, trigger a sensor_readings task */
        xTaskCreate(&perform_sensor_readings, "bme280_readings", 2048,
                    (void*) &dev, 1, NULL);

        break;

    case DHT11:
        rc = ENOSYS;
        break;

    default:
        rc = ENOSYS;
        break;
    }

    vTaskDelete(NULL);
}
