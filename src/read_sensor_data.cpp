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
 * The webserver code used in this file is based on the code shown in the following tutorials:
 * https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
 * https://docs.arduino.cc/tutorials/mkr-wifi-1010/hosting-a-webserver
 * https://docs.arduino.cc/tutorials/mkr-wifi-1010/web-server-ap-mode
 */

#include "read_sensor_data.h"

void webserver_sensor_data(WiFiServer &server, String sensorName)
{
    WiFiClient client;
    client = server.available();

    if (client) {
        if(Serial) Serial.println("new client");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n') {                    // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {

                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("Sensor name: ");
                        client.print(sensorName);
                        client.print("<br>");
                        client.print("Temperature [Celsius]: ");
                        client.print(ENV.readTemperature());
                        client.print("<br>");
                        client.print("Humidity [%]: ");
                        client.print(ENV.readHumidity());
                        client.print("<br>");
                        client.print("Pressure [mBar]: ");
                        client.print(ENV.readPressure(MILLIBAR));

                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop:
                        break;
                    } else {    // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        client.stop();
        if(Serial) Serial.println("client disconnected");
    }
}
