#ifndef BOOTLOADER_UTILITY_H
#define BOOTLOADER_UTILITY_H

#include <stdbool.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Initialize bootloader components
void bootloader_init(void);

// Verify if a valid application is present
bool bootloader_verify_app(void);

// Jump to the main application
void bootloader_jump_to_app(void);

#endif // BOOTLOADER_UTILITY_H