#include <signal.h>
#include <sys/time.h>
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
static MCP_CAN CAN0(BCM2835_SPI_CS0); //set CS pin
static MIEV_CAN miev_val;

uint32_t rxId;
uint8_t len = 0;
uint8_t rxBuf[100];
char msgString[500]; // Array to store serial string
ofstream myfile;
//struct sigaction sa;
//struct itimerval timer;

//void timer_handler (int signum){

//}

int main(void){
    
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
    //config_timer();  
	while(1){
        while(!bcm2835_gpio_lev(CAN0_INT)){                // If CAN0_INT pin is low, read receive buffer
            CAN0.readMsgBuf(&rxId, &len, rxBuf);        // Read data: len = data length, buf = data byte(s)
            if(rxId==0x412 || rxId==0x231 || rxId==0x208 || rxId==0x210 || rxId==0x236 || rxId==0x412 || rxId==0x285 || rxId==0x298 || rxId==0x346 || rxId==0x373)
                miev_val.receive_values(rxId, len, rxBuf);
                myfile.open ("CAN_VALUES.txt", std::ios_base::app);
                sprintf(msgString, "%3.1f,%1d,%2.1f,%2.1f,%3.0f,%3.0f,%5d,%d,%5d,%3d,%3.1f,%3.1f,%2.1f",miev_val.speed, miev_val.brake_state, miev_val.brake_pos, miev_val.throttle_pos, miev_val.steering_wheel, miev_val.steering_moment, miev_val.odometer, miev_val.gear, miev_val.rpm_motor, miev_val.autonomy_km, miev_val.volt_battery, miev_val.amp_battery, miev_val.perc_battery);
                myfile << msgString;
                myfile << "\n";
                myfile.close();
                printf("%s",msgString);
                printf("\n",msgString);
            }
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
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
}

/*
void config_timer(void){
    // Install timer_handler as the signal handler for SIGVTALRM. 
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &timer_handler;
    sigaction (SIGVTALRM, &sa, NULL);

    // Configure the timer to expire after 500 msec... 
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 200000;
    // ... and every 500 msec after that. 
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 200000;
    // Start a virtual timer. It counts down whenever this process isexecuting. 
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
}
*/

