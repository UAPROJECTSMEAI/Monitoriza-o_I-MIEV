/*
 * Copyright (c) 2010-2011 by Kevin Smith <faz@fazjaxton.net>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * as published by the Free Software Foundation.
 */

#ifndef __SPI_H__
#define __SPI_H__

/* Remove this line if building outside the Arduino environment */

#include "bcm2835.h"
#include <stdint.h>

/** Initialize the SPI */
int inic_SPI(void);
/** Close the SPI*/
void close_SPI(int SDI, int SDO, int SCK, int CS);
/** Assert the slave select signal */
/**
 * Initiate an SPI transfer.
 * @param byte - byte to send
 * @return     - the byte received
 */
uint8_t spi_transfer (uint8_t byte);

void spi_send(uint8_t byte);

uint8_t spi_receive(void);


#endif