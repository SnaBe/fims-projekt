//17-01-2019
//Simon S. Sørensen
//Teknologi eksamensprojekt 2018-2019

//Komponenter der skal bruges/eller der er brugt til projektet
//3.2s tommer TFT LCD, bruges til at visse inventar (Open smart)
//RTC module, så vi kender den nuværende dato og tid 
//Arduino Mega, til ekstra lageringsplads
//SD-kort læser, til at gemme filer og data

//Bibliotek til brug af grafik, kan være hardware-specifikke (Må ikke opdateres uden videre)
#include <Adafruit_GFX.h>    
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

bool printText = true;

//16-bit farve værdier som læselige variabler
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

uint16_t g_identifier;

//Øverst venstre fra USB port
const int fims_rotation = 3;

int x = 1;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);

  tft.begin(0x65);
  tft.setRotation(3);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  fimsText();
}

unsigned long fimsText() {
  tft.setRotation(fims_rotation);
  tft.setCursor(tft.width() / 5, tft.height() / 2.5);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("I <3 E :^)");
  delay(3000);
}
