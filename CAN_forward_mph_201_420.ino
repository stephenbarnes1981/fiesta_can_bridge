#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg420;
struct can_frame canMsg201;
struct can_frame canMsg4B0;

MCP2515 mcp2515(53);


void setup() {
  
  while (!Serial);
  Serial.begin(500000);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();

  Serial.println("CAN BUS Initialised: 1000KBps");
  delay(2000);
  
  Serial.println("Dash Data: 0x201 0x420");
  delay(2000);
}

void loop() {

  if (mcp2515.readMessage(&canMsg4B0) == MCP2515::ERROR_OK)
  {
    if(canMsg4B0.can_id == 0x4B0)    //filtering based on CAN bus message ID.

  {
  
  canMsg420.can_id  = 0x420; // CAN ID
  canMsg420.can_dlc = 8;
  canMsg420.data[0] = 0x80; // ect
  canMsg420.data[1] = 0x00; // pressure
  canMsg420.data[2] = 0x00; // fuel flow
  canMsg420.data[3] = 0x00; // prndl
  canMsg420.data[4] = 0x00; // MIL/overdrive
  canMsg420.data[5] = 0x00; // safe cooling/PATS
  canMsg420.data[6] = 0x00; // charging system status
  canMsg420.data[7] = 0x00; // engine off elapsed time

  canMsg201.can_id  = 0x201; // CAN ID
  canMsg201.can_dlc = 8;
  canMsg201.data[0] = 0x27; // byte 1+2 = rpm*4
  canMsg201.data[1] = 0x10; // byte 1+2 = rpm*4
  canMsg201.data[2] = 0x00;
  canMsg201.data[3] = 0x00;
  canMsg201.data[4] = canMsg4B0.data[4]; // speed
  canMsg201.data[5] = canMsg4B0.data[5]; // speed
  canMsg201.data[6] = 0x00;
  canMsg201.data[7] = 0x00;

  mcp2515.sendMessage(&canMsg420);
  mcp2515.sendMessage(&canMsg201);

  Serial.println("Messages sent");
  
  delay(20);
    }
  }
}
