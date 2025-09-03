#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LOG_MESSAGE(msg) send_log_message(msg, __FILE__, __LINE__)
#define MAX_LOG_MESSAGE_LENGTH 256

#define BUILTIN_LED_PIN GPIO_NUM_2

QueueHandle_t log_queue;

typedef struct {
    char message[MAX_LOG_MESSAGE_LENGTH];
    char file[64];
    int line;
} LogMessage;

void send_log_message(const char* msg, const char* file, int line) {
    LogMessage log_msg;
    snprintf(log_msg.message, sizeof(log_msg.message), "%s", msg);
    snprintf(log_msg.file, sizeof(log_msg.file), "%s", file);
    log_msg.line = line;

    if (log_queue != NULL) {
        // Wysyłanie do kolejki.
        // portMAX_DELAY oznacza czekanie w nieskończoność, jeśli kolejka jest pełna.
        xQueueSend(log_queue, &log_msg, portMAX_DELAY);
    }
}

void logger_task(void* argument) {
    LogMessage received_message;

    while (1) {
        if (xQueueReceive(log_queue, &received_message, portMAX_DELAY)) {
            // Oczekiwanie na wiadomość w kolejce
            // portMAX_DELAY oznacza, że zadanie będzie spać, dopóki wiadomość nie nadejdzie
            printf("[%s:%d]: %s\n", received_message.file, received_message.line, received_message.message);
        }
    }
}

void led_blinking_task(void* argument) {

    // Konfiguracja pinu GPIO jako wyjścia
    gpio_set_direction(BUILTIN_LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        // Włącz diodę LED.
        gpio_set_level(BUILTIN_LED_PIN, 1);
        LOG_MESSAGE("LED is ON");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Poczekaj 1 sekundę.

        // Wyłącz diodę LED.
        gpio_set_level(BUILTIN_LED_PIN, 0);
        LOG_MESSAGE("LED is OFF");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Poczekaj 1 sekundę.
    }
}

void app_main(void)
{
    log_queue = xQueueCreate(10, sizeof(LogMessage));
    if (log_queue == NULL) {
        printf("ERROR: Failed to create log queue\n");
        return;
    }

    // Parametry xTaskCreate:
    // 1. Nazwa funkcji zadania (wskaźnik na funkcję)
    // 2. Nazwa zadania (dla debugowania)
    // 3. Rozmiar stosu (w słowach, np. 2048 to 8KB na ESP32)
    // 4. Parametr przekazywany do zadania (tutaj NULL, bo nic nie przekazujemy)
    // 5. Priorytet zadania (im wyższy numer, tym wyższy priorytet)
    // 6. Uchwyt zadania (NULL, bo nie będziemy się do niego odwoływać)
    xTaskCreate(led_blinking_task, "LED_Blinking_Task", 2048, NULL, 5, NULL);
    xTaskCreate(logger_task, "Logger_Task", 2048, NULL, 5, NULL);

    // Po utworzeniu zadania, app_main() może zakończyć działanie
    // lub przełączyć się na inne zadanie.
    // W tym przykładzie, po prostu pozwalamy FreeRTOSowi na zarządzanie zadaniami.
}