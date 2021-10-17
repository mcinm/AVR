/*
*
*	https://mcinm.pl
*
*/

#include "I2C_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// ****** PODSTAWOWE FUNKCJE ******
void I2C_init()
{
	TWBR = 32;
}

void I2C_start()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while (!(TWCR & (1<<TWSTO)));
}

void I2C_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

uint8_t I2C_read(uint8_t ACK)
{
	TWCR = (1<<TWINT) | (ACK<<TWEA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

// ****** WYSYŁANIE DANYCH ******
	// wysyłanie pojedynczych danych
void I2C_send(uint8_t address, uint8_t data)
{
	I2C_start();
	I2C_write(address);
	I2C_write(data);
	I2C_stop();
}
