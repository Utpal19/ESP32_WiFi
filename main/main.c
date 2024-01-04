/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

/**
 * Application entry point
*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"
#include "ssd1306_i2c.h"
#include "oledDIsp.h"

#include "nvs_flash.h"
#include "wifi_app.h"
#include "wifi_simple.h"

#include "extern.h"


#define TAG "SSD1306"
SSD1306_t dev;

/*
TaskHandle_t oledTaskHandle;
SemaphoreHandle_t xMutex;

#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE sizeof(int)
QueueHandle_t xQueue;

// SSD1306_t dev;

/// @brief 
/// @param parameter 
/// @return 
void* oledTask(void* parameter)
{
    SSD1306_t* _dev = (SSD1306_t* )parameter;
    // static uint16_t i = 0;
    char sBuff[20] = "";
    int sendData = 0;

    printf("*** Address of parameter in oledTaask(): %p\n", (uint32_t* ) parameter);
    printf("*** Address of dev in oledTask(): %p\n", _dev);

    ssd1306_clear_screen(_dev, false);
	ssd1306_contrast(_dev, 0xff);

    while(1)
    {
        if(xQueueSend(xQueue, &sendData, portMAX_DELAY) == pdPASS) {
            // printf("Task1: Sent %d to the queue\n", sendData);
        }
        sprintf(sBuff, "Count: %u", sendData);
        // Acquire the mutex. Wait forever until it's available.
        // if (xSemaphoreTake(xMutex, portMAX_DELAY)) 
        {
            ssd1306_display_text(_dev, 0, "SSD1306 128x32", 14, false);
            ssd1306_display_text(_dev, 1, "Hello World!!", 13, false);
            ssd1306_display_text(_dev, 3, sBuff, strlen(sBuff), true);
            // ssd1306_clear_line(_dev, 2, true);
            // ssd1306_clear_line(_dev, 3, true);
            // xSemaphoreGive(xMutex);
        }
        sendData++;
        vTaskDelay(pdMS_TO_TICKS(1000));

    }
}


void Task2(void *pvParameters) {
    int receiveData;

    while (1) {
        if(xQueueReceive(xQueue, &receiveData, portMAX_DELAY) == pdPASS) {
            printf("Task2: Received %d from the queue\n", receiveData);
        }
    }
}
*/

void chipInfo(void)
{
    // Print chip information
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    // for (int i = 10; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     // vTaskDelay(pdMS_TO_TICKS(1000));
    // }

}

// wifi_app_start

void app_main(void)
{
    BaseType_t  status;

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "INTERFACE is i2c");
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);

	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    printf("*** Address of dev in main(): %p\n", &dev);
    chipInfo();
    o_disp_test(&dev);
    // wifi_app_start();
    wifi_connection();

/*
	vTaskDelay(5000 / portTICK_PERIOD_MS);

    // Create the mutex
    // xMutex = xSemaphoreCreateMutex();

    xQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);

    if(xQueue == NULL) {
        printf("Failed to create queue\n");
    }

    //  if (xMutex != NULL)
     {
        status = xTaskCreate(oledTask, "OLED DISPLAY TASK", 1024 * 4, (void* )&dev, 1, &oledTaskHandle);
        configASSERT(status == pdPASS);

        xTaskCreate(Task2, "Task2", 1024 * 2, NULL, 1, NULL);

     }

    // printf("Restarting device now.\n");
    // fflush(stdout);
    // esp_restart();

    */
}
