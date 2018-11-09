
#ifndef CO2_H
#define CO2_H

#include string
#include vector



/**
  * class CO2
  * 
  */

class CO2
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  CO2 ();

  /**
   * Empty Destructor
   */
  virtual ~CO2 ();

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

#endif // CO2_H
