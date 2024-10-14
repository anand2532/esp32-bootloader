#include <stdio.h>
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "bootloader_utility.h"

void app_main(void)
{
    printf("ESP32 Bootloader Starting\n");

    // Initialize bootloader
    bootloader_init();

    // Check for valid application
    if (bootloader_verify_app()) {
        printf("Valid application found. Booting...\n");
        bootloader_jump_to_app();
    } else {
        printf("No valid application found. Halting.\n");
        while(1) {
            // Infinite loop - in a real bootloader, you might implement
            // recovery logic or wait for a new application to be flashed
        }
    }
}