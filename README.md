# Cloud-BMS-data-monitoring
Cloud based BMS data monitoring using IoT (Mosquitto)
This project uses BMS data like Battery Temp and Battery Voltages across each cell and upload to Mosquitto MQTT.
for this it uses arduino uno for gathering all data and node mcu esp8266 for providing internet conectivity.
data from arduino uno is transmitted via serial communication to the node mcu which then pulblishes it to Mosquitto.
