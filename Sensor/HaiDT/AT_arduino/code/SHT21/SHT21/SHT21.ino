#include <SHT21.h>  // include SHT21 library
#include <SoftwareSerial.h>


SHT21 sht;    // SHT21 variable
SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX



float temp;   // variable to store temperature
float humidity; // variable to store hemidity

void setup() {
  // put your setup code here, to run once:

  Wire.begin();    // begin Wire(I2C)
  UART1.begin(9600);
  while (!UART1);

  pinMode(PIN_PB4, OUTPUT);
}

void loop() {

  char s[100];
  digitalWrite(PIN_PB4, 1); delay(1000);
  digitalWrite(PIN_PB4, 0); delay(1000);

  
  // read temperature and huimid
  temp = sht.getTemperature();  // get temp from SHT
  humidity = sht.getHumidity(); // get temp from SHT


// data trantransmission
  UART1.print("Temp: ");      // print readings
  UART1.print(temp);
  UART1.print("\t Humidity: ");
  UART1.println(humidity);

}
