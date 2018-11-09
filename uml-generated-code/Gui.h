
#ifndef GUI_H
#define GUI_H

#include string
#include vector



/**
  * class Gui
  * 
  */

class Gui
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Gui ();

  /**
   * Empty Destructor
   */
  virtual ~Gui ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * Wird einmal im loop ausgefürt
   */
  void update ()
  {
  }


  /**
   * Wird zum begin des programms aufgerufen
   */
  void setup ()
  {
  }


  /**
   * gibt das signal das licht schnell aus zu schalten
   */
  void licht_aus ()
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

  // Modus 
  // 1 == Home
  // 2 == Settings
  int mode;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of mode
   * Modus
   * 1 == Home
   * 2 == Settings
   * @param new_var the new value of mode
   */
  void setMode (int new_var)   {
      mode = new_var;
  }

  /**
   * Get the value of mode
   * Modus
   * 1 == Home
   * 2 == Settings
   * @return the value of mode
   */
  int getMode ()   {
    return mode;
  }
private:



  /**
   * Zeichent das Home menue
   */
  void drawHome ()
  {
  }


  /**
   * Zeichnet den Settings Bildschirm
   */
  void drawSettings ()
  {
  }


  /**
   * schaltet die pumpe an
   */
  void pumpe_an ()
  {
  }


  /**
   * schaltet die pumpe aus
   */
  void pumpe_aus ()
  {
  }


  /**
   * gibt das signal das licht schnell an zu schalten
   */
  void licht_an ()
  {
  }

  void initAttributes () ;

};

#endif // GUI_H
