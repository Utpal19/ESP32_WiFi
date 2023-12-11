#include <stdio.h>
#include "oledDIsp.h"


void o_disp_test(SSD1306_t* devName)
{
    // SSD1306_t* dev = devName;
    ssd1306_init(devName, 128, 32);
    ssd1306_clear_screen(devName, false);
	ssd1306_contrast(devName, 0xff);
	ssd1306_display_text_x3(devName, 0, "TEST#", 5, false);
}

void display_wifi_app_msg(SSD1306_t* devName, const char* msg, int len)
{
    // ssd1306_init(devName, 128, 32);
    ssd1306_clear_screen(devName, false);
	ssd1306_contrast(devName, 0xff);
	ssd1306_display_text(devName, 0, msg, len, false);
}