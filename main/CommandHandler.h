#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <M5CoreS3.h>
#include "SharedDefines.h"
#include <stdint.h>


#define MAX_ARGUMENTS 10
#define MAX_BUFFER_SIZE 1024 * 4 // 10 KB buffer

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
    private:
        void txSerial();
        void rxSerial();
        void txWifi();
        void rxWifi();
        
    public:
        CommandHandler();
        ~CommandHandler();

        uint8_t  begin(WifiStruct *pWifiDetails);
        void     txSlave();
        void     rxSlave();   
        uint32_t bufferToUint32(const byte* buffer);
  

    public:
        uint32_t                rxNumOfBytes;
        uint32_t                txNumOfBytes;

    private:
        RunningMode_e           connectionType;
};

extern byte           RxBuffer[MAX_BUFFER_SIZE];
extern byte           TxBuffer[MAX_BUFFER_SIZE];
extern CommandHandler commandHandler;

#endif // COMMAND_HANDLER_H