#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

// Dimensions the buffer that the task being created will use as its stack.
// NOTE:  This is the number of bytes the stack will hold, not the number of
// words as found in vanilla FreeRTOS.
#define STACK_SIZE 10000
#define cTime 1500 //ms

#define cTIME_BLE 20   // 0.1 * seconds
#define cTIME_SLEEP 20 // seconds

// Structure that will hold the TCB of the task being created.
StaticTask_t xTaskBuffer;

// Buffer that the task being created will use as its stack.  Note this is
// an array of StackType_t variables.  The size of StackType_t is dependent on
// the RTOS port.
StackType_t xStack[STACK_SIZE];

// extern void wifi_main();
// extern void deep_sleep_main();
// extern void udp_main();
// void vOtherFunction(void);

extern void deep_sleep_set_timer_wakeup(uint32_t u32TimeInMsP);
extern void ble_set_characteristic_response(uint16_t u16CharacteristicP, uint16_t u16ValueP);
extern void ble_main();

static TaskHandle_t xHandle = NULL;

static RTC_DATA_ATTR uint16_t u16CounterG = 0;

void app_main()
{
    // udp_main();
    // vOtherFunction();
    ble_main();

    ble_set_characteristic_response(0xFF01, u16CounterG++);

    //Wait ... seconds to run everything
    vTaskDelay(cTIME_BLE * 100 / portTICK_PERIOD_MS);

    //Go to sleep for ...
    deep_sleep_set_timer_wakeup(cTIME_SLEEP * 1000);
}

// Function that implements the task being created.
void vTaskPrint_500ms(void *pvParameters)
{
    const TickType_t xDelay = cTime / portTICK_PERIOD_MS;
    // The parameter value is expected to be 1 as 1 is passed in the
    // pvParameters value in the call to xTaskCreateStatic().

    for (;;)
    {
        printf("Task Printing on %dms.\n", cTime);
        printf("Stack Used: %d \n", uxTaskGetStackHighWaterMark(xHandle));
        vTaskDelay(xDelay);
    }
}

// Function that creates a task.
void vOtherFunction(void)
{
    // Create the task without using any dynamic memory allocation.
    xHandle = xTaskCreateStatic(
        vTaskPrint_500ms, // Function that implements the task.
        "NAME",           // Text name for the task.
        STACK_SIZE,       // Stack size in bytes, not words.
        (void *)1,        // Parameter passed into the task.
        tskIDLE_PRIORITY, // Priority at which the task is created.
        xStack,           // Array to use as the task's stack.
        &xTaskBuffer);    // Variable to hold the task's data structure.

    // puxStackBuffer and pxTaskBuffer were not NULL, so the task will have
    // been created, and xHandle will be the task's handle.  Use the handle
    // to suspend the task.
    // vTaskSuspend(xHandle);
}