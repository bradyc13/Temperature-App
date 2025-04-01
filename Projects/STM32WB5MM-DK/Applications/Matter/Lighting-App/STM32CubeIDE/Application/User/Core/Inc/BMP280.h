/*
 * BMP280.h
 *
 *  Created on: Feb 14, 2025
 *      Author: brady
 */
#include <stdint.h>
#ifndef INC_BMP280_H_
#define INC_BMP280_H_
#define Device_Address 0b1110110
#define Control_Config_Number 0xF4
#define Configuration_Register_Number 0xF5
#define Temperature_Register_Number 0xFA
#define resetRegister 0xE0
#define  DEVICE_ADDRESS_L (0x76 << 1)
#define  DEVICE_ADDRESS_H (0x76 << 1)

#define temp_xlsb 0xFC
#define temp_lsb 0xFB
#define temp_msb 0xFA

#define press_xslb 0xF9
#define press_lsb 0xF8
#define press_msb 0xF7

#define config 0xF5
#define ctrl_meas 0xF4

#define status 0xF3
#define reset 0xE0

#include "stm32wbxx_hal.h"
#define id 0xD0

//Calibration data registers (read only) which store the factory calibration data for calculating the final value of pressure and temperature.
#define cal25 0xA1
#define cal24 0xA0
#define cal23 0x9F
#define cal22 0x9E
#define cal21 0x9D
#define cal20 0x9C
#define cal19 0x9B
#define cal18 0x9A
#define cal17 0x99
#define cal16 0x98
#define cal15 0x97
#define cal14 0x96
#define cal13 0x95
#define cal12 0x94
#define cal11 0x93
#define cal10 0x92
#define cal09 0x91
#define cal08 0x90
#define cal07 0x8F
#define cal06 0x8E
#define cal05 0x8D
#define cal04 0x8C
#define cal03 0x8B
#define cal02 0x8A
#define cal01 0x89
#define cal00 0x88


// Oversampling off for pressure and temperature, normal mode for power
#define Config_Power_Mode_1 0b00000011
extern long int dig_T1;
extern long int dig_T2;
extern long int dig_T3;
extern long int t_fine;
typedef struct {
    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4, dig_H5;
    int8_t dig_H6;
} BMP280_CalibData;
extern BMP280_CalibData calib_data;
extern int32_t t_fine;
extern unsigned char temp_reg;
extern unsigned char press_reg;
long int BME_280_Compensation(long int adc_T,long int dig_T1, long int dig_T2, long int dig_T3);
float compensate_temperature(int32_t adc_T);
float compensate_pressure(int32_t adc_P);
float compensate_humidity(int32_t adc_H);
double compensate_pressure_v2(int32_t adc_P);
int32_t read_ADC_T();
int32_t read_ADC_P();
void read_calibration_data();
extern I2C_HandleTypeDef hi2c1;
extern int32_t t_fine;
#endif /* INC_BMP280_H_ */



