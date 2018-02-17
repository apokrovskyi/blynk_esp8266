/**
 * @file       BlynkSimpleEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSimpleEsp8266_h
#define BlynkSimpleEsp8266_h

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#define HIGH 1
#define LOW 0

typedef enum{
	INPUT,
	OUTPUT
}pinmode;

void digitalWrite(int pin, int value){
	GPIO_OUTPUT_SET(pin, (value==1));
}

void analogWrite(int pin, int value);

int digitalRead(int pin){
	return GPIO_INPUT_GET(pin);
}

int analogRead(int pin){
	return system_adc_read();
}

void pinMode(int pin, pinmode mode){
	if(mode==INPUT){
		gpio_output_set(0, 0, 0, 1<<pin);
	}
	else
	{
		gpio_output_set(0, 0, 1<<pin, 0);
	}
}

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <ESP8266WiFi.h>


static void ICACHE_FLASH_ATTR wifi_cb(System_Event_t *event)
{
	if(event->event==EVENT_STAMODE_GOT_IP)
    {
		BLYNK_LOG1(BLYNK_F("Connected to WiFi"));

		IPAddress myip = WiFi.localIP();
		BLYNK_LOG_IP("IP: ", myip);
	}
}

class BlynkWifi
    : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
public:
    BlynkWifi(BlynkArduinoClient& transp)
        : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG2(BLYNK_F("Connecting to "), ssid);
        WiFi.mode(STATION_MODE);
        if (pass && strlen(pass)) {
            WiFi.begin(ssid, pass);
        } else {
            WiFi.begin(ssid);
        }

        wifi_set_event_handler_cb(wifi_cb);
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
        config(auth, domain, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
        config(auth, ip, port);
    }

};

static Client _blynkESPClient;
static BlynkArduinoClient _blynkTransport(_blynkESPClient);
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
