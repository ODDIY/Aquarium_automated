#include "gui.h"



// Use hardware SPI ( D5= clk | D6= MISO | D7= MOSI
Gui::Gui() : tft(TFT_CS, TFT_DC), ts(CS_PIN) {



}





/*!
* Wird einmalig ausgeführt beim Start
*Initialisiert Display, Touch und Variablen
*fährt Testszenen beim starten ab
* @param ---
* @return ---
!*/
void Gui::setup(){
//kalibrierung, touch.begin,
// testbild
        mode = home;
        pumpState=false;
        tft.begin();

        ts.begin();
        ts.setRotation(1);



// read diagnostics (optional but can help debug problems)
        uint8_t x = tft.readcommand8(ILI9341_RDMODE);
        Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
        x = tft.readcommand8(ILI9341_RDMADCTL);
        Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
        x = tft.readcommand8(ILI9341_RDPIXFMT);
        Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
        x = tft.readcommand8(ILI9341_RDIMGFMT);
        Serial.print("Image Format: 0x"); Serial.println(x, HEX);
        x = tft.readcommand8(ILI9341_RDSELFDIAG);
        Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

        Serial.println(F("Benchmark                Time (microseconds)"));
        delay(10);
        Serial.print(F("Screen fill              "));
        Serial.println(testFillScreen());
        delay(10);

        Serial.print(F("Text                     "));
        Serial.println(testText());
        delay(1000);

        Serial.println(F("Done!"));


        tft.setRotation(3);
        ts.setRotation(3);

        homeChangedAll=true;
        drawHome(); // Hauptbildschirm initialisieren
}



/*!
* Updatefunktion, wird jeden Loop aufgeführt
*Zeichnet Szenen und wertet Touch aus
* @param ---
* @return ---
!*/
void Gui::update() {
  //pumpState = pumpe.status(); // Status der Pumpe abfragen
        /* Abfrage Touch position vom finger */
        if (ts.touched()) {
          lastPos = readTouch()  ;
          presssed = true;
         }
//Wenn losgelassen
  if (!ts.touched() && presssed) {
      presssed = false;

      if(mode == home) {
          analyzeTouchHome(lastPos);
          } else if (mode == settings) {
            analyzeTouchSettings(lastPos);
          } else {
          // ERROR
          }
  }


  if(millis()%1000 == 0) homeChangedTime=true; // test


  if (mode == home && (homeChangedPump==true || homeChangedAll == true|| homeChangedLight==true || homeChangedTime==true) ) drawHome();
}
// füllt Display mit Farben zum Test, beim Starten
unsigned long Gui::testFillScreen() {
        unsigned long start = micros();
        tft.fillScreen(ILI9341_BLACK);
        yield();
        tft.fillScreen(ILI9341_RED);
        yield();
        tft.fillScreen(ILI9341_GREEN);
        yield();
        tft.fillScreen(ILI9341_BLUE);
        yield();
        tft.fillScreen(ILI9341_BLACK);
        yield();
        return micros() - start;
}


// Zeichnet Testbild beim Starten
unsigned long Gui::testText() {
        tft.fillScreen(ILI9341_BLACK);
        unsigned long start = micros();
        tft.setCursor(0, 0);
        tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
        tft.println("Hello World!");
        tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
        tft.println(1234.56);
        tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
        tft.println(0xDEADBEEF, HEX);
        tft.println();
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(5);
        tft.println("Groop");
        tft.setTextSize(2);
        tft.println("I implore thee,");
        tft.setTextSize(1);
        tft.println("my foonting turlingdromes.");
        tft.println("And hooptiously drangle me");
        tft.println("with crinkly bindlewurdles,");
        tft.println("Or I will rend thee");
        tft.println("in the gobberwarts");
        tft.println("with my blurglecruncheon,");
        tft.println("see if I don't!");
        tft.fillScreen(ILI9341_BLACK);
        return micros() - start;

}



/*!
* Zeichnet Home interface
*  |-----------------|      /\
*  | <--2. Wert-->   |      |
*  |    0..320       |  1. Wert  0..240
*  |                 |      |
*  |-----------------|     \/
*
*
* @param ---
* @return ---
!*/
void Gui::drawHome(){

if(homeChangedAll){
    tft.fillScreen(ILI9341_BLACK);
        }


if(homeChangedPump || homeChangedAll){
if (pumpState){
    tft.fillRect(0,0,120,120,ILI9341_GREEN);
    tft.setCursor(10, 10);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Pumpe \n \n  AN");
    }
else{
tft.fillRect(0,0,120,120,ILI9341_RED);
tft.setCursor(10, 10);
tft.setTextSize(3);
tft.setTextColor(ILI9341_BLACK);
tft.println("Pumpe \n \n  AUS");
}
}


if(homeChangedLight || homeChangedAll){
if (lightState){
    tft.fillRect(120,0,200,120,ILI9341_CYAN);
    tft.setCursor(130, 10);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Licht AN");
    }
else{
  tft.fillRect(120,0,200,120,ILI9341_LIGHTGREY);
  tft.setCursor(130, 10);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("LICHT AUS");
}
}



if (homeChangedTime|| homeChangedAll){
tft.fillRect(0,190,100,50,ILI9341_DARKGREY);
tft.setCursor(10, 200);
tft.setTextSize(3);
tft.setTextColor(ILI9341_YELLOW);
tft.println(millis()/1000);
}







homeChangedTime= false;
homeChangedLight = false;
homeChangedPump=false;
homeChangedAll=false;
}





/*!
* Zeichnet Settings interface
*
* @param ---
* @return ---
!*/
void Gui::drawSettings(){



}


/*!
* Holt die x und y kordinate vom touch
* wird nur ausgefürt wenn ts.touched
* @param ---
* @return Punkt mit x und y kooridinate
!*/
Point Gui::readTouch(){


  TS_Point p = ts.getPoint();
  Point out;

  out.x = ((p.x -450)/343*32);
  out.y = ((p.y-230)/379*26);

  return out;
  }

  /*!
  * Zeichnet Settings interface
  *
  * @param ---
  * @return ---
  !*/
  void Gui::analyzeTouchHome(Point p){
    int x = p.x;
    int y = p.y;

    Serial.print(" Touch x="); Serial.println(x);
    Serial.print(" Touch y="); Serial.println(y);
    Serial.print(" Pumpe: "); Serial.println(pumpState);
    Serial.print(" \n \n");

    if (x<=120 && x>= 0 && y<=120 && y>=0){   // Pumpe Status ändern
        if (pumpState) {
          pumpState= false;
          homeChangedPump= true;
          }
        else {pumpState= true;
          homeChangedPump=true;
          }
        }

        if (x<=320 && x>= 120 && y<=120 && y>=0){   // LICHT Status ändern
            if (lightState) {
              lightState= false;
              homeChangedLight= true;
              }
            else {lightState= true;
              homeChangedLight=true;
              }
            }



  }


 void Gui::analyzeTouchSettings(Point) {}
