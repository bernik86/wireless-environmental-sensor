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

#include <WiFiNINA.h>
#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>

#include "src/wifi.h"
#include "src/config_sensor.h"
#include "src/read_sensor_data.h"
#include "src/set_mode.h"
#include "src/led.h"

String sensorName = "ENV1";
int status = WL_IDLE_STATUS;   //connection status
byte mode = 0;  //0 ... AP mode, 1 ... sensor mode

WiFiServer server(80);           
WiFiClient client;

void setup()
{
    setup_LED_pins();

    Serial.begin(9600);
    // while (!Serial);

    set_rgb(0, 255, 255);

    if (!SD.begin(4)) {
        if(Serial) Serial.println("SD initialization failed!");
        set_red();
        while (1);
    }

    enable_WiFi();
    set_mode(server, status, mode, sensorName);
}

void loop()
{
    switch(mode) {
    case 0:
        webserver_config_sensor(server, status, mode, sensorName);
        break;
    case 1:
        webserver_sensor_data(server, sensorName);
        break;

    }
}
