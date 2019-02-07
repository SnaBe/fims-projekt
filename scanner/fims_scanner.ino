 //Her bliver biblioteker importeret.
#include <SoftwareSerial.h>

#include <hidboot.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <SimpleTimer.h>

//Her bliver de globale variabler definieret
int zero = 0;
char key;
String code;

//En klasse styret af biblioteket "USB Host Shield library 2.0"
class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

//En metode styret af biblioteket "USB Host Shield library 2.0"
void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
};

//En metode styret af biblioteket "USB Host Shield library 2.0"
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  if(c)
    OnKeyPressed(c);
}

//En metode styret af biblioteket "USB Host Shield library 2.0"
void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.println("LeftShift Changed");
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.println("LeftGUI changed");
  }
  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.println("RightGUI changed");
  }
}

//En metode styret af biblioteket "USB Host Shield library 2.0"
void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  PrintKey(mod, key);
}

//En metode styret af biblioteket "USB Host Shield library 2.0"
void KbdRptParser::OnKeyPressed(uint8_t key)
{ 
  Serial.print((char)key); //debug
}
  
//Variabler styret af biblioteket "USB Host Shield library 2.0"
USB Usb;
//USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
KbdRptParser Prs;

//Klasisk arduino metode som bliver kaldt som den første.
void setup()
{
  Serial.begin( 115200 ); //Her bliver Serial kommunikationen initializeret
  //styret af "USB Host Shield" biblioteket 
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  Serial.println("Start");
  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
  delay( 200 );
  HidKeyboard.SetReportParser(0, &Prs);
}

//En metode der køres igen og igen i et loop
void loop()
{
  Usb.Task();
}
