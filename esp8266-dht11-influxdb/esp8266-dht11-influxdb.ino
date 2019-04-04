#include <ESP8266WiFi.h>
#include <InfluxDb.h>
#include <DHT.h>

#define INFLUXDB_HOST "192.168.4.1"
#define INFLUXDB_PORT "8888"
#define INFLUXDB_DATABASE "sensors"
String device = "esp2";
String sensor = "dht11";

//SSID and PW of Network
const char* ssid = "TempNet";
const char* password = "networkforthetemperaturesensors";

#define DHTTYPE DHT11   // DHT 11
// DHT Sensor
const int DHTPin = 4; //GPIO4 is pin D2 on the nodemcu esp8266
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

Influxdb influx(INFLUXDB_HOST);

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  //Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  
  influx.setDb(INFLUXDB_DATABASE);
}

void loop () {
  float tempC, tempF, hum;
  //Read temperature as Fahrenheit (isFahrenheit = true)
  tempF = float(dht.readTemperature(true));
  tempC = float(dht.readTemperature());
  hum = float(dht.readHumidity());

  InfluxData fahrenheit("temperature");
  fahrenheit.addTag("device", device);
  fahrenheit.addTag("sensor", sensor);
  fahrenheit.addValue("fahrenheit", tempF);
  influx.prepare(fahrenheit);

  InfluxData celcius("temperature");
  celcius.addTag("device", device);
  celcius.addTag("sensor", sensor);
  celcius.addValue("celcius", tempC);
  influx.prepare(celcius);

  InfluxData humidity("humidity");
  humidity.addTag("device", device);
  humidity.addTag("sensor", sensor);
  humidity.addValue("percent", hum);
  influx.prepare(humidity);

  if(!influx.write()) {
    Serial.println("Write fail");
  } else {
    Serial.println("Write successful");
  }

  delay(2000);
}
