#include "config.h"
void ReadConfig()
{
	STMFLASH_Read(FLASH_ADDR, (uint16_t *)&calibration_set_volt, sizeof(s_calibration_t) / 2);
	STMFLASH_Read(FLASH_ADDR + sizeof(s_calibration_t), (uint16_t *)&calibration_set_current, sizeof(s_calibration_t) / 2);
	STMFLASH_Read(FLASH_ADDR + 2*sizeof(s_calibration_t), (uint16_t *)&calibration_real_volt, sizeof(s_calibration_t) / 2); 
	STMFLASH_Read(FLASH_ADDR + 3 * sizeof(s_calibration_t), (uint16_t *)&calibration_real_current, sizeof(s_calibration_t) / 2);
}
void SaveConfig()
{

	STMFLASH_Write(FLASH_ADDR, (uint16_t *)&calibration_set_volt, sizeof(calibration_set_volt) / 2);
	STMFLASH_Write(FLASH_ADDR + sizeof(calibration_set_current), (uint16_t *)&calibration_set_current, sizeof(calibration_set_current) / 2);
	STMFLASH_Write(FLASH_ADDR + 2 * sizeof(s_calibration_t), (uint16_t *)&calibration_real_volt, sizeof(s_calibration_t) / 2);
	STMFLASH_Write(FLASH_ADDR + 3 * sizeof(s_calibration_t), (uint16_t *)&calibration_real_current, sizeof(s_calibration_t) / 2);
}
