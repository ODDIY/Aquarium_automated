#ifndef _GUI_H_
#define _GUI_H_

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <Arduino.h>


#define TFT_DC 2 // Display
#define TFT_CS 15 // Display
#define CS_PIN  4 // Touch


enum GuiMode {  home,
                settings,
                settings2,
                eeprom_WW,
                eeprom_KW,
                eeprom_RED,
                eeprom_BLUE,
                eeprom_RGB_RED,
                eeprom_RGB_GREEN,
                eeprom_RGB_BLUE,
                eeprom_TIME,
                  };

struct Point {
        int x;
        int y;
      };

class Gui
{
private:
Adafruit_ILI9341 tft;
XPT2046_Touchscreen ts;
GuiMode mode;       // 0= home ; 1= settings
bool pumpState;       // Status der Pumpe
bool lightState;       // Status ob Licht an oder aus
bool settingbuttonState;
bool presssed;       // Touch wird gerade gedrückt
Point lastPos;       // Merkt sich den zuletzt gedrückten Punkt
bool homeChangedPump;      // Home Screen aktuellisieren bei Änderung von Pumpe
bool homeChangedAll;       // Home Screen aktuallisieren bei kompletter Änderung ( z.B. aus Settingsfenster)
bool homeChangedLight;
bool homeChangedTime;       // Displayaktualisierung für Zeiten
bool homeChangedSettingsButton;
bool settingsChangedAll;
bool settingsChangedWW;
bool settingsChangedKW;
bool settingsChangedRED;
bool settingsChangedBLUE;
bool settings2ChangedAll;
bool settings2ChangedRED;
bool settings2ChangedGREEN;
bool settings2ChangedBLUE;
bool settings2ChangedWHITE;
bool eeprom_WW_ChangedAll;
bool eeprom_KW_ChangedAll;
bool eeprom_RED_ChangedAll;
bool eeprom_BLUE_ChangedAll;
bool eeprom_RGB_RED_ChangedAll;
bool eeprom_RGB_GREEN_ChangedAll;
bool eeprom_RGB_BLUE_ChangedAll;
bool eeprom_TIME_ChangedAll;
int WW_Brightness;
int KW_Brightness;
int RED_Brightness;
int BLUE_Brightness;
int RGB_RED_Brightness;
int RGB_GREEN_Brightness;
int RGB_BLUE_Brightness;
int RGB_WHITE_Brightness;

void drawHome();
void drawSettings();
void drawSettings2();
void drawSettings3();
Point readTouch();       // liesst Touch aus
void guiRowFinder(int* brightness, bool *changedbool, int x);
void drawSetting_eeprom_WW();
void drawSetting_eeprom_KW();
void drawSetting_eeprom_RED();
void drawSetting_eeprom_BLUE();
void drawSetting_eeprom_RGB_RED();
void drawSetting_eeprom_RGB_GREEN();
void drawSetting_eeprom_RGB_BLUE();
void drawSetting_eeprom_TIME();

// analyze funktionen führen auch die eigegebenen "Knöpfe" aus
void analyzeTouchHome(Point p);
void analyzeTouchSettings(Point p);
void analyzeTouchSettings2(Point p);
void analyzeToucheeprom_WW(Point p);
void analyzeToucheeprom_KW(Point p);
void analyzeToucheeprom_RED(Point p);
void analyzeToucheeprom_BLUE(Point p);
void analyzeToucheeprom_RGB_RED (Point p);
void analyzeToucheeprom_RGB_GREEN (Point p);
void analyzeToucheeprom_RGB_BLUE (Point p);
void eeprom_GUI_draw();
void analyzeToucheeprom_TIME(Point p);

unsigned long testFillScreen();
unsigned long testText();

public:
Gui();
void setup();
void update();
};


#endif
