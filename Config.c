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
#include "Config.h"

/**********************************************************************/
//////////////////////////////// INIT PSOC ////////////////////////////
void init_psoc(void) 
{
    /*En esta parte solo inicializo los modulos del psoc */
    UART_Start(); //Start UART module 
    SPI_Start();  //Start SPI module         
    wait500Ms(); //wait 500ms
    UART_UartPutString("  \n"); 
    UART_UartPutString("PSOC 5 LEADS TEST \n");
    UART_UartPutString("  \n");
    wait500Ms(); //wait 500ms
    dummyRead(); 
    /* Se realizan tres lecturas de prueba para sincronización con el dispositivo ads1293
    las primeras lecturas son erroneas por lo que realizo primero tres lecturas para luego obtener los 
    datos correctos*/
     
}
/*********************************************************/


/*********************************************************/
/////////////////// WAIT 500 MS ///////////////////////////
void wait500Ms(void)
{
    CyDelay(500); //wait 500ms
}
/*********************************************************/
void dummyRead(void)
{
    Test1=ADS1x9x_Reg_Read(ADS1293_R2_RATE_REG);//DummyRead
    Test1=ADS1x9x_Reg_Read(ADS1293_R2_RATE_REG);//DummyRead
    Test1=ADS1x9x_Reg_Read(ADS1293_R2_RATE_REG);//DummyRead
    // this part is necesary  
}

/* [] END OF FILE */
