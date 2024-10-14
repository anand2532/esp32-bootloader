#include "bootloader_utility.h"
#include "esp_system.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_cpu.h"
#include "esp_chip_info.h"
#include <stdbool.h>

#define APP_START_ADDRESS 0x10000  // Example start address for the main application
#define APP_SIZE 0x100000          // Example size of the application (1MB)

static const char *TAG = "BOOTLOADER";

void bootloader_init(void)
{
    ESP_LOGI(TAG, "Bootloader initializing");

    // Initialize SPI flash
    esp_err_t ret = esp_flash_init(esp_flash_default_chip);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI flash");
        return;
    }

    // Print chip information
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "ESP32 chip with %d CPU cores, WiFi%s%s",
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
}

bool bootloader_verify_app(void)
{
    ESP_LOGI(TAG, "Verifying application");

    // For this example, we'll just check if the first byte is not 0xFF
    // (assuming 0xFF means erased flash)
    uint8_t first_byte;
    if (esp_flash_read(esp_flash_default_chip, &first_byte, APP_START_ADDRESS, 1) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read flash");
        return false;
    }
    
    bool is_valid = (first_byte != 0xFF);
    ESP_LOGI(TAG, "Application is %s", is_valid ? "valid" : "invalid");
    return is_valid;
}

void bootloader_jump_to_app(void)
{
    ESP_LOGI(TAG, "Jumping to application");

    // Disable interrupts
    portDISABLE_INTERRUPTS();

    // Set up the initial stack pointer for the app
    uint32_t sp = *(uint32_t*)APP_START_ADDRESS;

    // Get the entry point of the app
    uint32_t pc = *(uint32_t*)(APP_START_ADDRESS + 4);

    // Jump to the app's entry point
    // Note: This is a simplified version. A real bootloader would need to set up
    // more CPU state and might use a different method to jump.
    typedef void (*entry_point_t)(void);
    entry_point_t entry = (entry_point_t)pc;
    
    __asm__ volatile ("mov sp, %0" : : "r" (sp));
    entry();
}