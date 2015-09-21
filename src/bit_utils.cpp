/*
Copyright © Nico Zink
All rights reserved.
*/

#include "bit_utils.h" 

// Local Includes

// Project Includes

// External Includes
#include <stdint.h>

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0xF000>(uint16_t value)
{
  return (value & 0xF000) >> 12;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x0F00>(uint16_t value)
{
  return (value & 0x0F00) >> 8;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x00F0>(uint16_t value)
{
  return (value & 0x00F0) >> 4;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x000F>(uint16_t value)
{
  return value & 0x000F;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0xFF00>(uint16_t value)
{
  return (value & 0xFF00) >> 8;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x0FF0>(uint16_t value)
{
  return (value & 0x0FF0) >> 4;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x00FF>(uint16_t value)
{
  return value & 0x00FF;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0xFFF0>(uint16_t value)
{
  return (value & 0xFFF0) >> 4;
}

template<>
template<>
uint16_t BitUtils<uint16_t>::GetHexValue<0x0FFF>(uint16_t value)
{
  return value & 0x0FFF;
}
