#include "CommandHandler.h"

// Buffer definitions
byte RxBuffer[MAX_BUFFER_SIZE] = {0};  /**< Receive buffer. */
byte TxBuffer[MAX_BUFFER_SIZE] = {0};  /**< Transmit buffer. */
CommandHandler commandHandler;         /**< Command handler instance. */

/**
 * @brief Default constructor that initializes member variables.
 */
CommandHandler::CommandHandler() : rxNumOfBytes(0), txNumOfBytes(0)
{}

/**
 * @brief Destructor. Currently empty but can be expanded if required in the future.
 */
CommandHandler::~CommandHandler() {}

/**
 * @brief Initialization function to establish a connection.
 * 
 * Tries to establish a connection either via USBSerial or WIFI.
 */
void CommandHandler::begin() {
  // Try to connect by WIFI/Serial
  if (USBSerial) 
  {
      USBSerial.setTimeout(10000);
      connectionType = RUNNING_MODE_SERIAL;
  } 
  else
  {
     // WIFI connection is currently not supported
      connectionType = RUNNING_MODE_STANDALONE;  // Fallback to standalone mode
  }
}

/**
 * @brief Checks if there's an active connection.
 * 
 * @return Returns true if connected, otherwise false.
 */
bool CommandHandler::isConnected() {
  return (connectionType != RUNNING_MODE_STANDALONE);
}

/**
 * @brief Transmit data over Serial.
 */
void CommandHandler::txSerial() {
    uint32_t remainedBytes = 4;
    // Clean Rx Buffer
    rxNumOfBytes = 0;

     // Transmit the number of bytes that will be sent
    while (remainedBytes)
    {
        remainedBytes -= USBSerial.write((byte*)&txNumOfBytes, remainedBytes);
    }

     // Transmit the actual data
    remainedBytes = txNumOfBytes;
    while (remainedBytes)
    {
        remainedBytes -= USBSerial.write(TxBuffer + (txNumOfBytes - remainedBytes), remainedBytes);
    }

    // Reset the Tx buffer counter
    txNumOfBytes = 0;
}

/**
 * @brief Receive data from Serial.
 */
void CommandHandler::rxSerial() 
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(2);
    /* Main handler */
    M5.Lcd.println("Pending for master command");

     // Wait until data is available
    while(!USBSerial.available())
    {
        delay(10);
    } 

     // Read the incoming data
    USBSerial.readBytes(RxBuffer, 4);
    commandHandler.rxNumOfBytes = commandHandler.bufferToUint32(RxBuffer);
    USBSerial.readBytes((RxBuffer + 4), commandHandler.rxNumOfBytes);
}

/**
 * @brief Convert a 4-byte buffer into a uint32_t value.
 * 
 * @param buffer 4-byte array to be converted.
 * @return Converted uint32_t value.
 */
uint32_t CommandHandler::bufferToUint32(const byte* buffer)
{
     return ((uint32_t)buffer[0] << 24) |  ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8)  | buffer[3];
}