/**
  ******************************************************************************
  * @file    AiThinkerAx.h
  * @author  Leonardo Cavagnis
  * @version V1.0.0
  * @brief   
  *
  ******************************************************************************
  */

#ifndef AiThinkerAx_h
#define AiThinkerAx_h

#include "Arduino.h"
#include "HardwareSerial.h"
#include "SoftwareSerial.h"

//#define DEBUG

#ifdef DEBUG
  #define DBGPrint(data) Serial.print(data)
  #define DBGPrintln(data) Serial.println(data)
#else
  #define DBGPrint(data)
  #define DBGPrintln(data)
#endif

class AiThinkerAx
{
  public:
    AiThinkerAx();
    AiThinkerAx(HardwareSerial& serialAT) : _serialAT(serialAT)
    {
      _hwSerial  = true;
    } 
    AiThinkerAx(SoftwareSerial& serialAT) : _serialAT(serialAT)
    {
      _hwSerial  = false;
    } 
    bool begin(long baudrate);
    void end();
    bool sendSMS(String phoneNum, String textMess);
  private:
    Stream& _serialAT;
    bool    _hwSerial;

    void    _portBegin(long baudrate);
    long    _portGetBaud();
    bool    _portRead(String cmdResp, unsigned long timeoutMs);
};

#endif /* AiThinkerAx_h */

