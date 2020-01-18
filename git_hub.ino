//OLED LIBRARY INITALIZATION //
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SSD1306_LCDHEIGHT 32

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// DHT_11 & SOILMOSITURE //
#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
float humidity;
float temperature;
float soilmositure;//stores converts 1024 to %
float soilmositure_1;//paddy
float soilmositure_2;//cotton

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
const char* ssid = "Guest";// 
const char* password = "apple@123";
char server[] = "168.168.14.57";   //eg: 192.168.0.2228
WiFiClient client;    
void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  pinMode(D8,OUTPUT); //pump
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
//server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  humidity =dht.readHumidity ();
  temperature = dht.readTemperature(); 
  soilmositure_1 =analogRead(A0);//paddy
  soilmositure = (100-( (soilmositure_1/1024.00) * 100 ));
  soilmositure_2 =random(1,10);//cotton
  if(soilmositure <=10)
  {
    digitalWrite(D8,1);
  }
  else 
  {
     digitalWrite(D8,0);
  }
  //OLED//
  // initialize and clear display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    //display a line of text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    //oled_dht11//
    display.setCursor(0,0);
    display.print("&humidity=");
    display.print(humidity);
    //oled_soilmositure//
    display.setCursor(0,10);
    display.print("&soilmositure=");
    display.print(soilmositure);
    //oled_soilmositure_2//
    display.setCursor(0,20);
    display.print("&soilmositure_2=");
    display.print(soilmositure_2);
    //oled_temperature//
    display.setCursor(0,30);
    display.print("&tempurature=");
    display.print(temperature);
    delay(3000);
   //controlpump();
  Sending_To_phpmyadmindatabase(); 
  delay(3000); // interval
}
 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server,80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /SIH/dht1.php?sih_2020=");
    client.print("GET /SIH/dht1.php?sih_2020=");     //YOUR URL
    //client_serial_display//
    client.print("&humidity=");
    Serial.println("&humidity=");
    Serial.println(humidity);
    client.print(humidity);
    //client_serial_display//
    client.print("&soilmositure=");
    Serial.println("&soilmositure=");
    Serial.println(soilmositure);
    client.print(soilmositure);
    //client_serial_display//
    client.print("&soilmositure_2=");
    Serial.println("&soilmositure_2=");
    Serial.println(soilmositure_2);
    client.print(soilmositure_2);
    //client_serial_display//
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperature);
    Serial.println(temperature);
    client.print("http://localhost/phpmyadmin/sql.php?server=1&db=av_2030&table=sih_2020&pos=0 ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 168.168.14.57 ");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
