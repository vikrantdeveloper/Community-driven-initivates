#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "smain.h"


void blink_led(void *pvParamaters)
{
    // select the GPIO
    gpio_pad_select_gpio(BLINK_GPIO);
    // select the direction 
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) 
    {
        ESP_LOGE("LEDBLINK", "Turning off the led");   // print on the console
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);        // LED delay
	    ESP_LOGI("LEDBLINK", "Turning on the led");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);       // Delay to switch the task
        int task = xPortGetCoreID();                // print which core does the task is running
        printf("the task id for blink led is = %d\n",task);
         
    }
}

void hello_world(void *pvParameters)
{
    while(1)
    {
        ESP_LOGI("ESP32_RTOS","Getting started with freeRTOS\n");
        int task = xPortGetCoreID();
        printf("The task id for hello world is = %d\n",task);
        vTaskDelay(500 / portTICK_PERIOD_MS);     // delay to switch the task 
    }
}

void app_main(void)    
{
    #if defined (SINGLECORE)
        xTaskCreate(&blink_led,"blink_led",2048,NULL,3,NULL);
        xTaskCreate(&hello_world,"hello_world",2048,NULL,5,NULL);
    #elif (DUALCORE)   
        static uint8_t core = 0;
        for(uint8_t i = 0; i<MAXCORE; i++)
        {
            switch (core)
            {
            case FIRSTCORE:
                xTaskCreatePinnedToCore(&hello_world, "hello_world", 2048, NULL, 0, NULL, 0);
                core = SECONDCORE;
                break;  
            case SECONDCORE:
                xTaskCreatePinnedToCore(&blink_led, "blink_led", 2048, NULL, 0, NULL, 1);
                break;
            default:
                break;
            }
        }
    #endif  
}

