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

#include <utility/wifi_drv.h>

void setup_LED_pins();
void set_red();
void set_green();
void set_blue();
void set_yellow();
void set_rgb(byte red, byte green, byte blue);
