#include "gui.h"



#include "settings.h"


// Use hardware SPI ( D5= clk | D6= MISO | D7= MOSI
Gui::Gui(Config *conf, Licht* licht) : tft(TFT_CS, TFT_DC), ts(CS_PIN) {
  this->config = conf;
  this->licht = licht;
}


/*!
 * Wird einmalig ausgeführt beim Start
 * Initialisiert Display, Touch und Variablen
 * fährt Testszenen beim starten ab
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
 * Zeichnet Szenen und wertet Touch aus
 * @param ---
 * @return ---
   !*/
void Gui::update() {
        //pumpState = pumpe.status(); // Status der Pumpe abfragen
        /* Abfrage Touch position vom finger */
        if (ts.touched()) {
                lastPos = readTouch();
                presssed = true;
        }
//Wenn losgelassen
        if (!ts.touched() && presssed) {
                presssed = false;

                if(mode == home) {
                        analyzeTouchHome(lastPos);
                } else if (mode == settings) {
                        analyzeTouchSettings(lastPos);
                } else if (mode == settings2){
                        analyzeTouchSettings2(lastPos);
                } else if (mode == eeprom_WW){
                        analyzeToucheeprom_WW(lastPos);
                } else if (mode == eeprom_KW){
                        analyzeToucheeprom_KW(lastPos);
                } else if (mode == eeprom_RED){
                        analyzeToucheeprom_RED(lastPos);
                } else if (mode == eeprom_BLUE){
                        analyzeToucheeprom_BLUE(lastPos);
                } else if (mode == eeprom_RGB_RED){
                        analyzeToucheeprom_RGB_RED(lastPos);
                } else if (mode == eeprom_RGB_GREEN){
                        analyzeToucheeprom_RGB_GREEN(lastPos);
                } else if (mode == eeprom_RGB_BLUE){
                        analyzeToucheeprom_RGB_BLUE(lastPos);
                } else if (mode == eeprom_TIME){
                        analyzeToucheeprom_TIME(lastPos);
                }




                  else{}      // ERROR
                }



        if(millis()%1000 == 0) homeChangedTime=true; // test


        if (mode == home && (homeChangedPump==true || homeChangedAll == true|| homeChangedLight==true || homeChangedTime==true) ) drawHome();
        if (mode == settings &&( settingsChangedAll == true ||settingsChangedWW==true ||settingsChangedKW==true || settingsChangedRED==true || settingsChangedBLUE==true )) drawSettings();
        if (mode == settings2 && (settings2ChangedAll== true||settings2ChangedRED== true ||settings2ChangedGREEN== true ||settings2ChangedBLUE== true||settings2ChangedWHITE==true)) drawSettings2();
        if (mode == eeprom_WW &&(eeprom_WW_ChangedAll==true) ) drawSetting_eeprom_WW();
        if (mode == eeprom_KW &&(eeprom_KW_ChangedAll==true) ) drawSetting_eeprom_KW();
        if (mode == eeprom_RED &&(eeprom_RED_ChangedAll==true) ) drawSetting_eeprom_RED();
        if (mode == eeprom_BLUE && (eeprom_BLUE_ChangedAll==true)) drawSetting_eeprom_BLUE();
        if (mode == eeprom_RGB_RED && (eeprom_RGB_RED_ChangedAll==true)) drawSetting_eeprom_RGB_RED();
        if (mode == eeprom_RGB_GREEN && (eeprom_RGB_GREEN_ChangedAll==true)) drawSetting_eeprom_RGB_GREEN();
        if (mode == eeprom_RGB_BLUE && (eeprom_RGB_BLUE_ChangedAll==true)) drawSetting_eeprom_RGB_BLUE();
        if (mode == eeprom_TIME && (eeprom_TIME_ChangedAll==true)) drawSetting_eeprom_TIME();


}

//*TEST_FNC
//*
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

//*TEST_FNC
//*
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
 *  | <--1. Wert-->   |      |
 *  |    0..320       |  2. Wert  0..240
 *  |                 |      |
 *  |-----------------|     \/
 *
 *
 * @param ---
 * @return ---
   !*/
void Gui::drawHome(){

        if(homeChangedAll) {
                tft.fillScreen(ILI9341_BLACK);
        }

        if(homeChangedPump || homeChangedAll) {
                if (pumpState) {
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

        if(homeChangedLight || homeChangedAll) {
                if (lightState) {
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

        if (homeChangedTime|| homeChangedAll) {
                tft.fillRect(0,190,100,50,ILI9341_DARKGREY);
                tft.setCursor(10, 200);
                tft.setTextSize(3);
                tft.setTextColor(ILI9341_YELLOW);
                tft.println(millis()/1000L);
        }



        if(homeChangedAll){

          tft.drawRGBBitmap(320-setting_image.width,240-setting_image.height, (uint16_t*) setting_image.pixel_data,setting_image.width,setting_image.height);

}






          // setzt alle startbedingungen zurück
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


    if(settingsChangedAll){ // zeichnen des Grundlayouts
          tft.fillScreen(ILI9341_LIGHTGREY);

          tft.setTextSize(2);
          for(int i =0; i<190; i= i+55)  {      // zeichnen von 5x4 Quadraten
              for (int j=0; j<270; j= j+55) {
                  tft.fillRect(5+j,5+i,50,50,ILI9341_BLACK);

                  if(i==0) tft.setTextColor(ILI9341_ORANGE);
                    if(i==55) tft.setTextColor(ILI9341_WHITE);
                      if(i==110) tft.setTextColor(ILI9341_RED);
                        if(i==165) tft.setTextColor(ILI9341_BLUE);

                  if(j== 0) {
                    tft.setCursor(7+j,25+i);
                    tft.println("+10%");  }

                  if(j==55){
                    tft.setCursor(7+j,25+i);
                    tft.println("+1%"); }

                    if(j==(3* 55)){
                      tft.setCursor(7+j,25+i);
                      tft.println("-1%");   }

                      if(j==4* 55){
                        tft.setCursor(7+j,25+i);
                        tft.println("-10%");   }
                      }
                    }
            tft.setTextColor(ILI9341_BLACK);
            tft.setCursor(5,223);
            tft.println("aktuelle Helligkeit");
            tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
            tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
            tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);

            }

            if(settingsChangedWW || settingsChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
              tft.fillRect(115,5,50,50,ILI9341_BLACK);
              tft.setTextColor(ILI9341_ORANGE);
              tft.setCursor(117,25);
              tft.printf("%d%%", WW_Brightness);                }

              if(settingsChangedKW || settingsChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                tft.fillRect(115,60,50,50,ILI9341_BLACK);
                tft.setTextColor(ILI9341_WHITE);
                tft.setCursor(117,80);
                tft.printf("%d%%", KW_Brightness);                }

                if(settingsChangedRED || settingsChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                  tft.fillRect(115,115,50,50,ILI9341_BLACK);
                  tft.setCursor(117,135);
                  tft.setTextColor(ILI9341_RED);
                  tft.printf("%d%%", RED_Brightness);                }

                  if(settingsChangedBLUE || settingsChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                    tft.fillRect(115,170,50,50,ILI9341_BLACK);
                    tft.setTextColor(ILI9341_BLUE);
                    tft.setCursor(117,190);
                    tft.printf("%d%%", BLUE_Brightness);                }




          settingsChangedAll=false;
          settingsChangedWW= false;
          settingsChangedKW=false;
          settingsChangedRED=false;
          settingsChangedBLUE=false;
} //Hauptbeleuchtung

void Gui::drawSettings2(){


  if (  settings2ChangedAll ){
    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,200);
    tft. println(" aktuelle Helligkeit \n RGB Hintergrund");


    for(int i =0; i<140; i= i+55)  {      // zeichnen von 5x4 Quadraten
        for (int j=0; j<270; j= j+55) {
            tft.fillRect(5+j,5+i,50,50,ILI9341_BLACK);

            if(i==0) tft.setTextColor(ILI9341_RED);
              if(i==55) tft.setTextColor(ILI9341_GREEN);
                if(i==110) tft.setTextColor(ILI9341_BLUE);


            if(j== 0) {
              tft.setCursor(7+j,25+i);
              tft.println("+10%");  }

            if(j==55){
              tft.setCursor(7+j,25+i);
              tft.println("+1%"); }

              if(j==(3* 55)){
                tft.setCursor(7+j,25+i);
                tft.println("-1%");   }

                if(j==4* 55){
                  tft.setCursor(7+j,25+i);
                  tft.println("-10%");   }
                }
              }
              tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
              tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
              tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
              }


              if(settings2ChangedRED || settings2ChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                tft.fillRect(115,5,50,50,ILI9341_BLACK);
                tft.setTextColor(ILI9341_RED);
                tft.setCursor(117,25);
                tft.printf("%d%%", RGB_RED_Brightness);                }

                if(settings2ChangedGREEN || settings2ChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                  tft.fillRect(115,60,50,50,ILI9341_BLACK);
                  tft.setTextColor(ILI9341_GREEN);
                  tft.setCursor(117,80);
                  tft.printf("%d%%", RGB_GREEN_Brightness);                }

                  if(settings2ChangedBLUE || settings2ChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                    tft.fillRect(115,115,50,50,ILI9341_BLACK);
                    tft.setCursor(117,135);
                    tft.setTextColor(ILI9341_BLUE);
                    tft.printf("%d%%", RGB_BLUE_Brightness);                }

                    if(settings2ChangedWHITE || settings2ChangedAll) {  // Wert von Warmweiß aktuallisierenetc...
                      tft.fillRect(115,115+55,50,50,ILI9341_BLACK);
                      tft.setCursor(117,190);
                      tft.setTextColor(ILI9341_WHITE);
                      tft.printf("%d%%", RGB_BLUE_Brightness);                }








settings2ChangedAll= false;
settings2ChangedRED= false;
settings2ChangedBLUE= false;
settings2ChangedGREEN = false;
settings2ChangedWHITE= false;
} // RGB Rückwand

void Gui::drawSetting_eeprom_WW() {
    //float start, float end, float val, float offStart, float offEnd, float offVal, int time
  // EEprom Änderung der Werte
  if(eeprom_WW_ChangedAll){

    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-WW");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }


    eeprom_WW_ChangedAll = false;
}



void Gui::drawSetting_eeprom_KW() {

  if(eeprom_KW_ChangedAll){
    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-KW");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

  eeprom_KW_ChangedAll = false;
}
void Gui::drawSetting_eeprom_RED() {

  if(eeprom_RED_ChangedAll){

    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-RED");
  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

    eeprom_RED_ChangedAll = false;
}



void Gui::drawSetting_eeprom_BLUE() {

  tft.fillScreen(ILI9341_LIGHTGREY);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(5,5);
  tft. println("EEPROM-Settings-BLUE");

  if(eeprom_BLUE_ChangedAll){


  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

    eeprom_BLUE_ChangedAll = false;
}



void Gui::drawSetting_eeprom_RGB_RED() {

  if(eeprom_RGB_RED_ChangedAll){
    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-RGB-RED");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

    eeprom_RGB_RED_ChangedAll = false;
}



void Gui::drawSetting_eeprom_RGB_GREEN() {


  if(eeprom_RGB_GREEN_ChangedAll){
    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-RGB-GREEN");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }
    eeprom_RGB_GREEN_ChangedAll = false;
}



void Gui::drawSetting_eeprom_RGB_BLUE() {

  if(eeprom_RGB_BLUE_ChangedAll){

    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-RGB-BLUE");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

  eeprom_RGB_BLUE_ChangedAll = false;
}


void Gui::drawSetting_eeprom_TIME() {

  if(eeprom_TIME_ChangedAll){

    tft.fillScreen(ILI9341_LIGHTGREY);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(5,5);
    tft. println("EEPROM-Settings-TIME");

  tft.drawRGBBitmap(320-arrow_left.width,240-(arrow_image.height+home_image.height+arrow_left.height), (uint16_t*) arrow_left.pixel_data,arrow_left.width,arrow_left.height);
  tft.drawRGBBitmap(320-arrow_image.width,240-(arrow_image.height+home_image.height), (uint16_t*) arrow_image.pixel_data,arrow_image.width,arrow_image.height);
  tft.drawRGBBitmap(320-home_image.width,240-home_image.height, (uint16_t*) home_image.pixel_data,home_image.width,home_image.height);
  }

  eeprom_TIME_ChangedAll = false;
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

        out.x = ((p.x -450.0)/343.0*32.0);
        out.y = ((p.y-244.0)/379.0*26);

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

        if (x<=120 && x>= 0 && y<=120 && y>=0) { // Pumpe Status ändern
                if (pumpState) {
                        pumpState= false;
                        homeChangedPump= true;
                }
                else {pumpState= true;
                      homeChangedPump=true;}
        }

        if (x<=320 && x>= 120 && y<=120 && y>=0) {   // LICHT Status ändern
                if (lightState) {
                        lightState= false;
                        homeChangedLight= true;
                }
                else {lightState= true;
                      homeChangedLight=true;}


        }
        if (x<=320 && x>= 250 && y<=240 && y>=200) {   // zu Settings wechseln
          mode= settings;
          settingsChangedAll= true;

        }

}


/*!
 * Zeichnet Settings interface
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
void Gui::analyzeTouchSettings(Point p) {

  int x = p.x;
  int y = p.y;

  Serial.print(" Touch x="); Serial.println(x);
  Serial.print(" Touch y="); Serial.println(y);
  Serial.print(" \n \n");
  if (x<=120 && x>= 0 && y<=120 && y>=0) {

  }

  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=settings2;
      settings2ChangedAll= true;

      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
             mode=eeprom_RGB_BLUE;
             eeprom_RGB_BLUE_ChangedAll= true;  }

  }

  if (y>5 && y< 55) {
  guiRowFinder(&WW_Brightness, &settingsChangedWW, x);
  licht->setWW(WW_Brightness);
  }
  if (y>60 && y< 110) {
  guiRowFinder(&KW_Brightness, &settingsChangedKW, x);
  licht->setKW(KW_Brightness);
  }
  if (y>115 && y< 165) {
  guiRowFinder(&RED_Brightness, &settingsChangedRED, x);
  licht->setR(RED_Brightness);
  }
  if (y>170 && y< 210) {
  guiRowFinder(&BLUE_Brightness, &settingsChangedBLUE, x);
  licht->setB(BLUE_Brightness);

  }


}


void Gui::analyzeTouchSettings2(Point p) {
  int x = p.x;
  int y = p.y;

  Serial.print(" Touch x="); Serial.println(x);
  Serial.print(" Touch y="); Serial.println(y);
  Serial.print(" \n \n");


if (y>5 && y< 55) {
guiRowFinder(&RGB_RED_Brightness, &settings2ChangedRED, x);
licht->setRGB(RGB_RED_Brightness, RGB_GREEN_Brightness,RGB_BLUE_Brightness );
}
if (y>60 && y< 110) {
guiRowFinder(&RGB_GREEN_Brightness, &settings2ChangedGREEN, x);
licht->setRGB(RGB_RED_Brightness, RGB_GREEN_Brightness,RGB_BLUE_Brightness );
}
if (y>115 && y< 165) {
guiRowFinder(&RGB_BLUE_Brightness, &settings2ChangedBLUE, x);
licht->setRGB(RGB_RED_Brightness, RGB_GREEN_Brightness,RGB_BLUE_Brightness );
}
if (y>170 && y< 210) {
guiRowFinder(&RGB_WHITE_Brightness, &settings2ChangedWHITE, x);
}



  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings nächste seite wechseln
      mode=eeprom_WW;
      eeprom_WW_ChangedAll= true;  }

      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
        mode=settings;
        settingsChangedAll= true;  }



    }


void Gui::analyzeToucheeprom_WW(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_KW;
      eeprom_KW_ChangedAll= true;  }

    if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
          mode=settings2;
          settings2ChangedAll= true;  }
}
void Gui::analyzeToucheeprom_KW(Point p) {
  int x = p.x;
  int y = p.y;



  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_BLUE;
      eeprom_BLUE_ChangedAll= true; }
      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
            mode=eeprom_WW;
            eeprom_WW_ChangedAll= true;  }
}
void Gui::analyzeToucheeprom_BLUE(Point p){

  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_RED;
      eeprom_RED_ChangedAll= true; }
      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
            mode=eeprom_KW;
            eeprom_KW_ChangedAll= true;  }
}
void Gui::analyzeToucheeprom_RED(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_RGB_RED;
      eeprom_RGB_RED_ChangedAll= true; }

      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
            mode=eeprom_BLUE;
            eeprom_BLUE_ChangedAll= true;  }
}
void Gui::analyzeToucheeprom_RGB_RED(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_RGB_GREEN;
      eeprom_RGB_GREEN_ChangedAll= true; }

      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
            mode=eeprom_RED;
            eeprom_RED_ChangedAll= true;  }


}
void Gui::analyzeToucheeprom_RGB_GREEN(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_RGB_BLUE;
      eeprom_RGB_BLUE_ChangedAll= true;}

      if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
            mode=eeprom_RGB_RED;
            eeprom_RGB_RED_ChangedAll= true;  }
}
void Gui::analyzeToucheeprom_RGB_BLUE(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=eeprom_TIME;
      eeprom_TIME_ChangedAll= true;}
       if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
              mode=eeprom_RGB_GREEN;
              eeprom_RGB_GREEN_ChangedAll= true;  }
}

void Gui::analyzeToucheeprom_TIME(Point p) {
  int x = p.x;
  int y = p.y;
  if (x<=320 && x>= 280 && y<=240 && y>=200) {   // zu home wechseln
    mode=home;
    homeChangedAll= true; }

    if (x<=320 && x>= 280 && y<=200 && y>=160) {   // zu settings wechseln
      mode=settings;
      settingsChangedAll= true;}
       if (x<=320 && x>= 280 && y<=160 && y>=120) {   // zu settings nächste seite wechseln
              mode=eeprom_RGB_GREEN;
              eeprom_RGB_GREEN_ChangedAll= true;  }
}















void Gui::guiRowFinder(int* brightness, bool* changedbool, int x) {
if (x>5&& x<55)           { *brightness+=10; *changedbool= true; }
else if (x>60 && x<115)   { *brightness+=1;   *changedbool=true; }
else if (x>180 && x<235)  { *brightness-=1 ;   *changedbool=true;}
else if (x>240 && x<295)  { *brightness -=10; *changedbool= true; }
  }
