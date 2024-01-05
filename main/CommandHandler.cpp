#include <WiFi.h>
#include <WiFiClient.h>
#include "CommandHandler.h"


#define MAX_RETRIES 3
#define WORD_NUM_OF_BYTES 4 


// WIFI 
const char* ssid = "Bar1";
const char* password = "0526006314";
const char* serverAddress = "192.168.7.7";    // Do not change
const int serverPort = 12345;                 // Do not change
WiFiClient client;

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
 * 
 * @return If managed to succseed being slave
 */
uint8_t CommandHandler::begin() {
    uint8_t num_of_retries = 0;

    connectionType = RUNNING_MODE_STANDALONE;  // Fallback to standalone mode
    // Try to connect by WIFI/Serial
    M5.Lcd.println("Trying connect via Serial!");
    if (USBSerial)
    {
        USBSerial.setTimeout(10000);
        connectionType = RUNNING_MODE_SERIAL;
        M5.Lcd.println("Connected via Serial!");
    }
    else
    {
        WiFi.begin(ssid, password);
        M5.Lcd.println("Trying connect via WIFI!");
        while (num_of_retries < MAX_RETRIES) {      
            if (WiFi.status() == WL_CONNECTED)
            {
                break;
            }
            num_of_retries++;
            delay(1000);
        }
        if (num_of_retries < MAX_RETRIES)
        {
            num_of_retries = 0;
            while(num_of_retries < MAX_RETRIES)
            {
                if (client.connect(serverAddress, serverPort))
                {
                    connectionType = RUNNING_MODE_WIFI;
                    M5.Lcd.println("Connected via Wifi!");
                    client.setTimeout(10000);
                    break;
                }
                num_of_retries++;
                delay(1000);
            }
        }
    }
    M5.Lcd.print("Connection Type:");
    M5.Lcd.print(connectionType);
    M5.Lcd.println("");
    delay(5000);
    return (connectionType != RUNNING_MODE_STANDALONE);
}

/**
 * @brief Transmit data.
 */
void CommandHandler::txSlave() {
    if (connectionType == RUNNING_MODE_SERIAL)
    {
        txSerial();
    }
    else // connectionType == RUNNING_MODE_WIFI
    {
        txWifi();
    }

}

/**
 * @brief Transmit data over serial
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
 * @brief Transmit data over wifi
 */
void CommandHandler::txWifi() {
    uint32_t remainedBytes = 4;
    // Clean Rx Buffer
    rxNumOfBytes = 0;

     // Transmit the number of bytes that will be sent
    while (remainedBytes)
    {
        remainedBytes -= client.write((byte*)&txNumOfBytes, remainedBytes);
    }
    
    // Transmit the actual data
    remainedBytes = txNumOfBytes;
    while (remainedBytes)
    {
        remainedBytes -= client.write(TxBuffer + (txNumOfBytes - remainedBytes), remainedBytes);
    }

    // Reset the Tx buffer counter
    txNumOfBytes = 0;
}

/**
 * @brief Receive data from Serial.
 */
void CommandHandler::rxSlave() 
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(2);
    
    M5.Lcd.println("Pending for master command");
    M5.Lcd.print("Wifi mode? ");
    M5.Lcd.print(connectionType == RUNNING_MODE_WIFI);
    M5.Lcd.println("");

    /* Main handler */
    if (connectionType == RUNNING_MODE_SERIAL)
    {
        rxSerial();
    }
    else // connectionType == RUNNING_MODE_WIFI
    {
        rxWifi();
    }
}

void CommandHandler::rxSerial() {
     // Wait until data is available
    while(!USBSerial.available())
    {
        delay(10);
    } 

     // Read the incoming data
    USBSerial.readBytes(RxBuffer, WORD_NUM_OF_BYTES);
    commandHandler.rxNumOfBytes = commandHandler.bufferToUint32(RxBuffer);
    USBSerial.readBytes((RxBuffer + WORD_NUM_OF_BYTES), commandHandler.rxNumOfBytes);
}

void CommandHandler::rxWifi() {
    while(!client.available())
    {
        delay(10);
    }
     client.readBytes(RxBuffer, WORD_NUM_OF_BYTES);
     commandHandler.rxNumOfBytes = commandHandler.bufferToUint32(RxBuffer);
     client.readBytes((RxBuffer + WORD_NUM_OF_BYTES), commandHandler.rxNumOfBytes);
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