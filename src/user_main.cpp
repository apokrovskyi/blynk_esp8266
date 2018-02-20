extern "C" {
  #include <ets_sys.h>
  #include <user_interface.h>
  #include <os_type.h>
  #include <osapi.h>
  #include <gpio.h>

  #include "driver/uart.h"

  #include "esp_missing.h"
}

#include "user_config.h"

#include "Serial.h"

#include "BlynkTimer.h"
BlynkTimer timer;

#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#define BLYNK_INFO_DEVICE "ESP8266"

#include "BlynkSimpleEsp8266_core.h"

void loop(void* arg)
{
    Blynk.run();
}

char ssid[] = "ssid";
char pass[] = "pass";
char auth[] = "token";

void ICACHE_FLASH_ATTR app_init()
{
    Serial.begin(115200);

    BLYNK_LOG("Build time: %s %s", __DATE__, __TIME__);
    BLYNK_LOG("SDK: %s", system_get_sdk_version());
    BLYNK_LOG("Chip ID: %08X", system_get_chip_id());

    Blynk.begin(auth, ssid, pass);
    
    timer.setInterval(100, loop);
}



