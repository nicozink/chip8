/*
Copyright © Nico Zink
All rights reserved.
*/

#include "program_controller.h" 

// Local Includes
#include "bit_utils.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <cstdlib>
#include <iostream>

ProgramController::ProgramController()
{
  
}

void ProgramController::Step(SystemState& state)
{
  uint8_t code1 = state.memory[state.program_counter];
  uint8_t code2 = state.memory[state.program_counter + 1];
  uint16_t command = code1 << 8 | code2;
  
  switch (command & 0xF000)
  {
    case 0x0000:
      if (command == 0x00E0)
      {
        Opcode_00E0(state, command);
      }
      else if (command == 0x00E0)
      {
        Opcode_00E0(state, command);
      }
      else
      {
        Opcode_00EE(state, command);
      }
      
      break;
      
    case 0x1000:
      Opcode_1NNN(state, command);
      break;
      
    case 0x2000:
      Opcode_2NNN(state, command);
      break;
      
    case 0x3000:
      Opcode_3XNN(state, command);
      break;
      
    case 0x4000:
      Opcode_4XNN(state, command);
      break;
      
    case 0x5000:
      Opcode_5XY0(state, command);
      break;
      
    case 0x6000:
      Opcode_6XNN(state, command);
      break;
      
    case 0x7000:
      Opcode_7XNN(state, command);
      break;
      
    case 0x8000:
      switch (command & 0x000F)
      {
        case 0x0000:
          Opcode_8XY0(state, command);
          break;
          
        case 0x0001:
          Opcode_8XY1(state, command);
          break;
          
        case 0x0002:
          Opcode_8XY2(state, command);
          break;
          
        case 0x0003:
          Opcode_8XY3(state, command);
          break;
          
        case 0x0004:
          Opcode_8XY4(state, command);
          break;
          
        case 0x0005:
          Opcode_8XY5(state, command);
          break;
          
        case 0x0006:
          Opcode_8XY6(state, command);
          break;
          
        case 0x0007:
          Opcode_8XY7(state, command);
          break;
          
        case 0x000E:
          Opcode_8XYE(state, command);
          break;
          
        default:
          std::cout << "Unknown command found: " << std::hex << command << std::endl;
          exit(0);
         
      }
      
      break;
      
    case 0x9000:
      Opcode_9XY0(state, command);
      break;
      
    case 0xA000:
      Opcode_ANNN(state, command);
      break;
      
    case 0xB000:
      Opcode_BNNN(state, command);
      break;
      
    case 0xC000:
      Opcode_CXNN(state, command);
      break;
      
    case 0xD000:
      Opcode_DXYN(state, command);
      break;
      
    case 0xE000:
      switch (command & 0x00FF)
      {
        case 0x009E:
          Opcode_EX9E(state, command);
          break;

        case 0x00A1:
          Opcode_EXA1(state, command);
          break;
        
        default:
          std::cout << "Unknown command found: " << std::hex << command << std::endl;
          exit(0);
      }
      
      break;
      
    case 0xF000:
      switch (command & 0x00FF)
      {
        case 0x0007:
          Opcode_FX07(state, command);
          break;
          
        case 0x000A:
          Opcode_FX0A(state, command);
          break;
          
        case 0x0015:
          Opcode_FX15(state, command);
          break;
          
        case 0x0018:
          Opcode_FX18(state, command);
          break;
          
        case 0x001E:
          Opcode_FX1E(state, command);
          break;
          
        case 0x0029:
          Opcode_FX29(state, command);
          break;
          
        case 0x0033:
          Opcode_FX33(state, command);
          break;
          
        case 0x0055:
          Opcode_FX55(state, command);
          break;
          
        case 0x0065:
          Opcode_FX65(state, command);
          break;
          
        default:
          std::cout << "Unknown command found: " << std::hex << command << std::endl;
          exit(0);
      }
      
      break;
      
    default:
      std::cout << "Unknown command found: " << std::hex << command << std::endl;
      exit(0);
  }
}

// Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_0NNN(SystemState& state, uint16_t command)
{
  std::cout << "Calls to RCA 1802 programs are not implemented." << std::endl;
  exit(0);
}

// Clears the screen.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_00E0(SystemState& state, uint16_t command)
{
  for (int i = 0; i < Globals::NUM_PIXELS; ++i)
  {
    state.display[i] = false;
  }
  
  state.program_counter += 2;
}

// Returns from a subroutine.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_00EE(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Jumps to address NNN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_1NNN(SystemState& state, uint16_t command)
{
  state.program_counter = BitUtils<uint16_t>::GetHexValue<0x0FFF>(command);
}

// Calls subroutine at NNN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_2NNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Skips the next instruction if VX equals NN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_3XNN(SystemState& state, uint16_t command)
{
  uint16_t register_index = BitUtils<uint16_t>::GetHexValue<0x0F00>(command);
  uint16_t value = BitUtils<uint16_t>::GetHexValue<0x00FF>(command);
  
  if (state.registers[register_index] == value)
  {
    state.program_counter += 4;
  }
  else
  {
    state.program_counter += 2;
  }
}

// Skips the next instruction if VX doesn't equal NN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_4XNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Skips the next instruction if VX equals VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_5XY0(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to NN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_6XNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Adds NN to VX.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_7XNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to the value of VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY0(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to VX or VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY1(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to VX and VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY2(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to VX xor VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY3(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY4(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY5(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.[2]
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY6(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XY7(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.[2]
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_8XYE(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Skips the next instruction if VX doesn't equal VY.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_9XY0(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets I to the address NNN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_ANNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Jumps to the address NNN plus V0.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_BNNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to the result of a bitwise and operation on a random number and NN.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_CXNN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sprites stored in memory at location in index register (I), 8bits wide. Wraps around the screen. If when drawn, clears a
// pixel, register VF is set to 1 otherwise it is zero. All drawing is XOR drawing (i.e. it toggles the screen pixels).
// Sprites are drawn starting at position VX, VY. N is the number of 8bit rows that need to be drawn. If N is greater than
// 1, second line continues at position VX, VY+1, and so on.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_DXYN(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Skips the next instruction if the key stored in VX is pressed.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_EX9E(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Skips the next instruction if the key stored in VX isn't pressed.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_EXA1(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets VX to the value of the delay timer.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX07(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// A key press is awaited, and then stored in VX.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX0A(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets the delay timer to VX.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX15(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets the sound timer to VX.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX18(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Adds VX to I.[3]
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX1E(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX29(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle
// digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place
// the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX33(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Stores V0 to VX in memory starting at address I.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX55(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}

// Fills V0 to VX with values from memory starting at address I.
// @param state The current system state.
// @param command The current opcode.
void ProgramController::Opcode_FX65(SystemState& state, uint16_t command)
{
  std::cout << "Opcode " << command << " not implemented." << std::endl;
  exit(0);
}
