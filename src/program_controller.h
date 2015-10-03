/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef PROGRAM_CONTROLLER_H
#define PROGRAM_CONTROLLER_H

// Local Includes
#include "bit_utils.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <stdint.h>

// Required classes
class SystemState;

// A class which handles execution of the game.
class ProgramController
{
  public:
  
    ProgramController();
    
    void Step(SystemState& system_state);
    
  private:
  
    void Opcode_0NNN(SystemState& state, uint16_t command);

    void Opcode_00E0(SystemState& state, uint16_t command);

    void Opcode_00EE(SystemState& state, uint16_t command);

    void Opcode_1NNN(SystemState& state, uint16_t command);

    void Opcode_2NNN(SystemState& state, uint16_t command);

    void Opcode_3XNN(SystemState& state, uint16_t command);

    void Opcode_4XNN(SystemState& state, uint16_t command);

    void Opcode_5XY0(SystemState& state, uint16_t command);

    void Opcode_6XNN(SystemState& state, uint16_t command);

    void Opcode_7XNN(SystemState& state, uint16_t command);

    void Opcode_8XY0(SystemState& state, uint16_t command);

    void Opcode_8XY1(SystemState& state, uint16_t command);

    void Opcode_8XY2(SystemState& state, uint16_t command);

    void Opcode_8XY3(SystemState& state, uint16_t command);

    void Opcode_8XY4(SystemState& state, uint16_t command);

    void Opcode_8XY5(SystemState& state, uint16_t command);

    void Opcode_8XY6(SystemState& state, uint16_t command);

    void Opcode_8XY7(SystemState& state, uint16_t command);

    void Opcode_8XYE(SystemState& state, uint16_t command);

    void Opcode_9XY0(SystemState& state, uint16_t command);

    void Opcode_ANNN(SystemState& state, uint16_t command);

    void Opcode_BNNN(SystemState& state, uint16_t command);

    void Opcode_CXNN(SystemState& state, uint16_t command);

    void Opcode_DXYN(SystemState& state, uint16_t command);

    void Opcode_EX9E(SystemState& state, uint16_t command);

    void Opcode_EXA1(SystemState& state, uint16_t command);

    void Opcode_FX07(SystemState& state, uint16_t command);

    void Opcode_FX0A(SystemState& state, uint16_t command);

    void Opcode_FX15(SystemState& state, uint16_t command);

    void Opcode_FX18(SystemState& state, uint16_t command);

    void Opcode_FX1E(SystemState& state, uint16_t command);

    void Opcode_FX29(SystemState& state, uint16_t command);

    void Opcode_FX33(SystemState& state, uint16_t command);

    void Opcode_FX55(SystemState& state, uint16_t command);

    void Opcode_FX65(SystemState& state, uint16_t command);
    
    template <int TBitMask>
    inline uint8_t UpdateDisplayBit(SystemState& state, int row, int col, uint8_t data)
    {
      bool value = BitUtils<uint8_t>::GetBitValue<TBitMask>(data);
      
      if (value)
      {
        int i = SystemState::GetDisplayIndex(row % Globals::DISPLAY_ROWS, col % Globals::DISPLAY_COLUMNS);

        state.display[i] = value ^ state.display[i];

        return !(state.display[i] & value);
      }
      
      return false;
    }
};

#endif

