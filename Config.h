/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#if !defined(Config_H)
#define Config_H
    
/**************************************************************/  
/////////////////////// Libraries/////////////////////////////// 
#include "project.h"
#include "Ads1293.h"
#include "stdio.h"      
#include "math.h"    
#include "stdint.h"     
#include "stdlib.h"   
/**************************************************************/  
    
/**************************************************************/    
///////////////////////// DEFINES //////////////////////////////    
#define true    1
#define false   0    
#define CH_DATA_SIZE 9 
#define OFF false
#define ON true    
#define ZERO 0
/**************************************************************/    
    
/**************************************************************/   
///////////////////////// General Variables ////////////////////      
char uartMessage[32];    
extern uint8 count;
extern uint32 PrintOn;
uint8 Test1;
/*************************************************************/   

/**************************************************************/
/****************************FUNCTIONS*************************/
void init_psoc(void);
void wait500Ms(void);
void dummyRead(void);

/**************************************************************/

#endif    
/* [] END OF FILE */
