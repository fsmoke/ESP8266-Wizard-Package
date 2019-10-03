#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__
#include "c_types.h"

#define MESH_DEMO_PRINT  ets_printf
#define MESH_DEMO_STRLEN ets_strlen
#define MESH_DEMO_MEMCPY ets_memcpy
#define MESH_DEMO_MEMSET ets_memset
#define MESH_DEMO_FREE   os_free

static const uint16_t server_port = 7000;                  /*PORT USED BY USER IOT SERVER FOR MESH SERVICE*/  
static const uint8_t server_ip[4] = {192, 168, 11, 116};   /*USER IOT SERVER IP ADDRESS*/
static const uint32_t UART_BAUT_RATIO = 74880;             /*UART BAUT RATIO*/
static const uint8_t MESH_GROUP_ID[6] = {0x18,0xfe,0x34,0x00,0x00,0x50};  /*MESH_GROUP_ID & MESH_SSID_PREFIX REPRESENTS ONE MESH NETWORK*/
static const uint8_t MESH_ROUTER_BSSID[6] = {0xF0, 0xB4, 0x29, 0x2C, 0x7C, 0x72}; /*MAC OF ROUTER*/

/*
 * please change MESH_ROUTER_SSID and MESH_ROUTER_PASSWD according to your router
 */
#define MESH_ROUTER_SSID     "ESP_IOT"      /*THE ROUTER SSID*/
#define MESH_ROUTER_PASSWD   "123456789"    /*THE ROUTER PASSWORD*/
#define MESH_SSID_PREFIX     "MESH_DEMO"    /*SET THE DEFAULT MESH SSID PREFIX;THE FINAL SSID OF SOFTAP WOULD BE "MESH_SSID_PREFIX_X_YYYYYY"*/
#define MESH_AUTH            AUTH_WPA2_PSK  /*AUTH_MODE OF SOFTAP FOR EACH MESH NODE*/
#define MESH_PASSWD          "123123123"    /*SET PASSWORD OF SOFTAP FOR EACH MESH NODE*/
#define MESH_MAX_HOP         (4)            /*MAX_HOPS OF MESH NETWORK*/

#endif

