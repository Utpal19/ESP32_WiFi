#pragma once
#ifndef _WIFI_SIMPLE_H__
#define _WIFI_SIMPLE_H__


#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "stdint.h"

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data);
void wifi_connection();



#endif