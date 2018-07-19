#ifndef MAIN_H
#define MAIN_H

//#include <climits>

#define CS_PIN RPI_GPIO_P1_24
#define SDO_SPI RPI_GPIO_P1_19
#define SDI_SPI RPI_GPIO_P1_21
#define SCK_SPI RPI_GPIO_P1_23
#define INT_PIN RPI_GPIO_P1_22


typedef uint8_t byte;

void inic_gpio(void);
void inicia_spi(void);
//void config_timer(void);

#endif // MAIN_H
