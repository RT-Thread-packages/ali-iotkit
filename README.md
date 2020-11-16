# Ali IoTKit

[中文页](README_ZH.md) | English

> Description:
The Ali IoTKit software package has been updated to c-sdk-v3.0.1-269691d1b45b15fb9045a8eb178efa54b262aca1c-sdk.git. The documentation and tutorials in this package have not been updated in time, we apologize, please move to Ali [Official Wikis](https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide) /Linkkit_User_Manual) and Ali [Official Document](https://help.aliyun.com/product/93051.html?spm=a2c4g.11186623.6.540.393e492bC6TzC4).

## 1. Introduction

**ali-iotkit** is a software package ported by RT-Thread to connect to the Alibaba Cloud IoT platform. The basic SDK is [**iotkit-embedded C-SDK**](https://github.com/aliyun/iotkit-embedded) provided by Ali.

**ali-iotkit** In order to facilitate the cloud on the device, a rich connection protocol is encapsulated, such as MQTT, CoAP, HTTP, TLS, and the hardware platform is abstracted to make it more flexible without being restricted by the specific hardware platform.

Compared with traditional cloud access SDK, **ali-iotkit** has the following advantages:

- Quick access capability
- Embedded device tuning
- Multiple compiler support (Gcc, IAR, MDK)
- Multi-connection protocol support (HTTP, MQTT, CoAP)
- Cross-hardware, cross-OS platform support
- Device firmware OTA upgrade
- TLS/DTLS secure connection
- Highly portable application program
- Highly reusable functional components

### 1.1 Directory structure

| Name | Description |
| ---- | ---- |
| docs | Document directory |
| iotkit-embedded | Ali iotkit original file directory |
| ports | Migration file directory |
| samples | Sample file directory |

### 1.2 Resource occupation

When counting the resource occupancy of the iotkit software package, the MQTT + TLS routines are used, and only the RAM and ROM size occupied by the package itself are counted. The resource size occupied by LibC and external dependent files (such as TLS) is not counted. , And the resource size occupied by the sample routine itself is not counted.

- Test platform: iMXRT1052
- Test IDE: MDK5
- Optimization level: o2

The resource usage is as follows:

```
RO(CODE + RO): 32886 bytes (32.11K)
RW(RW + ZI): 2421 bytes (2.36K)
ROM(CODE + RO + RW): 32962 bytes (32.18K)
Test run mqtt+tls routine dynamic memory usage: 47502 bytes (45.94K)
```


### 1.3 License

The `ali-iotkit` software package extends the Ali `iotkit-embedded` software package license agreement, please refer to the `iotkit-embedded/LICENSE` file.

### 1.4 Dependency

- [RT_Thread 3.0+](https://github.com/RT-Thread/rt-thread/releases/tag/v3.0.4)
- [MbedTLS package](https://github.com/RT-Thread-packages/mbedtls)

## 2. How to use

### 2.1 Enable package

- Use `menuconfig` to enable iotkit package and fill in device information

```c
RT-Thread online packages --->
    IoT-internet of things --->
        IoT Cloud --->
          [*] Ali-iotkit: Ali Cloud SDK for IoT platform --->
                Select Aliyun platform (LinkDevelop Platform) --->
          (a1dSQSGZ77X) Config Product Key
          (RGB-LED-DEV-1) Config Device Name
          (Ghuiyd9nmGowdZzjPqFtxhm3WUHEbIlI) Config Device Secret
          -*- Enable MQTT
          [*] Enable MQTT sample
          [*] Enable MQTT direct connect
          [*] Enable SSL
          [] Enable COAP
          [*] Enable OTA
                      Select OTA channel (Use MQTT OTA channel) --->
                    version (latest) --->
```

- Increase the frame size of `mbedTLS` (At least 8K size is required for OTA)

```c
RT-Thread online packages --->
    security packages --->
      -*- mbedtls:An open source, portable, easy to use, readable and flexible SSL library --->
      (8192) Maxium fragment length in bytes
```

- Use the `pkgs --update` command to download the package

### 2.2 Implementation example

> Use commands to execute preset sample programs in MSH

- MQTT Sample single release subscription

This sample program demonstrates how to use MQTT to publish and subscribe Topic. The MSH commands are as follows:

```c
msh />ali_mqtt_test
ali_mqtt_test|502 :: iotkit-embedded sdk version: V2.10
[inf] iotx_device_info_init(40): device_info created successfully!
[dbg] iotx_device_info_set(50): start to set device info!
[dbg] iotx_device_info_set(64): device_info set successfully!

...

mqtt_client|324 :: out of sample!
```

- MQTT Sample monitors subscription messages

This sample program demonstrates how to use MQTT to publish and subscribe to Topic, and always monitor the news of subscribing to Topic. The MSH command is as follows:

```c
msh />ali_mqtt_test loop
ali_mqtt_test|502 :: iotkit-embedded sdk version: V2.10
[dbg] iotx_device_info_init(32): device_info already created, return!
[dbg] iotx_device_info_set(50): start to set device info!
[dbg] iotx_device_info_set(64): device_info set successfully!

...

[dbg] iotx_mc_cycle(1269): SUBACK
event_handle|111 :: subscribe success, packet-id=0
[dbg] iotx_mc_cycle(1269): SUBACK
event_handle|111 :: subscribe success, packet-id=0
```

- OTA Sample

This sample program demonstrates how to use the Alibaba Cloud OTA service, using the `ali_ota_test` command to start the routine. At this time, the device will first report the current version number to Alibaba Cloud, and then wait for the cloud to issue an OTA upgrade command.

```c
msh />ali_ota_test
ali_ota_main|325 :: iotkit-embedded sdk version: V2.10
[dbg] iotx_device_info_init(32): device_info already created, return!
[dbg] iotx_device_info_set(50): start to set device info!
[dbg] iotx_device_info_set(64): device_info set successfully!

...

mqtt_client|232 :: wait ota upgrade command...
[dbg] iotx_mc_cycle(1260): PUBACK
event_handle|117 :: publish success, packet-id=2
[dbg] iotx_mc_cycle(1269): SUBACK
event_handle|093 :: subscribe success, packet-id=1
mqtt_client|232 :: wait ota upgrade command...
mqtt_client|232 :: wait ota upgrade command...
mqtt_client|232 :: wait ota upgrade command...
```

## 3. Reference

- To get started, please refer to [User Guide](docs/user-guide.md)
- For detailed sample introduction, please refer to [Sample Document](docs/samples.md)
- API introduction, please refer to [API documentation](docs/api.md)
- For more detailed documents, please visit the `/docs` directory to view

## 4. Matters needing attention

- Please configure your device information (PRODUCT_KEY, DEVICE_NAME and DEVICE_SECRET) in `menuconfig` before use
- Encrypted connection must be enabled to enable OTA function (because OTA upgrade must use HTTPS to download firmware)

## 5. Common problems

- MbedTLS returns 0x7200 error
  Usually the MbedTLS frame length is too small, please increase the MbedTLS frame length, refer to Chapter 2.

## 6. Contact & Thanks

- Maintenance: Murphy
- Homepage: https://github.com/RT-Thread-packages/ali-iotkit
