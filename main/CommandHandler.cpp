#include "CommandHandler.h"

CommandHandler commandHandler;

CommandHandler::CommandHandler() : 
LookupTable
{
    [COMMAND_RESCAN_SENSORS]    = NULL,
    [COMMAND_RUN_SENSORS]       = &CommandHandler::commandRun,
    [COMMAND_AVAILABLE_DEVICES] = NULL,
} {}

CommandHandler::~CommandHandler() {}

void CommandHandler::begin() {
  // Try to connect by WIFI/Serial
  if (USBSerial) {
    connectionType = RUNNING_MODE_SERIAL;
  } else {
    // WIFI NOT SUPPORTED YET !
    // connectionType = RUNNING_MODE_WIFI;
    // Try to connect if fails change connection type to RUNNING_MODE_STANDALONE(which equivalents to failure in connection)
    connectionType = RUNNING_MODE_STANDALONE;
  }
}

bool CommandHandler::isConnected() {
  return (connectionType != RUNNING_MODE_STANDALONE);
}

bool CommandHandler::isCommandReady() {
  return false;
}

void CommandHandler::run() {
  /* Endless loop */
  if (RUNNING_MODE_SERIAL == connectionType) {
    CommandHandler::runSerialMode();
  }
}

void CommandHandler::runSerialMode() {
  String commandStr;
  char inChar;
  Commands_e commandName;

  while (1) 
  {
       commandStr = "";
       while (true) {
         // Check for incoming data
         if (USBSerial.available() > 0) 
         {
              byte buf[4];
              USBSerial.readBytes(buf, 4);
              int value = ((int)buf[0] << 24) | 
                ((int)buf[1] << 16) | 
                ((int)buf[2] << 8)  | 
                buf[3];
              M5.Lcd.printf("number of bytes to read %u", value);
              M5.Lcd.println(USBSerial.readString());
         }
         delay(1);  // A short delay to allow buffer to fill
       }
  }
}

void CommandHandler::commandRun(String command) 
{
}
