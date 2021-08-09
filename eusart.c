#include "eusart.h"



/**
  Section: Global Variables
*/

static uint8_t eusartTxHead = 0;
//static uint8_t eusartTxTail = 0;
static uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile uint8_t eusartTxBufferRemaining;

static uint8_t eusartRxHead = 0;
static uint8_t eusartRxTail = 0;
static uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];
volatile uint8_t eusartRxCount;


void putch(char data)
{
 while( ! TXIF)
 continue;
 TXREG = data;
}


void init_uart(void)
{
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;
    TXSTAbits.SYNC = 0; // 0 = Asynchronous mode
    TXSTAbits.TXEN = 1; // 1 = Transmit enabled
    RCSTAbits.CREN = 1; // 1 = Enables receiver
    RCSTAbits.SPEN = 1; // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)


    TXSTAbits.BRGH = 1; // 1 = High speed
    SPBRG = 0x33;


    
    // BAUD = FOSC/[16 (n + 1)]
    // n = value of SPBRGH:SPBRG register pair
    //  SPBRGH:SPBRG = ((8000000/9600)/16) - 1 = 51
    // BAUDRATE = 8000000/(16*(51 + 1) = 9615
    // ERROR = (96156 - 9600)/9600 = 0.16%
    

    
        // initializing the driver state
    eusartTxHead = 0;
   // eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof(eusartTxBuffer);

    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;
    
        // enable receive interrupt
   // PIE1bits.RCIE = 1;
}

uint8_t EUSART_Read(void) {
    uint8_t readValue = 0;

    while (0 == eusartRxCount) {
    }

    readValue = eusartRxBuffer[eusartRxTail++];
    if (sizeof (eusartRxBuffer) <= eusartRxTail) {
        eusartRxTail = 0;
    }
    PIE1bits.RCIE = 0;
    eusartRxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}

void EUSART_Write(uint8_t txData) {
    while (0 == eusartTxBufferRemaining) {
    }

    if (0 == PIE1bits.TXIE) {
        while (!TXIF)
            continue;
        TXREG = txData;
        // TXREG = txData;
    } else {
        PIE1bits.TXIE = 0;
        eusartTxBuffer[eusartTxHead++] = txData;
        if (sizeof (eusartTxBuffer) <= eusartTxHead) {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining--;
    }
    //  PIE1bits.TXIE = 1;
}


//========================================
//           Передача строки
//========================================

void EUSART_Write_Str(const unsigned char *t) {
    while (*t != '\0') {
        EUSART_Write(*t);
        *t++;
    }
}


//=========================================
//  деініціалізувати прийомник (очистити)
//=========================================

void reinit_rx() {
    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;
}



// переривання по прийомі порта

//void EUSART_Receive_ISR(void) {
//
//    if (1 == RCSTAbits.OERR) {
//        // EUSART error - restart
//
//        RCSTAbits.CREN = 0;
//        RCSTAbits.CREN = 1;
//    }
//
//    // buffer overruns are ignored
//    eusartRxBuffer[eusartRxHead++] = RCREG;
//    if (sizeof (eusartRxBuffer) <= eusartRxHead) {
//        eusartRxHead = 0;
//    }
//    
//    if ((eusartRxCount++) >= sizeof (eusartRxBuffer) )
//        eusartRxCount = 0;
//        
//}