idf_component_register(SRCS "wifi_simple.c" "ssd1306_i2c.c" "ssd1306.c" "oledDisp.c" "wifi_app.c" "main.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)