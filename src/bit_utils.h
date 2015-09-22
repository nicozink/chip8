/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef BIT_UTILS_H
#define BIT_UTILS_H

// Local Includes

// Project Includes

// External Includes
#include <stdint.h>

// Required classes

// A class which handles execution of the game.
template <typename TValueType>
class BitUtils
{
  public:
  
    template<int TBitMask>
    static inline TValueType GetHexValue(TValueType value);
};

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0xF000>(uint16_t value)
{
  return (value & 0xF000) >> 12;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x0F00>(uint16_t value)
{
  return (value & 0x0F00) >> 8;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x00F0>(uint16_t value)
{
  return (value & 0x00F0) >> 4;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x000F>(uint16_t value)
{
  return value & 0x000F;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0xFF00>(uint16_t value)
{
  return (value & 0xFF00) >> 8;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x0FF0>(uint16_t value)
{
  return (value & 0x0FF0) >> 4;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x00FF>(uint16_t value)
{
  return value & 0x00FF;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0xFFF0>(uint16_t value)
{
  return (value & 0xFFF0) >> 4;
}

template<>
template<>
inline uint16_t BitUtils<uint16_t>::GetHexValue<0x0FFF>(uint16_t value)
{
  return value & 0x0FFF;
}

#endif
