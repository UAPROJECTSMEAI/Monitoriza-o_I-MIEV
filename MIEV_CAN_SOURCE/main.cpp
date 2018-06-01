
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "bcm2835.h"
#include "main.h"
#include "my_spi.h"
#include "mcp_can.h"
#include "miev_obd.h"
#include <fstream>
using namespace std;

#define CAN0_INT RPI_GPIO_P1_22
MCP_CAN CAN0(BCM2835_SPI_CS0); //set CS pin
MIEV_CAN miev_val;

uint32_t rxId;
uint8_t len = 0;
uint8_t rxBuf[100];
char msgString[128]; // Array to store serial string



int main(void){
    ofstream myfile;
    inic_gpio();
    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    inicia_spi();
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK){
        printf("MCP2515 Initialized Successfully!");
    }
    else{
        printf("Error Initializing MCP2515...");
    }
    CAN0.setMode(MCP_ANY);  
	while(1){
        if(!bcm2835_gpio_lev(CAN0_INT)){                         // If CAN0_INT pin is low, read receive buffer
            CAN0.readMsgBuf(&rxId, &len, rxBuf);        // Read data: len = data length, buf = data byte(s)
            //myfile.open ("CAN_VALUES.txt", std::ios_base::app);
            //sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
            miev_val.receive_values(rxId, len, rxBuf);
            /*
            printf("%s", msgString);
            //myfile << msgString;
            if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
                sprintf(msgString, " REMOTE REQUEST FRAME");
                printf("%s", msgString);
                myfile << msgString;
            }
            else {
                for(byte i = 0; i<len; i++){
                    sprintf(msgString, " 0x%.2X", rxBuf[i]);
                    printf("%s", msgString);
                    myfile << msgString;
                }
            }
            printf("\n");
            myfile << "\n";
            myfile.close();*/
            system("clear");
            printf("       - MIEV-CAN - ATLAS CAR II - \n\n\n");
            printf("Chave do veiculo   : %1d \n", miev_val.key_state);
            printf("Kilometros do carro: %.1f \n", miev_val.odometer);
            printf("Velocidade Atual   :%d \n", miev_val.speed);
            printf("Estado do travao   :%d \n", miev_val.brake_state);
            printf("Posicao Travao     :%3.1f \n", miev_val.brake_pos);
            printf("Posicao Acelerador :%s \n", miev_val.throttle_pos);
            printf("Mudanca            :%c \n", miev_val.gear);
            printf("Posicao Volante    :%3.1f \n", miev_val.steering_wheel);
        }
        
    }
    return 0;
}

void inic_gpio(void){
    int state=bcm2835_init();
	bcm2835_gpio_fsel(INT_PIN, BCM2835_GPIO_FSEL_INPT);
}

void inicia_spi(void){
    bcm2835_gpio_fsel(RPI_GPIO_P1_18, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RPI_GPIO_P1_18, HIGH);

    bcm2835_spi_begin();
    //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
    //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
}