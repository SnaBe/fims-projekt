//28-02-2019
//Simon S. Sørensen
//Teknologi eksamensprojekt 2018-2019

//SD-kort læser, til at gemme filer og data

#include <SPI.h>
#include <SD.h>

File myFile;

int cs = 4;

//Setup metode
void setup(void) {
  //Start serial kommunikation på port 9600
  Serial.begin(9600);
  while(!Serial) {
    //Vent på en åben forbindelse, dog kun native USB ports.
  }

  Serial.println("Initializing SD card...");
  //Der er ikke noget SD kort iadapteren.
  if(!SD.begin(cs)) {
    Serial.println("SD card initialization failed!");
    while(true);
  }
  Serial.println("SD card initialization done.");
  //Åben vores vores fil, vi kan dog ikke have andre filer åben.
  //Husk derfor at lukke den fil inden du åbner en anden.
  myFile = SD.open("test.txt", FILE_WRITE);

  //Hvis vi var i stand til at åbne vores fil, kan vi skrive til den.
  if(myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    //Luk filen efter brug
    myFile.close();
    Serial.println("Done closing test file.");
  } else {
    //Vi var ikke i stand til at åbne vores fil, print en error besked.
    Serial.println("Error opening test.txt");
  }
  
  //Genåben filen så vi kan læsen den
  myFile = SD.open("test.txt");
  if(myFile) {
    Serial.println("test.txt:");

    //Læs igennem vores fil indtil der ikke er mere at læse.
    while(myFile.available()) {
      Serial.write(myFile.read());
    }
    //Luk filen efter brug
    myFile.close();
  } else {
    //Vi var ikke i stand til at åbne vores fil, print en error besked.
    Serial.println("error opening test.txt");
  }
}

//Loop metode
void loop(void) {
  //Fyld ud senere
}
