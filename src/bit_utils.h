/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef BIT_UTILS_H
#define BIT_UTILS_H

// Local Includes

// Project Includes

// External Includes

// Required classes

// A class which handles execution of the game.
template <typename TValueType>
class BitUtils
{
  public:
  
    template<int TBitMask>
    static TValueType GetHexValue(TValueType value);
};

#endif
