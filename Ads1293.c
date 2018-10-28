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

#include "Ads1293.h" 

/**********************************************************************************************************
* ADS1x9x_Reset			 			                                         						  	  *
**********************************************************************************************************/
void ADS1x9x_Reset(void)
{
        PWDN_Write(1);                                      // Set High
        CyDelay(5);  				                        // Wait 1 mSec        
	    /* Provide suficient delay*/
        PWDN_Write(0);                                  	// Set to low
        CyDelay(5);  				                        // Wait 1 mSec     
        
        PWDN_Write(1);                                      // Set High
        CyDelay(10);                 				        // Wait 1 mSec
}
/*********************************************************************************************************/

/**********************************************************************************************************
* Set_ADS1x9x_Chip_Enable																                  *
**********************************************************************************************************/
void Set_ADS1x9x_Chip_Enable (void)
{
	/* ADS1x9x CS is Active low*/
   CS_Write(0);// Set to LOW
//    CyDelay(1);		
}
/********************************************************************************************************/

/**********************************************************************************************************
* Clear_ADS1x9x_Chip_Enable						                                          			  *
**********************************************************************************************************/
void Clear_ADS1x9x_Chip_Enable (void)
  {
	/* ADS1x9x CS is Active high*/    
  	CS_Write(1);// Set to High
//    CyDelay(1);
  }
/*********************************************************************************************************/

/*********************************************************************************************************
* ADS1x9x_Reg_Read																	                 *
**********************************************************************************************************/
unsigned char ADS1x9x_Reg_Read(unsigned char Reg_address) //Leer Registro 
  {
  		uint32 retVal;
		SPI_Tx_buf[0] = Reg_address | ADS1293_READ_BIT;         // Send register Address to read
		SPI_Tx_buf[1] = 0;							// Dummy value
		Set_ADS1x9x_Chip_Enable();					// Set chip select to low
//        CyDelay(1);
        CyDelayUs(100);        
        SPI_WriteTxData(SPI_Tx_buf[0]);                     // Send the first data to the TX Buffer
        while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // USCI_B0 TX buffer ready?

        SPI_WriteTxData(SPI_Tx_buf[1]);                     //Dummy write so we can read data
        while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // USCI_B0 TX buffer ready?	
        
        retVal = SPI_ReadRxData();  						// Read RX buff        

        Clear_ADS1x9x_Chip_Enable();				// Disable chip select	        
//        CyDelay(1);
        CyDelayUs(100);        
        return 	retVal;
  }
/*********************************************************************************************************/

/*********************************************************************************************************
* ADS1x9x_Auto_Inc_Reg_Read																	                 *
**********************************************************************************************************/
void ADS1x9x_Auto_Inc_Reg_Read (unsigned char Reg_address, uint8_t *buffer, uint8_t count) //Leer N registros
  { 
    uint8 i=0;
    uint8 Dummy=0;
	SPI_Tx_buf[0] = Reg_address | ADS1293_READ_BIT; //Register Address
    
	Set_ADS1x9x_Chip_Enable();// CS enable
    CyDelay(5);
    
    SPI_WriteTxData(SPI_Tx_buf[0]);                     /// Send an address

    for(i=0; i<count;i++)
    {
        while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE

        SPI_WriteTxData(Dummy);// Dummy Write so can read data
        while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
        
        *(buffer+i) = SPI_ReadRxData();//Read data        
    }
        
	Clear_ADS1x9x_Chip_Enable();// CS disable  
    CyDelay(5);
  }
/*********************************************************************************************************/
/*********************************************************************************************************
* ADS1x9x_Stream_Reg_Read																	                 *
**********************************************************************************************************/
void ADS1x9x_Stream_Reg_Read (uint8_t *buffer, uint8_t count) // Stream Read ver Datasheet del dispositivo
  { 
    uint8 temporal = count;
    
    SPI_Tx_buf[0]=0;
    
	SPI_Tx_buf[0] = ADS1293_DATA_LOOP_REG | ADS1293_READ_BIT; //Read from data loop register
	Set_ADS1x9x_Chip_Enable();// CS enable        
    CyDelayUs(500);//Test 2 
    
    SPI_WriteTxData(SPI_Tx_buf[0]);               /// Send an address
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE 
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE    
    buffer[9] = SPI_ReadRxData();//Read data //STATUS   
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[0] = SPI_ReadRxData();//Read data //
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[1] = SPI_ReadRxData();//Read data //        
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[2] = SPI_ReadRxData();//Read data //  
//
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[3] = SPI_ReadRxData();//Read data //
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[4] = SPI_ReadRxData();//Read data //    
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[5] = SPI_ReadRxData();//Read data //  
//    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[6] = SPI_ReadRxData();//Read data //
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[7] = SPI_ReadRxData();//Read data //   
    
    SPI_WriteTxData(0);// Dummy Write so can read data 
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    buffer[8] = SPI_ReadRxData();//Read data //    
    
//    SPI_WriteTxData(0);// Dummy Write so can read data
    /*Nota: Revisar la salida  comentando esta linea de codigo
    podria no ser necesario esta ultima escritura */

	Clear_ADS1x9x_Chip_Enable();// CS disable  

    CyDelayUs(500);//Test 2       
  }
/*********************************************************************************************************/

/*********************************************************************************************************
* ADS1x9x_Reg_Write																	                 *
**********************************************************************************************************/
void ADS1x9x_Reg_Write (unsigned char WRITE_ADDRESS, unsigned char DATA) // Escribir un registro
  { 

	SPI_Tx_buf[0] = WRITE_ADDRESS & ADS1293_WRITE_BIT;
	SPI_Tx_buf[1] = DATA;					// Write Single byte
    
	Set_ADS1x9x_Chip_Enable();// CS enable
    CyDelay(5);
    
    SPI_WriteTxData(SPI_Tx_buf[0]);                     /// Send an address
    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
    
	SPI_WriteTxData(SPI_Tx_buf[1]);                     // Send the first data to the TX Buffer
	while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE));	// USCI_B0 TX buffer ready? or SPI_STS_BYTE_COMPLETE
//	i = SPI_ReadRxData();

	Clear_ADS1x9x_Chip_Enable();// CS disable  
    CyDelay(5);    
  }
/*********************************************************************************************************/

/*********************************************************************************************************
* ADS1x9x_Auto_Inc_Reg_Write																	                 *
**********************************************************************************************************/
void ADS1x9x_Auto_Inc_Reg_Write (unsigned char WRITE_ADDRESS, uint8_t *buffer, unsigned char count) // Escribir N registros
  { 
    uint8 i=0;
	SPI_Tx_buf[0] = WRITE_ADDRESS & ADS1293_WRITE_BIT;
//	SPI_Tx_buf[1] = DATA;					// Write Single byte
    
	Set_ADS1x9x_Chip_Enable();// CS enable

    while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait for TXBUF ready
    SPI_WriteTxData(SPI_Tx_buf[0]);                     /// Send an address
    
    for(i=0; i<count;i++)
    {
        while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE)); // Wait to complete byte   or SPI_STS_BYTE_COMPLETE
        SPI_WriteTxData(*buffer+i);
    }
        
	while(0u==(SPI_ReadTxStatus() & SPI_STS_SPI_DONE));	// USCI_B0 TX buffer ready? or SPI_STS_BYTE_COMPLETE

	Clear_ADS1x9x_Chip_Enable();// CS disable    
  }
/*********************************************************************************************************/

/**********************************************************************************************************
* Initialize ADS1x9x						                                          *
**********************************************************************************************************/
void Init_ADS1x9x (void) // Configuración inicial del dispositivo 
{
    char uartMessage[32];  
    uint16 temporal=0;

    ADS1x9x_Reg_Write(ADS1293_CONFIG_REG,0x00);//Stop data conversion
    temporal=ADS1x9x_Reg_Read(ADS1293_CONFIG_REG);
    sprintf(uartMessage, "CONFIG_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);    
    
    ADS1x9x_Reg_Write(ADS1293_FLEX_CH1_CN_REG,0x11);// Connect channel 1's INP to IN2 and INN to IN1 
    temporal=ADS1x9x_Reg_Read(ADS1293_FLEX_CH1_CN_REG);
    sprintf(uartMessage, "FLEX_CH1_CN : %i\n",temporal); // 
    UART_UartPutString(uartMessage);    

    ADS1x9x_Reg_Write(ADS1293_FLEX_CH2_CN_REG,0x19);// Connect channel 2's INP to IN3 and INN to IN1
    temporal=ADS1x9x_Reg_Read(ADS1293_FLEX_CH2_CN_REG);
    sprintf(uartMessage, "FLEX_CH2_CN : %i\n",temporal); // 
    UART_UartPutString(uartMessage);  

    ADS1x9x_Reg_Write(ADS1293_FLEX_CH3_CN_REG,0x2E);// Connect channel 3's INP to IN5 and INN to IN6
    temporal=ADS1x9x_Reg_Read(ADS1293_FLEX_CH3_CN_REG);
    sprintf(uartMessage, "FLEX_CH3_CN : %i\n",temporal); // 
    UART_UartPutString(uartMessage);     
    
    ADS1x9x_Reg_Write(ADS1293_CMDET_EN_REG,0x07);//Enable the common-mode detector on input pins IN1,IN2,IN3
    temporal=ADS1x9x_Reg_Read(ADS1293_CMDET_EN_REG);
    sprintf(uartMessage, "CMDET_EN_REG : %i\n",temporal); // 
    UART_UartPutString(uartMessage); 
    
    ADS1x9x_Reg_Write(ADS1293_RLD_CN_REG,0x04);//Connect the output of the RLD amplifier internally to pin IN4
    temporal=ADS1x9x_Reg_Read(ADS1293_RLD_CN_REG);
    sprintf(uartMessage, "RLD_CN_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_WILSON_EN1_REG,0x01);//Connects the first buffer of the wilson reference to IN1 pin
    temporal=ADS1x9x_Reg_Read(ADS1293_WILSON_EN1_REG);
    sprintf(uartMessage, "WILSON_EN1_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_WILSON_EN2_REG,0x02);//Connects the second buffer of the wilson reference to IN2 pin
    temporal=ADS1x9x_Reg_Read(ADS1293_WILSON_EN2_REG);
    sprintf(uartMessage, "WILSON_EN2_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_WILSON_EN3_REG,0x03);//Connects the third buffer of the wilson reference to IN3 pin
    temporal=ADS1x9x_Reg_Read(ADS1293_WILSON_EN3_REG);
    sprintf(uartMessage, "WILSON_EN3_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_WILSON_CN_REG,0x01);//Connects the output of the wilson reference internally to IN6
    temporal=ADS1x9x_Reg_Read(ADS1293_WILSON_CN_REG);
    sprintf(uartMessage, "WILSON_CN_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_OSC_CN_REG,0x04);//Use external crystal and feed the internal oscillator's output to the digital
    
    temporal=ADS1x9x_Reg_Read(ADS1293_OSC_CN_REG);
    sprintf(uartMessage, "OSC_CN_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
//    ADS1x9x_Reg_Write(ADS1293_R2_RATE_REG,0x02);//Configures the R2 decimation rate as 5 for all channels
    ADS1x9x_Reg_Write(ADS1293_R2_RATE_REG,0x04);//Configures the R2 decimation rate as 6 for all channels    
    temporal=ADS1x9x_Reg_Read(ADS1293_R2_RATE_REG);
    sprintf(uartMessage, "R2_RATE_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
//    ADS1x9x_Reg_Write(ADS1293_R3_RATE1_REG,0x02);//Configures the R3 decimation rate as 6 for channel 1
    ADS1x9x_Reg_Write(ADS1293_R3_RATE1_REG,0x04);//Configures the R3 decimation rate as 8 for channel 1    
    temporal=ADS1x9x_Reg_Read(ADS1293_R3_RATE1_REG);
    sprintf(uartMessage, "R3_RATE1_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
//    ADS1x9x_Reg_Write(ADS1293_R3_RATE2_REG,0x02);//Configures the R3 decimation rate as 6 for channel 2
    ADS1x9x_Reg_Write(ADS1293_R3_RATE2_REG,0x04);//Configures the R3 decimation rate as 8 for channel 2    
    temporal=ADS1x9x_Reg_Read(ADS1293_R3_RATE2_REG);
    sprintf(uartMessage, "R3_RATE2_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
//    ADS1x9x_Reg_Write(ADS1293_R3_RATE3_REG,0x02);//Configures the R3 decimation rate as 6 for channel 3
    ADS1x9x_Reg_Write(ADS1293_R3_RATE3_REG,0x04);//Configures the R3 decimation rate as 8 for channel 3
    temporal=ADS1x9x_Reg_Read(ADS1293_R3_RATE3_REG);
    sprintf(uartMessage, "R3_RATE3_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_DRDYB_SRC_REG,0x08);//Configures the DRDYB source to ECG channel 1 (or fastest channel)
    temporal=ADS1x9x_Reg_Read(ADS1293_DRDYB_SRC_REG);
    sprintf(uartMessage, "DRDYB_SRC_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
//    ADS1x9x_Reg_Write(ADS1293_CH_CNFG_REG,0x70);//Enables ECG channel 1, ECG channel 2, and ECG channel 3 for loop read-back mode
//    ADS1x9x_Reg_Write(ADS1293_CH_CNFG_REG,0x71);//Enables Status, ECG channel 1, ECG channel 2, and ECG channel 3 for loop read-back mode
    ADS1x9x_Reg_Write(ADS1293_CH_CNFG_REG,0x71);//Enables Status data loop read-back mode
    temporal=ADS1x9x_Reg_Read(ADS1293_CH_CNFG_REG);
    sprintf(uartMessage, "CH_CNFG_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);
    
    ADS1x9x_Reg_Write(ADS1293_CONFIG_REG,0x01);//Start data conversion
    temporal=ADS1x9x_Reg_Read(ADS1293_CONFIG_REG);
    sprintf(uartMessage, "CONFIG_REG: %i\n",temporal); // 
    UART_UartPutString(uartMessage);    
}
/*********************************************************************************************************/

/* [] END OF FILE */
