/*
 * Copyright (c) 2006-2018 RT-Thread Development Team. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <rtthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <sys/time.h>

#include "infra_config.h"
#include "infra_compat.h"
#include "infra_defs.h"
#include "wrappers_defs.h"

#define ALI_IOTKIT_HAL_OS_DEBUG

#ifdef ALI_IOTKIT_HAL_OS_DEBUG
#define DBG_TAG                        "ali.os"
#define DBG_LVL                        DBG_INFO
#include <rtdbg.h>
#else
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#define LOG_E(...)
#endif

#ifdef DYNAMIC_REGISTER
    char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1ZETBPbycq";
    char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "L68wCVXYUaNg1Ey9";
    char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
    char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "";
#else
    #ifdef DEVICE_MODEL_ENABLED
        char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1RIsMLz2BJ";
        char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "fSAF0hle6xL0oRWd";
        char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
        char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "RDXf67itLqZCwdMCRrw0N5FHbv5D7jrE";
    #else
        char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1MZxOdcBnO";
        char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "h4I4dneEFp7EImTv";
        char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "test_01";
        char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "t9GmMf2jb3LgWfXBaZD2r3aJrfVWBv56";
    #endif
#endif

#undef  perror
#define perror rt_kprintf

#define HAL_OS_LOG_MAXLEN 512

static char log_buf[HAL_OS_LOG_MAXLEN];

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

void *HAL_MutexCreate(void)
{
    rt_mutex_t mutex = rt_mutex_create("ali_ld_mutex", RT_IPC_FLAG_FIFO);
    return mutex;
}

void HAL_MutexDestroy(void *mutex)
{
    int err_num;

    if (0 != (err_num = rt_mutex_delete((rt_mutex_t)mutex)))
    {
        LOG_E("destroy mutex failed, err num: %d", err_num);
    }
}

void HAL_MutexLock(void *mutex)
{
    int err_num;

    if (0 != (err_num = rt_mutex_take((rt_mutex_t)mutex, RT_WAITING_FOREVER)))
    {
        LOG_E("lock mutex failed, err num: %d", err_num);
    }
}

void HAL_MutexUnlock(void *mutex)
{
    int err_num;

    if (0 != (err_num = rt_mutex_release((rt_mutex_t)mutex)))
    {
        LOG_E("unlock mutex failed, err num: %d", err_num);
    }
}

/**
 * @brief   create a semaphore
 *
 * @return semaphore handle.
 * @see None.
 * @note The recommended value of maximum count of the semaphore is 255.
 */
void *HAL_SemaphoreCreate(void)
{
    char name[10] = {0};
    static uint8_t sem_num = 0;
    snprintf(name, sizeof(name), "sem%02d", ((++sem_num)%100));
    rt_sem_t sem = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO);
    if (!sem)
    {
        LOG_E("Semaphore create failed!");
    }
	return (void*)sem;
}

/**
 * @brief   destory a semaphore
 *
 * @param[in] sem @n the specified sem.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SemaphoreDestroy(void *sem)
{
    rt_err_t err = RT_EOK;
    rt_object_t obj = sem;

    if (!obj)
    {
        LOG_E("In param (sem) is NULL!");
        return;
    }

    if (obj->type == RT_Object_Class_Semaphore)
    {
        err = rt_sem_delete((rt_sem_t)obj);
        if (err != RT_EOK)
        {
            LOG_E("sem delete failed! errno:%d", err);
        }
    }
    else
    {
        LOG_E("Error sem handler!");
    }
	return;
}


/**
 * @brief   signal thread wait on a semaphore
 *
 * @param[in] sem @n the specified semaphore.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SemaphorePost(void *sem)
{
    rt_err_t err = RT_EOK;
    rt_object_t obj = sem;

    if (!obj)
    {
        LOG_E("In param (sem) is NULL!");
        return;
    }

    if (obj->type == RT_Object_Class_Semaphore)
    {
        err = rt_sem_release((rt_sem_t)obj);
        if (err != RT_EOK)
        {
            LOG_E("sem release failed! errno:%d", err);
        }
    }
    else
    {
        LOG_E("Error sem handler!");
    }
	return;
}

/**
 * @brief   wait on a semaphore
 *
 * @param[in] sem @n the specified semaphore.
 * @param[in] timeout_ms @n timeout interval in millisecond.
     If timeout_ms is PLATFORM_WAIT_INFINITE, the function will return only when the semaphore is signaled.
 * @return
   @verbatim
   =  0: The state of the specified object is signaled.
   =  -1: The time-out interval elapsed, and the object's state is nonsignaled.
   @endverbatim
 * @see None.
 * @note None.
 */
int HAL_SemaphoreWait(void *sem, uint32_t timeout_ms)
{
    rt_err_t err = RT_EOK;
    rt_object_t obj = sem;

    if (!obj)
    {
        LOG_E("In param (sem) is NULL!");
        return -1;
    }

    if (obj->type == RT_Object_Class_Semaphore)
    {
        err = rt_sem_take((rt_sem_t)obj, timeout_ms);
        if (err != RT_EOK)
        {
            LOG_E("sem take failed! errno:%d", err);
        }
    }
    else
    {
        LOG_E("Error sem handler!");
    }
	return (err == RT_EOK ? 0 : -1);
}

void *HAL_Malloc(uint32_t size)
{
    return rt_malloc(size);
}

void HAL_Free(void *ptr)
{
    rt_free(ptr);
}

uint64_t HAL_UptimeMs(void)
{
#if (RT_TICK_PER_SECOND == 1000)
    return (uint64_t)rt_tick_get();
#else

    uint64_t tick;
    tick = rt_tick_get();

    tick = tick * 1000;

    return (tick + RT_TICK_PER_SECOND - 1)/RT_TICK_PER_SECOND;
#endif
}

void HAL_SleepMs(uint32_t ms)
{
    rt_thread_mdelay(ms);
}

void HAL_Srandom(uint32_t seed)
{
    srand(seed);
}

uint32_t HAL_Random(uint32_t region)
{
    return (region > 0) ? (rand() % region) : 0;
}

int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int     rc;

    va_start(args, fmt);
    rc = rt_vsnprintf(str, len, fmt, args);
    va_end(args);

    return rc;
}

int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap)
{
    return rt_vsnprintf(str, len, format, ap);
}

void HAL_Printf(const char *fmt, ...)
{
    va_list args;
    
    va_start(args, fmt);
    rt_vsnprintf(log_buf, HAL_OS_LOG_MAXLEN, fmt, args);
    va_end(args);
    rt_kprintf("%s", log_buf);
}

extern void rt_hw_cpu_reset();

#ifndef rt_hw_cpu_reset
void rt_hw_cpu_reset()
{
}
#endif
void HAL_Reboot(void)
{
    rt_hw_cpu_reset();
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

void HAL_Firmware_Persistence_Start(void)
{
    LOG_I("OTA start... [Not implemented]");
    return;
}

int HAL_Firmware_Persistence_Write(char *buffer, uint32_t length)
{
    LOG_I("OTA write... [Not implemented]");
    return 0;
}

int HAL_Firmware_Persistence_Stop(void)
{
    /* check file md5, and burning it to flash ... finally reboot system */

    LOG_I("OTA finish... [Not implemented]");
    return 0;
}
