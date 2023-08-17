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
#include "led.h"

void setup_LED_pins()
{
    WiFiDrv::pinMode(25, OUTPUT);
    WiFiDrv::pinMode(26, OUTPUT);
    WiFiDrv::pinMode(27, OUTPUT);
    set_rgb(0, 0, 0);
}

void set_red()
{
    set_rgb(255, 0, 0);
}

void set_green()
{
    set_rgb(0, 255, 0);
}

void set_blue()
{
    set_rgb(0, 0, 255);
}

void set_yellow()
{
    set_rgb(255, 255, 0);
}

void set_rgb(byte red, byte green, byte blue)
{
    WiFiDrv::analogWrite(25, red); //RED
    WiFiDrv::analogWrite(26, green);   //GREEN
    WiFiDrv::analogWrite(27, blue);   //BLUE
}
