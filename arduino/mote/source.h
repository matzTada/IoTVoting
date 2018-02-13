/*
 * source.h
 * Author: Tada Matz
 * Comment: MyXBee class. simple XBee handler
 */

#ifndef SOURCE_H
#define SOURCE_H

#include "Arduino.h"
#include "XBee.h"

//==========class
class MyXBee {
  public:
    //=== members ===
    //XBee
    XBee xbee;
    //receive
    XBeeResponse response;
    ZBRxResponse rx; // create reusable response objects for responses we expect to handle
    //for send
    uint32_t txAddrHSB;
    uint32_t txAddrLSB;
    XBeeAddress64 txAddr64;
    ZBTxRequest txRequest;

    //=== methods ===
    MyXBee();
    void init(Stream &serial);
    //xbee
    void sendXBeeData(String payload);
    String receiveXBeeData();
};

#endif //ifndef SOURCE_H
