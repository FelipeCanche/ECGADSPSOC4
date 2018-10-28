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
#ifndef ADS1293_H_
#define ADS1293_H_

#include "project.h"
#include "stdlib.h" 
#include "stdio.h" 
/************************************************************
////////////// ADS1293 REGISTER SET ADDRESSES////////////////
************************************************************/

#define ADS1293_CONFIG_REG                 (0x00)  /* Main Configuration */

#define ADS1293_FLEX_CH1_CN_REG            (0x01)  /* Flex Routing Swich Control for Channel 1 */
#define ADS1293_FLEX_CH2_CN_REG            (0x02)  /* Flex Routing Swich Control for Channel 2 */
#define ADS1293_FLEX_CH3_CN_REG            (0x03)  /* Flex Routing Swich Control for Channel 3 */
#define ADS1293_FLEX_PACE_CN_REG           (0x04)  /* Flex Routing Swich Control for Pace Channel */
#define ADS1293_FLEX_VBAT_CN_REG           (0x05)  /* Flex Routing Swich Control for Battery Monitoriing */

#define ADS1293_LOD_CN_REG                 (0x06)  /* Lead Off Detect Control */
#define ADS1293_LOD_EN_REG                 (0x07)  /* Lead Off Detect Enable */
#define ADS1293_LOD_CURRENT_REG            (0x08)  /* Lead Off Detect Current */
#define ADS1293_LOD_AC_CN_REG              (0x09)  /* AC Lead Off Detect Current */

#define ADS1293_CMDET_EN_REG               (0x0A)  /* Common Mode Detect Enable */
#define ADS1293_CMDET_CN_REG               (0x0B)  /* Commond Mode Detect Control */
#define ADS1293_RLD_CN_REG                 (0x0C)  /* Right Leg Drive Control */

#define ADS1293_WILSON_EN1_REG             (0x0D)  /* Wilson Reference Input one Selection */
#define ADS1293_WILSON_EN2_REG             (0x0E)  /* Wilson Reference Input two Selection */
#define ADS1293_WILSON_EN3_REG             (0x0F)  /* Wilson Reference Input three Selection */
#define ADS1293_WILSON_CN_REG              (0x10)  /* Wilson Reference Input Control */

#define ADS1293_REF_CN_REG                 (0x11)  /* Internal Reference Voltage Control */

#define ADS1293_OSC_CN_REG                 (0x12)  /* Clock Source and Output Clock Control */

#define ADS1293_AFE_RES_REG                (0x13)  /* Analog Front-End Frequency and Resolution */
#define ADS1293_AFE_SHDN_CN_REG            (0x14)  /* Analog Front-End Shutdown Control */
#define ADS1293_AFE_FAULT_CN_REG           (0x15)  /* Analog Front-End Fault Detection Control */
#define ADS1293_AFE_DITHER_EN_REG          (0x16)  /* Enable Dithering in Signma-Delta */
#define ADS1293_AFE_PACE_CN_REG            (0x17)  /* Analog Pace Channel Output Routing Control */

#define ADS1293_ERROR_LOD_REG              (0x18)  /* Lead Off Detect Error Status */
#define ADS1293_ERROR_STATUS_REG           (0x19)  /* Other Error Status */
#define ADS1293_ERROR_RANGE1_REG           (0x1A)  /* Channel 1 Amplifier Out of Range Status */
#define ADS1293_ERROR_RANGE2_REG           (0x1B)  /* Channel 1 Amplifier Out of Range Status */
#define ADS1293_ERROR_RANGE3_REG           (0x1C)  /* Channel 1 Amplifier Out of Range Status */
#define ADS1293_ERROR_SYNC_REG             (0x1D)  /* Synchronization Error */

#define ADS1293_R2_RATE_REG                (0x21)  /* R2 Decimation Rate */
#define ADS1293_R3_RATE1_REG               (0x22)  /* R3 Decimation Rate for Channel 1 */
#define ADS1293_R3_RATE2_REG               (0x23)  /* R3 Decimation Rate for Channel 2 */
#define ADS1293_R3_RATE3_REG               (0x24)  /* R3 Decimation Rate for Channel 3 */
#define ADS1293_P_DRATE_REG                (0x25)  /* 2x Pace Data Rate */
#define ADS1293_DIS_EFILTER_REG            (0x26)  /* ECG Filter Disable */
#define ADS1293_DRDYB_SRC_REG              (0x27)  /* Data Ready Pin Source */
#define ADS1293_SYNCOUTB_SRC_REG           (0x28)  /* Sync Out Pin Source */
#define ADS1293_MASK_DRDYB_REG             (0x29)  /* Optional Mask Control for DRDYB Output */
#define ADS1293_MASK_ERR_REG               (0x2A)  /* Mask Error on ALARMB Pin */

#define ADS1293_ALARM_FILTER_REG           (0x2E)  /* Digital Filter for Analog Alarm Signals */
#define ADS1293_CH_CNFG_REG                (0x2F)  /* Configure Channel for Loop Read Back Mode */

#define ADS1293_DATA_STATUS_REG            (0x30)  /* ECG and Pace Data Ready Status */
#define ADS1293_DATA_CH1_PACE_H_REG        (0x31)  /* Channel1 Pace Data High [15:8] */
#define ADS1293_DATA_CH1_PACE_L_REG        (0x32)  /* Channel1 Pace Data Low [7:0] */

#define ADS1293_DATA_CH2_PACE_H_REG        (0x33)  /* Channel2 Pace Data High [15:8] */
#define ADS1293_DATA_CH2_PACE_L_REG        (0x34)  /* Channel2 Pace Data Low [7:0] */

#define ADS1293_DATA_CH3_PACE_H_REG        (0x35)  /* Channel3 Pace Data High [15:8] */
#define ADS1293_DATA_CH3_PACE_L_REG        (0x36)  /* Channel3 Pace Data Low [7:0] */

#define ADS1293_DATA_CH1_ECG_H_REG         (0x37)  /* Channel1 ECG Data High [23:16] */
#define ADS1293_DATA_CH1_ECG_M_REG         (0x38)  /* Channel1 ECG Data Medium [15:8] */
#define ADS1293_DATA_CH1_ECG_L_REG         (0x39)  /* Channel1 ECG Data Low [7:0] */

#define ADS1293_DATA_CH2_ECG_H_REG         (0x3A)  /* Channel2 ECG Data High [23:16] */
#define ADS1293_DATA_CH2_ECG_M_REG         (0x3B)  /* Channel2 ECG Data Medium [15:8] */
#define ADS1293_DATA_CH2_ECG_L_REG         (0x3C)  /* Channel2 ECG Data Low [7:0] */

#define ADS1293_DATA_CH3_ECG_H_REG         (0x3D)  /* Channel3 ECG Data High [23:16] */
#define ADS1293_DATA_CH3_ECG_M_REG         (0x3E)  /* Channel3 ECG Data Medium [15:8] */
#define ADS1293_DATA_CH3_ECG_L_REG         (0x3F)  /* Channel3 ECG Data Low [7:0] */

#define ADS1293_REVID_REG                  (0x40)  /* Revision ID */
#define ADS1293_DATA_LOOP_REG              (0x50)  /* Loop Read Back Address */

// Useful definitions
#define ADS1293_READ_BIT                   (0x80)
#define ADS1293_WRITE_BIT                  (0x7F)
    
#define ID_ADS1293                         (0x01)      //
//#define DEV_ADS1292R    0x73      // 0b01110011 
/***************************************************************/
    
/***************************************************************/ 
/////////////////////////VARIABLES//////////////////////////////    
uint32 channelData[8];
unsigned char SPI_Rx_Buffer[12];
unsigned char SPI_Tx_buf[12];

/***************************************************************/
/************************************************************/
/////////////////////////// FUNCTIONS/////////////////////////
void ADS1x9x_Reset(void);
void Set_ADS1x9x_Chip_Enable (void);
void Clear_ADS1x9x_Chip_Enable (void);
unsigned char ADS1x9x_Reg_Read(unsigned char Reg_address);
void ADS1x9x_Auto_Inc_Reg_Read (unsigned char Reg_address, uint8_t *buffer, uint8_t count);
void ADS1x9x_Stream_Reg_Read (uint8_t *buffer, uint8_t count);
void ADS1x9x_Reg_Write (unsigned char WRITE_ADDRESS, unsigned char DATA);
void ADS1x9x_Auto_Inc_Reg_Write (unsigned char WRITE_ADDRESS, uint8_t *buffer, unsigned char count);
void Init_ADS1x9x (void);
uint8 Firstsamples(void);
/************************************************************/    
#endif    
/* [] END OF FILE */
