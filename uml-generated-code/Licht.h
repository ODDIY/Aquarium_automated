
#ifndef LICHT_H
#define LICHT_H

#include string
#include vector



/**
  * class Licht
  * 
  */

class Licht
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Licht ();

  /**
   * Empty Destructor
   */
  virtual ~Licht ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   */
  void setup ()
  {
  }


  /**
   * Fadet das licht nach bedarf an und aus
   * Und steuert die C02 zufur
   */
  void update ()
  {
  }


  /**
   * gibt das signal das licht mit einer bestimmten geschwindichkeit zu starten
   * @param  speed
   */
  void an (int speed)
  {
  }


  /**
   * Schaltet das licht mit einer bestimmten geschwindichket aus
   * @param  speed
   */
  void aus (int speed)
  {
  }


  /**
   * Schaltet sofort die RGB lampen auf einen bestimten wert
   * @param  red
   * @param  green
   * @param  blue
   */
  void setRGB (int red, int green, int blue)
  {
  }


  /**
   * setzt die Warm Weiß sofort auf einen bestimmten wert
   * @param  value
   */
  void setWW (int value)
  {
  }


  /**
   * setzt die Kalt Weiß sofort auf einen bestimmten wert
   * @param  value
   */
  void setKW (int value)
  {
  }


  /**
   * setzt die Roten LEDs sofort auf einen bestimmten wert
   * @param  value
   */
  void setR (int value)
  {
  }


  /**
   * setzt die Blauen LEDs sofort auf einen bestimmten wert
   * @param  value
   */
  void setB (int value)
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  int PWM_PIN_WW;
  int PWM_PIN_KW;
  int PWM_PIN_R;
  int PWM_PIN_B;
  int PWM_PIN_RGB_R;
  int PWM_PIN_RGB_G;
  int PWM_PIN_RGB_B;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of PWM_PIN_WW
   * @param new_var the new value of PWM_PIN_WW
   */
  void setPWM_PIN_WW (int new_var)   {
      PWM_PIN_WW = new_var;
  }

  /**
   * Get the value of PWM_PIN_WW
   * @return the value of PWM_PIN_WW
   */
  int getPWM_PIN_WW ()   {
    return PWM_PIN_WW;
  }

  /**
   * Set the value of PWM_PIN_KW
   * @param new_var the new value of PWM_PIN_KW
   */
  void setPWM_PIN_KW (int new_var)   {
      PWM_PIN_KW = new_var;
  }

  /**
   * Get the value of PWM_PIN_KW
   * @return the value of PWM_PIN_KW
   */
  int getPWM_PIN_KW ()   {
    return PWM_PIN_KW;
  }

  /**
   * Set the value of PWM_PIN_R
   * @param new_var the new value of PWM_PIN_R
   */
  void setPWM_PIN_R (int new_var)   {
      PWM_PIN_R = new_var;
  }

  /**
   * Get the value of PWM_PIN_R
   * @return the value of PWM_PIN_R
   */
  int getPWM_PIN_R ()   {
    return PWM_PIN_R;
  }

  /**
   * Set the value of PWM_PIN_B
   * @param new_var the new value of PWM_PIN_B
   */
  void setPWM_PIN_B (int new_var)   {
      PWM_PIN_B = new_var;
  }

  /**
   * Get the value of PWM_PIN_B
   * @return the value of PWM_PIN_B
   */
  int getPWM_PIN_B ()   {
    return PWM_PIN_B;
  }

  /**
   * Set the value of PWM_PIN_RGB_R
   * @param new_var the new value of PWM_PIN_RGB_R
   */
  void setPWM_PIN_RGB_R (int new_var)   {
      PWM_PIN_RGB_R = new_var;
  }

  /**
   * Get the value of PWM_PIN_RGB_R
   * @return the value of PWM_PIN_RGB_R
   */
  int getPWM_PIN_RGB_R ()   {
    return PWM_PIN_RGB_R;
  }

  /**
   * Set the value of PWM_PIN_RGB_G
   * @param new_var the new value of PWM_PIN_RGB_G
   */
  void setPWM_PIN_RGB_G (int new_var)   {
      PWM_PIN_RGB_G = new_var;
  }

  /**
   * Get the value of PWM_PIN_RGB_G
   * @return the value of PWM_PIN_RGB_G
   */
  int getPWM_PIN_RGB_G ()   {
    return PWM_PIN_RGB_G;
  }

  /**
   * Set the value of PWM_PIN_RGB_B
   * @param new_var the new value of PWM_PIN_RGB_B
   */
  void setPWM_PIN_RGB_B (int new_var)   {
      PWM_PIN_RGB_B = new_var;
  }

  /**
   * Get the value of PWM_PIN_RGB_B
   * @return the value of PWM_PIN_RGB_B
   */
  int getPWM_PIN_RGB_B ()   {
    return PWM_PIN_RGB_B;
  }
private:


  void initAttributes () ;

};

#endif // LICHT_H
