/*
*
*	https://mcinm.pl
*
*/
#include <stdint.h>

void I2C_init();
void I2C_start();
void I2C_stop();
void I2C_write(uint8_t data);
uint8_t I2C_read(uint8_t ACK);

void I2C_send(uint8_t address, uint8_t data);

