#pragma once

#ifndef _SSD1306_I2C_H__
#define _SSD1306_I2C_H__


#define CONFIG_SCL_GPIO     22    /*!< GPIO number used for I2C master clock */
#define CONFIG_SDA_GPIO     21    /*!< GPIO number used for I2C master data  */
#define CONFIG_RESET_GPIO   15
#define CONFIG_OFFSETX      0

#define I2C_MASTER_FREQ_HZ 400000 /*!< I2C clock of SSD1306 can run at 400 kHz max. */

void i2c_master_init(SSD1306_t * dev, int16_t sda, int16_t scl, int16_t reset);
void i2c_init(SSD1306_t * dev, int width, int height);
void i2c_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
void i2c_contrast(SSD1306_t * dev, int contrast);
void i2c_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll);


#endif
