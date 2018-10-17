#ifndef _GUI_H_
#define _GUI_H_


#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <Arduino.h>


#define TFT_DC 2 // Display
#define TFT_CS 15 // Display
#define CS_PIN  4 // Touch


enum GuiMode {  home,  settings};

struct Point{
  int x;
   int y;
 };

class Gui {

  Adafruit_ILI9341 tft;
  XPT2046_Touchscreen ts;
  GuiMode mode; // 0= Home ; 1= Setting
  bool pumpState; // Status der Pumpe
  bool lightState; // Status ob Licht an oder aus
  bool presssed; // Touch wird gerade gedrückt
  Point lastPos; // Merkt sich den zuletzt gedrückten Punkt
  bool homeChangedPump;// Home Screen aktuellisieren bei Änderung von Pumpe
  bool homeChangedAll; // Home Screen aktuallisieren bei kompletter Änderung ( z.B. aus Settingsfenster)
  bool homeChangedLight;
  bool homeChangedTime; // Displayaktualisierung für Zeiten
  void drawHome();
  void drawSettings();
  Point readTouch(); // liesst Touch aus


  // analyze funktionen führen auch die eigegebenen "Knöpfe" aus
  void analyzeTouchHome(Point p);
  void analyzeTouchSettings(Point p);

  unsigned long testFillScreen();
  unsigned long testText();

  public:

  Gui();
  void setup();
  void update();

};

#endif
