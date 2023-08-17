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

#include "config_sensor.h"

void webserver_config_sensor(WiFiServer &server, int &wifi_status, byte &mode, String &sensorName)
{
    WiFiClient client;
    client = server.available();
    File conf;

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

                        client.print(index_html);

                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop:
                        break;
                    } else {    // if you got a newline, parse response and then clear currentLine:
                        if(currentLine.startsWith("GET")) {
                            int idx_http = currentLine.indexOf("HTTP");
                            int idx_start = currentLine.indexOf("?");
                            if(idx_start > -1) {
                                String request = currentLine.substring(idx_start, idx_http);
                                request.trim();
                                String inputs[3];
                                unsigned int lastFrom = 0;
                                for(int i=0; i<3; i++) {
                                    int start = request.indexOf("=", lastFrom + 1) + 1;
                                    int end = request.indexOf("&", lastFrom + 1);

                                    if(end == -1) {
                                        inputs[i] = request.substring(start);
                                    } else {
                                        inputs[i] = request.substring(start, end);
                                        lastFrom = end;
                                    }
                                }
                                if(inputs[0].length() > 0 && inputs[1].length() > 0 && inputs[2].length() > 0) {
                                    // WiFi.end();
                                    sensorName = inputs[2];
                                    const char *ssid = inputs[0].c_str();
                                    const char *pass = inputs[1].c_str();

                                    mode = 1;

                                    conf = SD.open("sensconf.txt", O_WRITE);
                                    if(conf.availableForWrite()) {
                                        conf.seek(0);
                                        conf.write('1');
                                        conf.write('\n');
                                        conf.write(ssid);
                                        conf.write('\n');
                                        conf.write(pass);
                                        conf.write('\n');
                                        conf.write(sensorName.c_str());
                                        conf.write('\n');
                                    } else {
                                        if(Serial) Serial.println("Cannot write to file!");
                                    }

                                    conf.close();
                                    if(Serial) Serial.println("Switching to sensor mode");
                                    set_sensor_mode(ssid, pass, wifi_status);
                                }
                            }

                        }
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // close the connection:
        client.stop();
        if(Serial) Serial.println("client disconnected");
    }
}

