//Libary til real-time-clock module
#include <DS3231.h>

DS3231 rtc(SDA, SCL);
 
void setup() { 
  //Initialisere vores RTC objekt
  rtc.begin();
  //Serial kommunikation til debugging
  Serial.begin(9600); 
  //Set dato og tid i time, minut og sekunder
  //rtc.setDOW(THURSDAY);
  //rtc.setTime(14, 07, 0);
  //rtc.setDate(1, 10, 2019);
}
void loop() { 
  //Print klokken
  Serial.print("Time:  ");
  Serial.print(rtc.getTimeStr());
  Serial.println(" ");
  //Print datoen
  Serial.print("Date: ");
  Serial.print(rtc.getDateStr());
  Serial.println(" ");
  delay(1000); 
}
