/*
 * ESP8266WiFi.h
 *
 *  Created on: 07.07.2017
 *      Author: andrew
 */

#ifndef ESP8266WIFI_H_
#define ESP8266WIFI_H_

#include "IPAddress.h"
#include "user_interface.h"
#include "Serial.h"

class ESP8266WiFi{
public:
	void mode(uint8 opmode)
	{
		wifi_set_opmode(opmode);
	}

	void begin(const char* ssid, const char* pass = "")
	{
		struct station_config stconfig;
		wifi_station_disconnect();
		wifi_station_dhcpc_stop();

		if(wifi_station_get_config(&stconfig))
		{
			os_memset(stconfig.ssid, 0, sizeof(stconfig.ssid));
			os_memset(stconfig.password, 0, sizeof(stconfig.password));
			os_sprintf((char*)stconfig.ssid, "%s", ssid);
			os_sprintf((char*)stconfig.password, "%s", pass);
			wifi_station_set_config(&stconfig);
		}


		wifi_station_connect();
		wifi_station_dhcpc_start();
	}

	uint8 status()
	{
		return wifi_station_get_connect_status();
	}

	IPAddress localIP()
	{
		struct ip_info result;
		wifi_get_ip_info(STATION_IF, &result);
		return result.ip.addr;
	}
};

ESP8266WiFi WiFi;

#endif /* ESP8266WIFI_H_ */
