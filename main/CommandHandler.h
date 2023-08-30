#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "SharedDefines.h"
#include <stdint.h>
#include <M5CoreS3.h>

#define MAX_ARGUMENTS 10
#define MAX_BUFFER_SIZE 1024 * 2 // 10 KB buffer

typedef struct
{
    String   name;
    uint32_t value;
} Arguments_t;

typedef struct
{
    Arguments_t   arg[MAX_ARGUMENTS];
    uint8_t       numOfParams;
} ArgumentParser_t;


class CommandHandler 
{

    public:
        CommandHandler();
        ~CommandHandler();

        bool isConnected();
        void begin();
        bool isBufferReadyRead();
        void txSerial();
        void rxSerial();   
        uint32_t bufferToUint32(const byte* buffer);
  

    public:
        uint32_t                rxNumOfBytes;
        uint32_t                txNumOfBytes;

    private:
        RunningMode_e           connectionType;
        bool                    canReadBuffer;
};

extern byte           RxBuffer[MAX_BUFFER_SIZE];
extern byte           TxBuffer[MAX_BUFFER_SIZE];
extern CommandHandler commandHandler;

#endif // COMMAND_HANDLER_H