
#ifndef TIMER_H
#define TIMER_H

#include string
#include vector



/**
  * class Timer
  * 
  */

class Timer
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Timer ();

  /**
   * Empty Destructor
   */
  virtual ~Timer ();

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
  void update ()
  {
  }


  /**
   */
  void setup ()
  {
  }


  /**
   * time info für die GUI
   * 
   * @return string
   */
  string info ()
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

  unsigned long int time;
  time time_obj;
  unsigned long int last_millis;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of time
   * @param new_var the new value of time
   */
  void setTime (unsigned long int new_var)   {
      time = new_var;
  }

  /**
   * Get the value of time
   * @return the value of time
   */
  unsigned long int getTime ()   {
    return time;
  }

  /**
   * Set the value of time_obj
   * @param new_var the new value of time_obj
   */
  void setTime_obj (time new_var)   {
      time_obj = new_var;
  }

  /**
   * Get the value of time_obj
   * @return the value of time_obj
   */
  time getTime_obj ()   {
    return time_obj;
  }

  /**
   * Set the value of last_millis
   * @param new_var the new value of last_millis
   */
  void setLast_millis (unsigned long int new_var)   {
      last_millis = new_var;
  }

  /**
   * Get the value of last_millis
   * @return the value of last_millis
   */
  unsigned long int getLast_millis ()   {
    return last_millis;
  }
private:



  /**
   * Gibt das signal die lichter an zu schalten
   * 
   */
  void sunrise ()
  {
  }


  /**
   * gibt das signal die lichter aus zu schalten
   */
  void sunset ()
  {
  }


  /**
   * holt die aktuelle zeit aus dem internet
   */
  void configTime ()
  {
  }

  void initAttributes () ;

};

#endif // TIMER_H
