/*
 * Copyright (c) 2010-2011 by Kevin Smith <faz@fazjaxton.net>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * as published by the Free Software Foundation.
 */

#include "my_spi.h"
#include "bcm2835.h"
#include "main.h"
/* Don't build this file if for the Arduino */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <sstream>

uint8_t spi_transfer(uint8_t byte){
    return bcm2835_spi_transfer(byte);
}

int inic_SPI(void){
    int aux=0;
    int val=bcm2835_spi_begin();
    if(val==1){
        aux=1;
    }
    else{
        printf("\nNao inicio\n SPI");
    }

    // Clear TX and RX fifos

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default

    return aux;
}

void close_SPI(){
    // Set all the SPI0 pins back to input

    bcm2835_gpio_fsel(CS_PIN, BCM2835_GPIO_FSEL_INPT); // CE0
    bcm2835_gpio_fsel(SCK_SPI, BCM2835_GPIO_FSEL_INPT); // MISO
    bcm2835_gpio_fsel(SDO_SPI, BCM2835_GPIO_FSEL_INPT); // MOSI
    bcm2835_gpio_fsel(SDI_SPI, BCM2835_GPIO_FSEL_INPT); // CLK
}
/** Convenience function for sending a byte and ignoring the receive value */
void spi_send(uint8_t byte)
{
    bcm2835_spi_transfer(byte);
}
/** Convenience function for receiving a byte and ignoring the send value */
uint8_t spi_receive(void)
{
    return bcm2835_spi_transfer(0x00);
}