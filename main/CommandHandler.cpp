#include "CommandHandler.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

byte          RxBuffer[MAX_BUFFER_SIZE] = {0};
byte          TxBuffer[MAX_BUFFER_SIZE] = {0};
CommandHandler commandHandler;

CommandHandler::CommandHandler() : canReadBuffer(false), rxNumOfBytes(0), txNumOfBytes(0)
{}

CommandHandler::~CommandHandler() {}

void CommandHandler::begin() {
  // Try to connect by WIFI/Serial
  if (USBSerial) 
  {
      USBSerial.setTimeout(10000);
      connectionType = RUNNING_MODE_SERIAL;
  } 
  else
  {
      // WIFI NOT SUPPORTED YET !
      // connectionType = RUNNING_MODE_WIFI;
      // Try to connect if fails change connection type to RUNNING_MODE_STANDALONE(which equivalents to failure in connection)
      connectionType = RUNNING_MODE_STANDALONE;
  }
}

bool CommandHandler::isConnected() {
  return (connectionType != RUNNING_MODE_STANDALONE);
}

bool CommandHandler::isBufferReadyRead() {
  return canReadBuffer;
}

void CommandHandler::txSerial() {
    uint32_t remainedBytes = 4;
    // Clean Rx Buffer
    rxNumOfBytes = 0;

    // Send number of bytes that will be sent
    while (remainedBytes)
    {
        remainedBytes -= USBSerial.write((byte*)&txNumOfBytes, remainedBytes);
    }
    USBSerial.flush();
    remainedBytes = txNumOfBytes;
    while (remainedBytes)
    {
        remainedBytes -= USBSerial.write(TxBuffer + (txNumOfBytes - remainedBytes), remainedBytes);
    }
    USBSerial.flush();
    txNumOfBytes = 0;
    // Clean TX buffer
    canReadBuffer = false; // Waiting for data
}

void CommandHandler::run() {
  /* Endless loop */
  if (RUNNING_MODE_SERIAL == connectionType) {
    CommandHandler::runSerialMode();
  }
}

void CommandHandler::runSerialMode() 
{
    while (1) 
    {
        // Check for incoming data
        if (USBSerial.available() > 0) 
        {
            USBSerial.readBytes(RxBuffer, 4);
            rxNumOfBytes = bufferToUint32(RxBuffer);
            USBSerial.readBytes((RxBuffer + 4), rxNumOfBytes);
            canReadBuffer = true;
            while(canReadBuffer)
            {
                delay(100);  // A short delay to allow buffer to fill
            }
        }
        delay(1);
    }
}

uint32_t CommandHandler::bufferToUint32(const byte* buffer)
{
     return ((uint32_t)buffer[0] << 24) |  ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8)  | buffer[3];
}