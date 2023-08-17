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

#include "wifi.h"
#include "set_mode.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Configure Sensor</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Namen of WIFI: <input type="text" name="name"><br>

    WIFI password: <input type="text" name="pass"><br>

    Sensor name: <input type="text" name="sensor"><br>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void webserver_config_sensor(WiFiServer &server, int &wifi_status, byte &mode, String &sensorName);

