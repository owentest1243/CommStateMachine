#ifndef USARTDRIVER_H
#define USARTDRIVER_H
#include "UsartEvent.h"
#include "UsartHardware.h"
#include "TimerEvent.h"
#include "Usart.h"
#include "SM_Common.h"

typedef enum{
    WAIT_FOR_PACKET_HEADER,
    WAIT_FOR_PACKET_PAYLOAD,
} RxHandlerState;

typedef struct UsartDriverInfo UsartDriverInfo;
struct UsartDriverInfo {
    UsartEvent * rxUsartEvent;
    UsartEvent * txUsartEvent;
    char * activeRxBuffer;
    char * spareRxBuffer;
    RxHandlerState state;
    int requestTxPacket;
    int requestRxPacket;
};

STATIC char * getRxPacket(UsartDriverInfo *info);
STATIC int getPacketLength(char * txData);
STATIC int isCorrectAddress(UsartDriverInfo *info);
void usartInit();
void usartConfig(UsartPort port,int baudRate,OversampMode overSampMode,ParityMode parityMode,
               WordLength length,StopBit sBitMode,EnableDisable halfDuplex);
//need to add more config inside
void usartDriverTransmit(UsartPort port, char * txData,UsartEvent * event);
void usartDriverReceive(UsartPort port, char * txData,UsartEvent * event);
// the data store is retrieved in the UsartEvent

void usartRemoveReceivefromQueue(UsartPort port , UsartEvent * event);
void usartRemoveReceiveTimer(UsartPort port , TimerEvent * event);

void usartRxCompletionHandler(UsartPort port);
void usartTxCompletionHandler(UsartPort port);
#endif // USARTDRIVER_H
