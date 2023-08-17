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

#include "set_mode.h"

void set_mode(WiFiServer &server, int &status, byte &mode, String &sensorName)
{
    File conf;
    conf = SD.open("sensconf.txt");
    char cMode;
    if(conf.available()) {
        cMode = conf.read();
        mode = cMode - '0';
        if(Serial) {
            Serial.print("Mode read from file: ");
            Serial.println(mode);
        }
        if(mode == 1) {
            while(conf.read() != '\n');
        }
    }

    switch(mode) {
    case 0:
        set_up_AP(status);
        break;
    case 1:
        if (!ENV.begin()) {
            if(Serial) Serial.println("Failed to initialize MKR ENV shield!");
            while (1);

        }

        if(!conf.available()) {
            if(Serial) Serial.println("File incomplete: could not read WIFI SSID!");
            while(1);
        }
        String strSSID = read_line(conf);
        const char* ssid = strSSID.c_str();

        if(!conf.available()) {
            if(Serial) Serial.println("File incomplete: could not read WIFI password!");
            while(1);
        }

        String strPW = read_line(conf);
        const char* pass = strPW.c_str();

        if(conf.available()) {
            sensorName = read_line(conf);
            if(Serial) {
                Serial.print("Sensor name from file: ");
                Serial.println(sensorName);
            }
        }
        if(Serial) Serial.println(ssid);
        set_sensor_mode(ssid, pass, status);

        break;
    }
    conf.close();
    server.begin();
    printWifiStatus();
}

String read_line(File &conf)
{
    String line = "";
    char c;
    c = conf.read();
    while(c != '\n') {
        line += c;
        c = conf.read();
        if(c == -1) {
            break;
        }
    }
    return line;
}

void set_sensor_mode(const char* ssid, const char* pass, int &status)
{

    if (!ENV.begin()) {
        if(Serial) Serial.println("Failed to initialize MKR ENV shield!");
        while (1);
    }
    connect_WiFi(ssid, pass, status);
    printWifiStatus();
}
