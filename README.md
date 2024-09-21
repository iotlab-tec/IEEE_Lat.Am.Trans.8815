# IEEE_Lat.Am.Trans.8815
This repository contains the code for the article **_"Implementation of an adaptive data logging algorithm in low-cost IoT nodes for supply chain transport monitoring"_** published in **IEEE Latin America Transactions (ISSN: 1548-0992)**.

The files description is as follows:

+**WebPage.html:** The code provided is dashboard displaying acquired data from the client to the user, automatically refreshing every 30 s. It was created with HTML, CSS, and JavaScript. 
  Main sections:
    1. Displays temperature and humidity readings from the DHT sensor, along with latitude and longitude from the GPS.
    2. Historic plots show the latest values for temperature and humidity, with time on the horizontal axis and data value on the vertical axis. The vertical axis scale adjusts based on the one hundred data points plotted during each refresh.
    3. Presents the date and time obtained from the GPS.
    4. Utilizes the Google Maps API to show the location based on latitude and longitude under Geographical Coordinates.
    5. Includes a menu bar for potential future development, currently serving a decorative purpose.

+**IoT_ESP8266_GPS_TempHumidity_DataLogger.ino:** The code provided is an Arduino sketch that integrates a GPS sensor, a DHT sensor (for temperature and humidity), and an ESP8266 Wi-Fi module to collect and transmit environmental and location data to a server.
  Libraries Used:
    ESP8266WiFi.h: Handles the Wi-Fi connection using the ESP8266 module.
    SoftwareSerial.h: Enables serial communication on digital pins to interact with the GPS module.
    TinyGPS.h: Handles the parsing and extraction of GPS data (latitude, longitude, time).
    DHT.h: Handles communication with a DHT11 sensor to measure temperature and humidity.
  Key Components:
    1. DHT Sensor Setup: The DHT11 sensor is used for temperature and humidity readings. It is connected to a specified pin (DHTPIN 0) on the microcontroller.
    2. GPS Setup: The TinyGPS library is used to handle GPS data. A SoftwareSerial instance is created to interface with the GPS module through pins 4 and 5.
    3. Wi-Fi Setup: The sketch sets the ESP8266 in station mode and connects it to a Wi-Fi network using provided SSID and password.
    4. Main Functionality: The loop() function collects temperature and humidity data from the DHT sensor. It also gathers latitude, longitude, and date/time data from the GPS module. Once the data is collected, the ESP8266 sends this information to a remote server through an HTTP GET request. The data is passed as URL parameters, such as temperature, humidity, latitude, longitude, date, and time.
    5. Supporting Functions: 
      smartdelay(): This function ensures the GPS module continues to receive and process data during the delay periods.
      print_date(): This function extracts and formats the date and time information from the GPS module.

