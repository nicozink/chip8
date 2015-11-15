/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef TIMER_H
#define TIMER_H

// Local Includes

// Project Includes

// External Includes
#include <ctime>

// A class which represents a timer.
template <unsigned int TFrequency>
class Timer
{
  public:
  
    Timer()
    {
      Set(0);
    }
    
    void Set(const unsigned int steps)
    {
      zero_time = std::clock() + steps * (CLOCKS_PER_SEC / TFrequency);
    }

    unsigned int Get() const
    {
      clock_t current = std::clock();

      if (current > zero_time)
      {
        return 0;
      }

      return (zero_time - current) / (CLOCKS_PER_SEC / TFrequency);
    }

  private:

    clock_t zero_time;
};

#endif

