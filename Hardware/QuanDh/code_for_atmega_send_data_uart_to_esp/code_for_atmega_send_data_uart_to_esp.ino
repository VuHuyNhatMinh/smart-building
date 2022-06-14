#include <GP2YDustSensor.h>
#include <SoftwareSerial.h>
#include <BH1750FVI.h>
#include <BH1750.h>
#include <Wire.h>

// uint16_t Light_Intensity=0;
 // Call the function 
// BH1750FVI LightSensor;
BH1750 lightMeter;



//int dustPin=0;
#define dustPin PIN_PA1     //chân đọc dữ liệu analog đầu vào
//int ledPower=2;
#define ledPower PIN_PF1    //chân cấp led mẫu cho cảm biến
int delayTime=280;
int delayTime2=40;
float offTime=9680; //10000-280-40

int dustVal=0;
char s[32];
float voltage = 0;
float dustdensity = 0;






 

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
void setup() {
  // put your setup code here, to run once:
  UART1.begin(9600);
  while (!UART1);

  pinMode(PIN_PB4, OUTPUT);
  Serial.begin(9600);

  
//  LightSensor.begin();
//  LightSensor.SetAddress(Device_Address_H); //Address 0x5C
//  LightSensor.SetMode(Continuous_H_resolution_Mode);
  Wire.begin();
  lightMeter.begin();


  pinMode(ledPower,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime);
  dustVal=analogRead(dustPin); // read the dust value
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);
  
  voltage = dustVal*0.0049;//dustval*5/1024
  dustdensity = 0.172*voltage-0.1;
  
  if (dustdensity < 0 )
  dustdensity = 0;
  if (dustdensity > 0.5)
  dustdensity = 0.5;
  String dataString = "";
  dataString += dtostrf(voltage, 9, 4, s);
  dataString += "V,";
  dataString += dtostrf(dustdensity*1000.0, 5, 2, s);
  dataString += "ug/m3";

  if (UART1.available() > 0) {
    UART1.print("Dust: ");
    UART1.print(dataString);
  }

  delay(1000);









  

//  Light_Intensity = LightSensor.GetLightIntensity();
float lux = lightMeter.readLightLevel();
  
  if (UART1.available() > 0) {
    UART1.print("Light: ");
    UART1.print(lux);
  }

  delay(1000);




  
  
//  if (UART1.available() > 0) {
//    UART1.println("HELLO");
//  }

  
  if (UART1.available() > 0) {
    UART1.print("YEAR3");
  }
  delay(1000);





  

  digitalWrite(PIN_PB4, 1); delay(1000);
  digitalWrite(PIN_PB4, 0); delay(1000);


  digitalWrite(PIN_PB4, 1); delay(1000);
  digitalWrite(PIN_PB4, 0); delay(1000);
}
