/*
 * Copyright (c) 2023 bernik86.
 *
 * This file is part of arduino-mkr-wifi-environmental-sensor 
 * (see github).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * The code used in this file is based on the code shown in the following tutorials:
 * https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
 * https://docs.arduino.cc/tutorials/mkr-wifi-1010/hosting-a-webserver
 * https://docs.arduino.cc/tutorials/mkr-wifi-1010/web-server-ap-mode
 */

#include "wifi.h"
#include "led.h"

void printWifiStatus()
{
    if(Serial) {
        // print the SSID of the network you're attached to:
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        // print your board's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("IP Address: ");
        Serial.println(ip);

        Serial.print("To see this page in action, open a browser to http://");
        Serial.println(ip);
    }
}

void enable_WiFi()
{
    if (WiFi.status() == WL_NO_MODULE) {
        if(Serial) Serial.println("Communication with WiFi module failed!");
        set_red();
        while (true);
    }
}

void connect_WiFi(const char* ssid, const char* pass, int &status)
{
    while (status != WL_CONNECTED) {
        if(Serial) {
            Serial.print("Attempting to connect to SSID: ");
            Serial.println(ssid);
        }
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
    set_green();
}

void set_up_AP(int &status)
{
    if(Serial) Serial.print("Attempting to create AP");
    while(status != WL_AP_LISTENING) {
        status = WiFi.beginAP("SENSOR_123", "whatever123");
        delay(10000);
    }
    set_blue();
}
