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

void printWifiStatus();
void enable_WiFi();
void connect_WiFi(const char* ssid, const char* pass, int &status);
void set_up_AP(int &status);

