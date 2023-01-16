// IMPORT LIBRARY
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <Ticker.h>

//DEFINES VALUES
#define debug 2 //debug via serial.print, bisa 0 SAMPAI 2, KALAU 0 TIDAK ADA SERIAL PRINT SAMA SEKALIx.
#define relay_gnd D5
#define relay_vcc D6

//untuk lebar lcd
#define LCDCOLUMN 20
#define LCDROW 2
#define LCDI2CADDRESS 0x27  //alamat I2C module, antara 0x3C atau 0x27

//buat mqtt
#define clientId "EQdetect"
#define namaMesin "EQdetect"

#define wifiDHCP 1    //0 = static ip; 1 = DHCP;

//CONSTANT
const char Sen_ID[] = namaMesin;

//GLOBAL VARIABLE
unsigned long lastReconnectAttempt;
uint8_t statusWifi, statusMqtt, statusPos, eqCount = 0;
bool situation = false;

//IP CONFIG
//const char* ssid = "Base Camp X Tensi";
//const char* password = "janganlupa1";
//IPAddress staticIP(11, 11, 11, 98); //ESP static ip kalo perlu static
//IPAddress gateway(11, 11, 11, 1);    //Gateway
//IPAddress subnet(255, 255, 255, 0);

//const char* ssid = "bye kuota";
//const char* password = "password";
//IPAddress staticIP(192, 168, 255, 21); //ESP static ip kalo perlu static
//IPAddress gateway(192, 168, 255, 1);    //Gateway
//IPAddress subnet(255, 255, 255, 202);

const char* ssid = "okedeh";
const char* password = "password";
IPAddress staticIP(192, 168, 255, 21); //ESP static ip kalo perlu static
IPAddress gateway(192, 168, 255, 1);    //Gateway
IPAddress subnet(255, 255, 255, 202);

//MQTT
//const char* mqtt_server = "11.11.11.49";
//const char* mqtt_server = "192.168.255.190";
const char* mqtt_server = "192.168.137.1";

WiFiClient espClient;
PubSubClient client(mqtt_server, 1883, espClient);

//LCD
LiquidCrystal_I2C lcd(LCDI2CADDRESS, LCDCOLUMN, LCDROW);

//ADXL345 SENSOR
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

//TICKER SELALU CEK UNTUK WIFI
Ticker tickWifi;

void setup()
{
  //SERIAL COMM INIT
  Serial.begin(115200);

  //LCD INIT
  lcdInit();

  //WIFI INIT
  SetupWifi();
  //WIFI TICKER ATTACH CEK WIFI
  tickWifi.attach(2, checkWifi);


  //MQTT INIT
  mqttInit();
  MqttConnect();

  //RELAY INIT
  relayInit();

  //ADXL345 INIT
  adxlInit();
}

void loop()
{
  // MqttConnect();
  //untuk mqtt -> mengirim data ke server

  //  checkWifi();
  client.loop(); //LOOP MQTT

  // mengambil data sensor dan menjadikannya skala richter
  float sr_val = getSR(50);
  SendDataToServer(sr_val);

  situation = isDanger(sr_val);
  relay(situation);

  if (!situation)
  {
    lcd.setCursor(0, 1);
    lcd.print("SR: ");
    lcd.setCursor(3, 1);
    lcd.print(sr_val);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("!!!Danger!!!");
    lcd.setCursor(0, 1);
    lcd.print("ADA GEMPA >5 SR");
  }

#if debug > 0
  Serial.print("RIchter Scale: ");
  Serial.println(sr_val);
  Serial.print("Status Situasi: ");
  Serial.println(situation);
  Serial.print("Status Mqtt: ");
  Serial.println(statusMqtt);
#endif

  delay(500);
}
