/**
  ******************************************************************************
  * @file    AiThinkerAx_Debug.h
  * @author  Leonardo Cavagnis
  * @version V1.0.0
  * @brief   
  *
  ******************************************************************************
  */

#ifndef AiThinkerAx_Debug_h
#define AiThinkerAx_Debug_h

//#define AITHINKERAX_ENABLE_DBG
#define AITHINKERAX_DBG_SERIAL		Serial

#ifdef AITHINKERAX_ENABLE_DBG
  #ifndef AITHINKERAX_DBG_SERIAL
    #define DBGPrint(data)    Serial.print(data)
    #define DBGPrintln(data)  Serial.println(data)
  #else
    #define DBGPrint(data)    AITHINKERAX_DBG_SERIAL.print(data)
    #define DBGPrintln(data)  AITHINKERAX_DBG_SERIAL.println(data)
  #endif
#else
  #define DBGPrint(data)
  #define DBGPrintln(data)
#endif

 #endif /* AiThinkerAx_Debug_h */
