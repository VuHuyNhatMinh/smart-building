
#include <DS3231.h>
#include <SoftwareSerial.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX

void setup()
{
  // Setup Serial connection
  UART1.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();

  // The following lines can be uncommented to set the date and time
  //  rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(22, 35, 0);     // Set the time to 22:35:00 (24hr format)
  //  rtc.setDate(3, 19, 2022);   // Set the date to January 1st, 2014
}

void loop()
{
  // Send Day-of-Week
  UART1.print(rtc.getDOWStr());
  UART1.print(" ");

  // Send date
  UART1.print(rtc.getDateStr());
  UART1.print(" -- ");

  // Send time
  UART1.println(rtc.getTimeStr());

  // Wait one second before repeating :)
  delay (1000);




}
