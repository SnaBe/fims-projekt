  //17-01-2019
//Simon S. Sørensen
//Teknologi eksamensprojekt 2018-2019

//Komponenter der skal bruges/eller der er brugt til projektet
//3.2s tommer TFT LCD, bruges til at visse inventar (Open smart)
//RTC module, så vi kender den nuværende dato og tid 
//Arduino Mega, til ekstra lageringsplads
//SD-kort læser, til at gemme filer og data

//Importer de nødvendige biblioteker
#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

char stregkodeChar[50];
int countChar = 0;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DS3231 rtc(SDA, SCL);

class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

String findVare(char stregkode[50]) {
  Serial.println("Parsed code: ");
  Serial.println(stregkode);
  String vare = String(stregkode);
  if(vare == "5740700994203") {
    Serial.println("Fanta Lemon");
    return "Fanta Lemon";   
  } else if(vare == "5760466304160") {
    Serial.println("Buko Rejeost");
    return "Buko Rejeost";    
  } else if(vare == "5760466904919") {
    Serial.println("Kærgården smør");
    return "Kærgården smør";    
  } else {
    Serial.println("Ukendt vare!");
    return "Ukendt vare";
  }
}


MyParser::MyParser() {}

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error or empty, return
  if (buf[2] == 1 || buf[2] == 0) return;
  for (uint8_t i = 7; i >= 2; i--) {
    // If empty, skip
    if (buf[i] == 0) continue;
    // If enter signal emitted, scan finished
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
      OnScanFinished();
    }
    // If not, continue normally
    else {
      // If bit position not in 2, it's uppercase words
      OnKeyScanned(i > 2, buf, buf[i]);
    }
    return;
  }
}

uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  // Letters
  if(VALUE_WITHIN(key, 0x04, 0x1d)) {
    if(upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }
  //Numbers
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }
  return 0;
}

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  Serial.print((char)ascii);
  lcd.print((char)ascii);
  stregkodeChar[countChar] = (char)ascii;
  countChar += 1;
}

void MyParser::OnScanFinished() {
  Serial.println(" - Finished");
  lcd.setCursor(0, 1);
  lcd.print(findVare(stregkodeChar));
  Serial.println(findVare(stregkodeChar));
  countChar = 0;
}

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser Parser;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println("Loading RTC module.");
  rtc.begin();
  Serial.println("Initialising the connection to the USB Host Shield.");
  if (Usb.Init() == -1) {
    Serial.println("OSC did not start.");
  }
  delay(200);
  Serial.println("All set, F.I.M.S is running");
  Hid.SetReportParser(0, &Parser);
}

void loop() {
  Usb.Task();
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDateStr());
  lcd.print(" ");
  lcd.print(rtc.getTimeStr());
}
