#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "SharedDefines.h"
#include <M5CoreS3.h>

#define MAX_ARGUMENTS 10
#define INVALID_VALUE 0xFFFFFFFF

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

        void run(); 
        bool isConnected();
        void begin();
        bool isCommandReady();

        /* Commands parser*/
        

    private:
        typedef void (CommandHandler::*CallbackCommandFunction)(String);

        void        runSerialMode();     
        void        commandRun(String command);

    private:
        RunningMode_e           connectionType;
        CallbackCommandFunction LookupTable[COMMAND_MAX_COMMANDS];
};

extern CommandHandler commandHandler;

#endif // COMMAND_HANDLER_H