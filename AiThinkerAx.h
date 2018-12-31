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

#include "AiThinkerAx_Debug.h"

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

