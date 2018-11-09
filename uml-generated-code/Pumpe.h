
#ifndef PUMPE_H
#define PUMPE_H

#include string
#include vector



/**
  * class Pumpe
  * 
  */

class Pumpe
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Pumpe ();

  /**
   * Empty Destructor
   */
  virtual ~Pumpe ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * Schaltet nach 30 mintuten in der die pumpe nicht in betrieb ist den Summer an
   */
  void update ()
  {
  }


  /**
   */
  void setup ()
  {
  }


  /**
   */
  void an ()
  {
  }


  /**
   */
  void aus ()
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

  unsigned long int timer;
  int PWM_PIN;
  bool status;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of timer
   * @param new_var the new value of timer
   */
  void setTimer (unsigned long int new_var)   {
      timer = new_var;
  }

  /**
   * Get the value of timer
   * @return the value of timer
   */
  unsigned long int getTimer ()   {
    return timer;
  }

  /**
   * Set the value of PWM_PIN
   * @param new_var the new value of PWM_PIN
   */
  void setPWM_PIN (int new_var)   {
      PWM_PIN = new_var;
  }

  /**
   * Get the value of PWM_PIN
   * @return the value of PWM_PIN
   */
  int getPWM_PIN ()   {
    return PWM_PIN;
  }

  /**
   * Set the value of status
   * @param new_var the new value of status
   */
  void setStatus (bool new_var)   {
      status = new_var;
  }

  /**
   * Get the value of status
   * @return the value of status
   */
  bool getStatus ()   {
    return status;
  }
private:


  void initAttributes () ;

};

#endif // PUMPE_H
