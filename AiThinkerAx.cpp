/**
  ******************************************************************************
  * @file    AiThinkerAx.cpp
  * @author  Leonardo Cavagnis
  * @version V1.0.0
  * @brief   
  *
  ******************************************************************************
  */
#include "AiThinkerAx.h"

bool AiThinkerAx::begin(long baudrate)
{
  long currentBaudrate;

  currentBaudrate = _portGetBaud();

  if(currentBaudrate != baudrate){
    _serialAT.print("AT+IPR=");
    _serialAT.print(baudrate);
    _serialAT.print("\r\n");

    if(_portRead("OK", 3000)){

      currentBaudrate = _portGetBaud();    

      if(currentBaudrate != baudrate) return false;
    }
    else{
      return false;
    }
  }

  _serialAT.print("AT+CMEE=0\r\n");

  if(!_portRead("OK", 3000)){
    return false;
  }

  _serialAT.print("AT+CMER=3,0,0,2\r\n");

  if(!_portRead("OK", 3000)){
    return false;
  }

  _serialAT.print("AT+CPIN?\r\n");

  if(!_portRead("+CPIN:READY", 3000)){
    return false;
  }

  return true;
}

void AiThinkerAx::end()
{
  //TODO
}

bool AiThinkerAx::sendSMS(String phoneNum, String textMess){
  _serialAT.print("AT+CMGF=1\r\n");

  if(!_portRead("OK", 3000)){
    return false;
  }

  delay(100);

  _serialAT.print("AT+CMGS=\""+phoneNum+"\"\r\n");

  if(!_portRead(">", 3000)){
    return false;
  }

  delay(100);

  _serialAT.print(textMess);
  _serialAT.write(0x1A);

  delay(100);
  return true;
}
  
void AiThinkerAx::_portBegin(long baudrate)
{
  if(_hwSerial) {
    static_cast<HardwareSerial*>(&_serialAT)->begin(baudrate);
  } else {
    static_cast<SoftwareSerial*>(&_serialAT)->begin(baudrate);
  }
}

long AiThinkerAx::_portGetBaud()
{
  static long rates[] = { 115200, 57600, 38400, 19200, 9600, 74400, 74880, 230400, 460800, 2400, 4800, 14400, 28800 };

  for (unsigned i = 0; i < sizeof(rates)/sizeof(rates[0]); i++) {
    long rate = rates[i];

    DBGPrint("Test baudrate ");
    DBGPrintln(rate);

    _portBegin(rate);
    delay(10);
    for (int i=0; i<3; i++) {
      _serialAT.print("AT\r\n");
      String input = _serialAT.readString();
      if (input.indexOf("OK") >= 0) {
        DBGPrint("Detected baudrate ");
        DBGPrintln(rate);
        return rate;
      }
    }
  }
  return 0;
}

bool AiThinkerAx::_portRead(String cmdResp, unsigned long timeoutMs) {
  unsigned long startMs = 0;
  String        readStr = "";
  bool          result  = false;

  startMs = millis();

  do {
    if (_serialAT.available()) {
      readStr = _serialAT.readString();
    }
  } while ( (readStr.indexOf(cmdResp) == -1) && (millis() - startMs < timeoutMs) );

  if ((millis() - startMs) >= timeoutMs) {
    result = false;
  } else {
    if (readStr.indexOf(cmdResp) != -1) { result = true; }
    else { result = false; }
  }

  return result;
}