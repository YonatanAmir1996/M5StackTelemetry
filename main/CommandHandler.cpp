#include "CommandHandler.h"

CommandHandler commandHandler;

CommandHandler::CommandHandler()
  : LookupTable{
      [COMMAND_SHOW_USAGE] = &CommandHandler::commandShowUsage,
      [COMMAND_RUN]        = &CommandHandler::commandRun,
      [COMMAND_RESCAN]     = NULL
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

  USBSerial.println("");
  USBSerial.println("Welcome to M5Telemtry CLI. For usage type \"help\"");
  while (1) 
  {
       commandStr = "";
       USBSerial.printf("# ");
       while (true) {
         // Check for incoming data
         if (USBSerial.available() > 0) 
         {
              inChar = USBSerial.read();  // Read a character
              // If Enter key is pressed
              if ((inChar == '\n') || (inChar == '\r')) 
              {
                  USBSerial.println();
                  break;
              }
              // Backspace character
              else if (inChar == 8 || inChar == 127) 
              {
                   // Ensure string isn't empty
                   if (commandStr.length() > 0) 
                   {
                       commandStr.remove(commandStr.length() - 1);  // Remove the last character from the string
                       USBSerial.print("\b \b");                    // Move back, print space, move back - effectively deleting the char on terminal
                   }
              } 
              else 
              {
                  commandStr += inChar;  // Append character to command string
                  USBSerial.printf("%c", inChar);
              }
         }
         delay(1);  // A short delay to allow buffer to fill
       }

       /* From here commandStr should be same as WIFI mode ! */
       commandStr.trim();  // Right stripping \n, \r, whitespace
       commandName = getCommandName(commandStr);
       if (COMMAND_INVALID != commandName)
       {
           (this->*LookupTable[commandName])(commandStr);
       } 
       else
       {
           USBSerial.println("\nInvalid command. For usage type \"help\"");
       }
  }
}

Commands_e CommandHandler::getCommandName(String command) {
  Commands_e commandName = COMMAND_INVALID;

  if (command == "help") {
    commandName = COMMAND_SHOW_USAGE;
  }
  if (command.startsWith("run")) {
    commandName = COMMAND_RUN;
  }

  return commandName;
}


void CommandHandler::commandShowUsage(String command) {
  USBSerial.println("");
  USBSerial.println("M5Telemetry CLI was created by Yonatan Amir and Yuri Lukach");
  // Print Devices
  USBSerial.println("Supported Sensors and their bit:");
  USBSerial.printf("IMU=0x%X | HRU=0x%X | AMG=0x%X | ToF=0x%X | FSR=0x%X \n",
                   (1 << DEVICE_IMU),
                   (1 << DEVICE_HEART_UNIT_MAX_30100),
                   (1 << DEVICE_AMG8833_GRID_EYE),
                   (1 << DEVICE_VL3L5CX_TOF),
                   (1 << DEVICE_FSR402));
  USBSerial.println("Commands:");
  USBSerial.println("Activate Device/Sensor command:\"run bitmap=[DeviceNameBitmap], <fsrPbHubPort>=<0-6>\"");
}

void CommandHandler::commandRun(String command) {
  ArgumentParser_t args;

  command = command.substring(3);  // String("run").length()
  ArgsParser(command, &args);
}

void CommandHandler::ArgsParser(const String &command, ArgumentParser_t *argsStruct) {
    String cmdNotParsed;
    uint32_t startIndex = 0;
    uint32_t endIndex = command.indexOf(",");

    while ((endIndex != -1) && (argsStruct->numOfParams < MAX_ARGUMENTS)) 
    {
        cmdNotParsed = command.substring(startIndex, endIndex);
        cmdNotParsed.trim();
        argsStruct->arg[argsStruct->numOfParams] = parseKeyValue(cmdNotParsed);
        argsStruct->numOfParams++;
        startIndex = endIndex + 1;
        endIndex = command.indexOf(",", startIndex);
    }

    // Parse the last key-value pair after the last comma, if space is available in the array
    if (argsStruct->numOfParams < MAX_ARGUMENTS) 
    {
        cmdNotParsed = command.substring(startIndex);
        argsStruct->arg[argsStruct->numOfParams] = parseKeyValue(cmdNotParsed);
        argsStruct->numOfParams++;
    }

    USBSerial.println("Results: ");
    for (uint8_t param = 0; param < argsStruct->numOfParams; param++) 
    {
        USBSerial.print("argument ");
        USBSerial.print(argsStruct->arg[param].name);
        USBSerial.printf("| value=%X", argsStruct->arg[param].value);
    }
    USBSerial.println();
}

Arguments_t CommandHandler::parseKeyValue(const String &item) {
    Arguments_t argument;
    String tempNum;
    int equalsIndex = item.indexOf("=");

    if (equalsIndex != -1) 
    {
        argument.name = item.substring(0, equalsIndex);
        argument.name.trim();
        tempNum = item.substring(equalsIndex + 1);
        tempNum.trim();

        if ((tempNum.startsWith("0x") || tempNum.startsWith("0X")) && (isInteger(tempNum.substring(2)))) 
        {
            tempNum = tempNum.substring(2);
            // Convert hex string to integer
            char* endptr;
            argument.value = strtol(tempNum.c_str(), &endptr, 16); // Base 16 for hex
        } 
        else if (isInteger(tempNum)) 
        {
            argument.value = tempNum.toInt();
        } 
        else 
        {
            argument.value = INVALID_VALUE;
        }
    }
    return argument;
}

bool CommandHandler::isInteger(String input) {
    bool retVal = true;

    if (input.length() == 0) 
    {
        retVal = false;
    } 
    else 
    {
        for (unsigned int i = 0; i < input.length(); i++) 
        {
            char c = input[i];
            if (!isDigit(c) && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')) 
            {
                retVal = false;
                break;
            }
        }
    }
    return retVal;
}