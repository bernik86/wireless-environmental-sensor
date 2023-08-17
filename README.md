# wireless-environmental-sensor

_Wireless environmental sensor_ is a program to read temperature, humidity, and pressure and to provide them via a simple web interface using the Arduino MKR 1010 WiFi board in combination with the MKR ENV Shield. The MKR ENV Shield also provides a SD port, which is used to store a configuration file on a SD card (in terms of memory usage this is a bit of an overkill, but it is more convenient for debugging and testing than storing the configuration in the non-volatile memory of the MKR 1010 WiFi board). The code first tries to read the configuration (WiFi SSID, WiFi password, and sensor name) from the SD card. In case no configuration file can be found (or if the first line of the file contains a zero), the MKR board creates a WiFi access point and starts a webserver. This webserver then provides a form which can be used to specify the WiFi SSID, the WiFi password, and a name for the sensor. After pressing the submit button, the MKR board connects to the specified WiFi and creates a webserver which provides the sensor name and the values for the temperature, humidity, and pressure.

The code uses the built-in RGB-LED on the MKR 1010 WiFi board for conveying some status information:
- Light blue: program started
- Dark blue: access point is up and running
- Green: webserver ready to provide sensor values
- Red: an error occurred (e.g., no SD card found) 

Note 1: so far, the IP addresses of the webservers are only provided via the serial port (support for providing the IP addresses via a small display or other means is planned for the future). However, the IP addresses for the access point (in my case: 192.168.4.1) and the webserver providing sensor values (in my case: 192.168.17.105) never changed. So, once one got the IP addresses, one should not need a serial connection to a computer anymore. 

Note 2: the name of the access point created to configure the sensor is called "sensor123". This is also the password.

Note 3: the MKR ENV Shield can be connected to the MKR 1010 WiFi board in a way, so that it sits directly on top (or below) the board. In this case, the temperature sensor puts out values that are several °C too high because of the heat produced by the microcontroller and the WiFi chip. Possible ways to correct this are currently investigated.

### Files
- `wireless-environmental-sensor.ino`: main file; contains setup and loop functions that are the entry points for the code running on the microcontroller of the MKR 1010 WiFi board.
- `src/*.cpp` and `src/*.h`: source files; contain the functions that do the actual work.

### Configuration file

At the beginning, the code attempts to read a file called `sensconf.txt` stored on the SD card. If the file does not exist or the first line contains a 0, the MKR board creates a WiFi access port and a webserver for configuring the WiFi. However, the file can also created or modified manually using computer with a SD card reader and a text editor. The format is the following:

- Line 1: `0` or `1`. A `0` signals the code to start a WiFi access point and the WiFi configuration webserver (useful mainly for debugging). In this case, no more data is read from the file. A `1` tells the code to read the configuration from file and, therefore, requires the following lines to present as well.
- Line 2: WiFi SSID
- Line 3: WiFi password
- Line 4: Name or identifier for the sensor
  
## Security

Security advisory 1: currently, security of the code is a bit weak as there is no encryption in the communication between the webserver and a client (only HTTP, no HTTPS yet). Furthermore, the WiFi credentials are stored in clear text on the SD card.

Security advisory 2: the strings input in the webserver for the WiFi configuration are not normalized or checked for malicious input (special characters may or may not cause problems either, but this is not well tested yet). 

## Compilation

### Requirements

#### Hardware

- Arduino MKR 1010 WiFi board and MKR ENV Shield (https://store.arduino.cc/collections/bundles-projects/products/environmental-monitor-bundle)
- Micro USB cable to connect the MKR 1010 WiFi board to a computer (only for uploading the code)

#### Software

- GNU Make (https://www.gnu.org/software/make/; only when using the `Makefile` included in this project)
- Arduino CLI (https://arduino.github.io/arduino-cli/0.33/installation/)
- Arduino SAMD core (1.8.13)
- Arduino Libraries:
  - WiFiNINA (1.8.14; https://www.arduino.cc/reference/en/libraries/wifinina/)
  - Arduino MKRENV (1.2.1; https://github.com/arduino-libraries/Arduino_MKRENV)
  - SD (1.2.4; https://www.arduino.cc/reference/en/libraries/sd/)

The SAMD core can be installed using the Arduino CLI using the following command:
```
arduino-cli core install arduino:samd
```

In a similar fashion, the required libraries can be installed using the Arduino CLI as well:
```
arduino-cli lib install WiFiNINA Arduino_MKRENV SD
```

### Building and uploading

In the makefile, there are 3 variables defined that may need to be adapted:
- `PORT`: the serial port to which the MKR board is connected.
- `BUILD`: directory in which the files generated during the compilation are stored.

To compile the code just run:
```
make
```

The compiled code can be uploaded to the board by running:
```
make upload
```

It is also possible to compile and upload the code with one command:
```
make install
```

To remove the files generated during the compilation, run:
```
make clean
```

## Credits

Some code used in this project is based on the code shown in the following tutorials:
- https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
- https://docs.arduino.cc/tutorials/mkr-wifi-1010/hosting-a-webserver
- https://docs.arduino.cc/tutorials/mkr-wifi-1010/web-server-ap-mode