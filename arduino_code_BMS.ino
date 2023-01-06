//Serial Communication lib and variables
#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);
String data;

// voltmeter variable declaration
int value1 = 0;
float voltage1;
int value2 = 0;
float voltage2;
int value3 = 0;
float voltage3;
int value4 = 0;
float voltage4;
float R1 = 39000.0;
float R2 = 8800.0;

// Thermister Variables

//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------
#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ
//Variables
float RT, VR, ln, TX, T0, VRT;



void setup(){
//Serial Communication
espSerial.begin(115200);
Serial.begin(9600);
 T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
delay(2000);

}


void loop()
{
 // voltmeter readings start
 value1 = analogRead(A0);
  float temp = (value1 * 5.0) / 1024.0; 
  voltage1 = temp / (R2/(R1+R2));
  delay(500);

   value2 = analogRead(A1);
  float temp2 = (value2 * 5.0) / 1024.0; 
  voltage2 = temp2 / (R2/(R1+R2));
  delay(500);


 value3 = analogRead(A2);
  float temp3 = (value3 * 5.0) / 1024.0; 
  voltage3 = temp3 / (R2/(R1+R2));
  delay(500);


 value4 = analogRead(A3);
  float temp4 = (value4 * 5.0) / 1024.0; 
  voltage4 = temp4 / (R2/(R1+R2));
  delay(500);
  // voltmeter readings end

  //Temperature Reading start
VRT = analogRead(A4);              //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius

  //Serial.print("Temperature:");
// Serial.print("\t");
 //Serial.print(TX);
  //Serial.print("C\t\t");
  //Serial.print(TX + 273.15);        //Conversion to Kelvin
  //Serial.print("K\t\t");
  //Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
  //Serial.println("F");
  //delay(500);
  // Temperature reading end
  

  
//Sending data to Node MCU
data =String(voltage1)+String(" , ")+String(voltage2)+String(" , ")+String(voltage3)+String(" , ")+String(voltage4)+String(" , ")+String(TX);
espSerial.println(data);
delay(1000);
}
