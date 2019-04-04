# Pi-Sensors
Use a Raspberry Pi as a data processor &amp; grapher for external esp8266 chips connected to dht-11 temperature sensors and hub75 32x16 led matrix displays

## Setup
Run:
```
curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
echo "deb https://repos.influxdata.com/debian stretch stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
sudo apt update
sudo apt install influxdb chronograf -y
sudo systemctl enable influxdb
sudo systemctl start influxdb 
```
## Lib Dependencies
- [General Sensors](https://github.com/adafruit/Adafruit_Sensor)
- [DHT Sensors](https://github.com/adafruit/DHT-sensor-library)
- [ESP8266 InfluxDB](https://github.com/tobiasschuerg/ESP8266_Influx_DB)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [PxMatrix](https://github.com/2dom/PxMatrix)
- [Time](https://github.com/PaulStoffregen/Time)
