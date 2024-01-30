#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiMulti.h>
#include "CommandHandler.h"


#define MAX_RETRIES 10
#define WORD_NUM_OF_BYTES 4 

WiFiClient client;
WiFiMulti WiFiMulti;

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
uint8_t CommandHandler::begin(WifiStruct *pWifiDetails) {
    uint8_t num_of_retries = 0;

    connectionType = RUNNING_MODE_STANDALONE;  // Fallback to standalone mode
    // Try to connect by WIFI/Serial
    M5.Lcd.println("Trying connecting via Serial!");
    while (num_of_retries < 10)
    {
        if (USBSerial)
        {
          USBSerial.setTimeout(10000);
          connectionType = RUNNING_MODE_SERIAL;
          M5.Lcd.println("Connected via Serial!");
          break;
        }
        num_of_retries += 1;
        delay(400);
    }
    
    if (num_of_retries == 10)
    { 
        num_of_retries = 0;
        M5.Lcd.println("Trying connecting via WIFI!");
        M5.Lcd.print("SSID: ");
        M5.Lcd.print(pWifiDetails->ssid);
        M5.Lcd.println();
        M5.Lcd.print("Password: ");
        M5.Lcd.print(pWifiDetails->password);
        M5.Lcd.println();
        WiFiMulti.addAP(pWifiDetails->ssid, pWifiDetails->password);  // Add wifi configuration information.  添加wifi配置信息  
        while ((WiFiMulti.run() != WL_CONNECTED) && (num_of_retries < MAX_RETRIES))
        {     
            num_of_retries++;
            delay(400);
        }
        if (num_of_retries < MAX_RETRIES)
        {
            M5.Lcd.println("Try connecting server");
            M5.Lcd.print(pWifiDetails->serverAddress);
            M5.Lcd.print(":");
            M5.Lcd.print(pWifiDetails->serverPort);
            M5.Lcd.println();
            num_of_retries = 0;
            while(num_of_retries < MAX_RETRIES)
            {
                if (client.connect(pWifiDetails->serverAddress, pWifiDetails->serverPort))
                {
                    connectionType = RUNNING_MODE_WIFI;
                    M5.Lcd.println("Connected via Wifi!");
                    client.setTimeout(10000);
                    break;
                }
                num_of_retries++;
                delay(400);
            }
        }
    }
    M5.Lcd.print("Connection Type[0 - Serial | 1 - WIFI | 2 - Standalone]:");
    M5.Lcd.print(connectionType);
    M5.Lcd.println("");
    delay(5000);
    return (connectionType != RUNNING_MODE_STANDALONE);
}

/**
 * @brief Transmit data.
 */
void CommandHandler::txSlave() {
    // Clean Rx Buffer
    rxNumOfBytes = 0;
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
    uint32_t chunkSize = 32; // Size of each chunk
    uint32_t bytesSent = 0;  // Bytes sent in each iteration
    byte     *pBuf     = TxBuffer;
    // Transmit the number of bytes that will be sent
    USBSerial.write((byte*)&txNumOfBytes, sizeof(txNumOfBytes)); // Send 4 bytes representing the size
    USBSerial.flush(); // Ensure all data is sent
    // Transmit the actual data in chunks
    while (txNumOfBytes > 0) 
    {
        bytesSent = chunkSize < txNumOfBytes? chunkSize : txNumOfBytes;
        USBSerial.write(pBuf, bytesSent);     
        USBSerial.flush(); // Ensure all data is sent
        txNumOfBytes -= bytesSent;
        pBuf += bytesSent;
    }
}

/**
 * @brief Transmit data over wifi
 */
void CommandHandler::txWifi() {
    uint32_t chunkSize = 32; // Size of each chunk
    uint32_t bytesSent = 0;  // Bytes sent in each iteration
    byte     *pBuf     = TxBuffer;

    // Transmit the number of bytes that will be sent
    client.write((byte*)&txNumOfBytes, sizeof(txNumOfBytes)); // Send 4 bytes representing the size
    client.flush();  // Ensure all data is sent
    // Transmit the actual data in chunks
    while (txNumOfBytes > 0) 
    {
        bytesSent = chunkSize < txNumOfBytes? chunkSize : txNumOfBytes;
        client.write(pBuf, bytesSent);     
        client.flush(); // Ensure all data is sent
        txNumOfBytes -= bytesSent;
        pBuf += bytesSent;
    }
}

/**
 * @brief Receive data from master connection
 */
void CommandHandler::rxSlave() 
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(2);
    
    //M5.Lcd.println("Pending for master command");
    if (connectionType == RUNNING_MODE_WIFI)
    {
      M5.Lcd.println("Via WIFI");
    }
    else
    {
      //M5.Lcd.println("Via Serial");
    }

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

/**
 * @brief Receive data via serial
 */
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
    USBSerial.flush();
}

/**
 * @brief Receive data via wifi
 */
void CommandHandler::rxWifi() {
    // Wait until data is available
    while(!client.available())
    {
        delay(10);
    }
    // Read the incoming data
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