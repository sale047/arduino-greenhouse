#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#define DHTPIN 2 // Digitalni pin koji se koristi
#define DHTTYPE DHT22 // tip DHT-a DHT22
#define RE_SVETLO 6
#define RE_VENT 7
#define RE_VODA 8
#define RE_GREJ 9
const int read = A3; //Sensor A3 pin na Arduino pin A1
int value;
int sensor_pin = A0;
int vl_zemlje;
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
void setup() {
 // Inicijalizacija Arduino data pinova za OUTPUT
 pinMode(RE_SVETLO, OUTPUT);
 pinMode(RE_VENT, OUTPUT);
 pinMode(RE_VODA, OUTPUT);
 pinMode(RE_GREJ, OUTPUT);
 digitalWrite(RE_SVETLO,HIGH);
 digitalWrite(RE_VENT,HIGH);
 digitalWrite(RE_VODA,HIGH);
 digitalWrite(RE_GREJ,HIGH);
 Serial.begin(9600);
 dht.begin();
 lightMeter.begin();
 Serial.println("Running...");
 Serial.println("Reading From the Sensor ...");
 delay(2000);
}
void loop() {

 /////////////// DHT///////////////////
 // 2sek pauza
 // citanje traje 250ms!
 float hum = dht.readHumidity();
 // citanje temperature u C
 float temp = dht.readTemperature();
 Serial.print(" Vlaznost vazduha: ");
 Serial.print(hum);
 Serial.print(" % ");
22
 Serial.print(" Temperatura: ");
 Serial.print(temp);
 Serial.print(" *C ");
 /////////////BH1750///////////////////
uint16_t lux = lightMeter.readLightLevel();
 Serial.print(" Light: ");
 Serial.print(lux);
 Serial.print(" lx");

 ////////////////////FC 28 SENZOR ////////
 vl_zemlje= analogRead(sensor_pin);
 vl_zemlje = map(vl_zemlje,1050,250,0,100);
 Serial.print(" Vlaznost zemlje : ");
 Serial.print(vl_zemlje);
 Serial.println("%");

 //////////////////////////SENZOR NIVOA VODE/////////////////////////
 value = analogRead(A3); // Citanje sa analognog pina
 if (value<=480){
 Serial.println(" Water level: Empty!");
 }
 else if (value>480 && value<=530){
 Serial.println(" Water level: Low");
 }
 else if (value>530 && value<=615){
 Serial.println(" Water level: 10%");
 }
 else if (value>615 && value<=660){
 Serial.println(" Water level: 20%");
 }
 else if (value>660 && value<=680){
 Serial.println(" Water level: 40%");
 }
 else if (value>680 && value<=690){
 Serial.println(" Water level: 50%");
 }
 else if (value>690 && value<=700){
 Serial.println(" Water level: 60%");
 }
 else if (value>700 && value<=705){
 Serial.println(" Water level: 80%");
 }
 else if (value>705){
 Serial.println(" Water level: Full");
 }

 /////////////////////RELEJI///////////////////////////////////
 if (lux<=5)
 digitalWrite(RE_SVETLO,LOW); // Turns ON Relays 1
 else
23
 digitalWrite(RE_SVETLO,HIGH); // Turns Relay Off

 if ((temp>35)||(hum>75))
 digitalWrite(RE_VENT,LOW); // Turns ON Relays 2
 else
 digitalWrite(RE_VENT,HIGH); // Turns Relay Off
 if (vl_zemlje<10)
 digitalWrite(RE_VODA,LOW); // Turns ON Relays 3
 else
 digitalWrite(RE_VODA,HIGH); // Turns Relay Off
 if (temp<20)
 digitalWrite(RE_GREJ,LOW); // Turns ON Relays 4
 else
 digitalWrite(RE_GREJ,HIGH); // Turns Relay Off
delay
