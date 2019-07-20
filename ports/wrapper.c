#include <rtthread.h>
#include <string.h>

#include "wrappers_defs.h"

#define DBG_TAG                        "ali.tcp"
#define DBG_LVL                        DBG_INFO
#include <rtdbg.h>

char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1ZETBPbycq";
char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "L68wCVXYUaNg1Ey9";
char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "";

int HAL_GetFirmwareVersion(char *version)
{
    RT_ASSERT(version);

    char *ver = "app-1.0.0-20180101.1000";
    int len = strlen(ver);
    memset(version, 0x0, IOTX_FIRMWARE_VER_LEN);
    strncpy(version, ver, IOTX_FIRMWARE_VER_LEN);
    version[len] = '\0';
    return strlen(version);
}

int HAL_SetProductKey(char* product_key)
{
    int len = strlen(product_key);

    if (len > IOTX_PRODUCT_KEY_LEN)
        return -1;
    memset(_product_key, 0x0, IOTX_PRODUCT_KEY_LEN + 1);
    strncpy(_product_key, product_key, len);

    return len;
}

int HAL_SetDeviceName(char* device_name)
{
    int len = strlen(device_name);

    if (len > IOTX_DEVICE_NAME_LEN)
        return -1;
    memset(_device_name, 0x0, IOTX_DEVICE_NAME_LEN + 1);
    strncpy(_device_name, device_name, len);

    return len;
}

int HAL_SetDeviceSecret(char* device_secret)
{
    int len = strlen(device_secret);

    if (len > IOTX_DEVICE_SECRET_LEN)
        return -1;
    memset(_device_secret, 0x0, IOTX_DEVICE_SECRET_LEN + 1);
    strncpy(_device_secret, device_secret, len);

    return len;
}

int HAL_SetProductSecret(char* product_secret)
{
    int len = strlen(product_secret);

    if (len > IOTX_PRODUCT_SECRET_LEN)
        return -1;
    memset(_product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN + 1);
    strncpy(_product_secret, product_secret, len);

    return len;
}

int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1])
{   
    memset(product_key, 0x0, IOTX_PRODUCT_KEY_LEN + 1);
    strncpy(product_key, _product_key, IOTX_PRODUCT_KEY_LEN);

    return strlen(product_key);
}

int HAL_GetProductSecret(char product_secret[IOTX_PRODUCT_SECRET_LEN + 1])
{
    memset(product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN + 1);
    strncpy(product_secret, _product_secret, IOTX_PRODUCT_SECRET_LEN);

    return strlen(product_secret);
}

int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1])
{
    memset(device_name, 0x0, IOTX_DEVICE_NAME_LEN + 1);
    strncpy(device_name, _device_name, IOTX_DEVICE_NAME_LEN);

    return strlen(device_name);
}

int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN + 1])
{
    memset(device_secret, 0x0, IOTX_DEVICE_SECRET_LEN + 1);
    strncpy(device_secret, _device_secret, IOTX_DEVICE_SECRET_LEN);

    return strlen(device_secret);
}

RT_WEAK void HAL_Firmware_Persistence_Start(void)
{
    LOG_I("OTA start... [Not implemented]");
    return;
}

RT_WEAK int HAL_Firmware_Persistence_Write(char *buffer, uint32_t length)
{
    LOG_I("OTA write... [Not implemented]");
    return 0;
}

RT_WEAK int HAL_Firmware_Persistence_Stop(void)
{
    /* check file md5, and burning it to flash ... finally reboot system */

    LOG_I("OTA finish... [Not implemented]");
    return 0;
}