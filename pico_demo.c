#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "ST7735.h"

#include "clockDigital.h"
#include "clockFlip.h"
#include "clockMatrix.h"
#include "clockVFD.h"
#include "clockInk.h"
#include "clockWood.h"

#Raspberry Pi Pico
#https: // savageelectronics.com/spi-display-array-board-clock/
#define ONBOARD_LED 25

int main()
{
    stdio_init_all();

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &SPILCD_program);
    lcdPIOInit(pio, sm, offset, PIN_SDI, PIN_SCK, SERIAL_CLK_DIV);

    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);

    gpio_init(PIN_CS1);
    gpio_init(PIN_CS2);
    gpio_init(PIN_CS3);
    gpio_init(PIN_CS4);
    gpio_init(PIN_CS5);
    gpio_init(PIN_CS6);
    gpio_init(PIN_DC);
    gpio_init(PIN_RST);
    gpio_init(PIN_BLK);

    gpio_set_dir(PIN_CS1, GPIO_OUT);
    gpio_set_dir(PIN_CS2, GPIO_OUT);
    gpio_set_dir(PIN_CS3, GPIO_OUT);
    gpio_set_dir(PIN_CS4, GPIO_OUT);
    gpio_set_dir(PIN_CS5, GPIO_OUT);
    gpio_set_dir(PIN_CS6, GPIO_OUT);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_set_dir(PIN_BLK, GPIO_OUT);

    gpio_put(ONBOARD_LED, 1);
    gpio_put(PIN_CS1, 0);
    gpio_put(PIN_CS2, 0);
    gpio_put(PIN_CS3, 0);
    gpio_put(PIN_CS4, 0);
    gpio_put(PIN_CS5, 0);
    gpio_put(PIN_CS6, 0);
    gpio_put(PIN_RST, 1);
    lcdInit(pio, sm, st7735_initSeq);
    gpio_put(PIN_BLK, 1);

    lcdStartPx(pio, sm);

    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, one_Flip[i]);
    }

    gpio_put(PIN_CS1, 1);
    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, two_Matrix[i]);
    }

    gpio_put(PIN_CS2, 1);
    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, three_Digital[i]);
    }

    gpio_put(PIN_CS3, 1);
    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, four_VFD[i]);
    }

    gpio_put(PIN_CS4, 1);
    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, five_Ink[i]);
    }

    gpio_put(PIN_CS5, 1);
    for (int i = 0; i < 160 * 80 * 2; i++)
    {
        lcdPut(pio, sm, six_Wood[i]);
    }
}