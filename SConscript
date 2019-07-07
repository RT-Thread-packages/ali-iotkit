import os
from building import *
import rtconfig

cwd     = GetCurrentDir()

src     = []
CPPPATH = []

src     = Split("""
ports/rtthread/HAL_OS_rtthread.c
ports/rtthread/HAL_TCP_rtthread.c
ports/rtthread/HAL_UDP_rtthread.c
""")

#
# infra
#
src += Glob('iotkit-embedded/src/infra/infra_defs.c')

if GetDepend(['INFRA_AES']):
    src += Glob('iotkit-embedded/src/infra/infra_aes.c')
if GetDepend(['INFRA_CJSON']):
    src += Glob('iotkit-embedded/src/infra/infra_cjson.c')
if GetDepend(['INFRA_COMPAT']):
    src += Glob('iotkit-embedded/src/infra/infra_compat.c')
if GetDepend(['INFRA_HTTPC']):
    src += Glob('iotkit-embedded/src/infra/infra_httpc.c')
if GetDepend(['INFRA_JSON_PARSER']):
    src += Glob('iotkit-embedded/src/infra/infra_json_parser.c')
if GetDepend(['INFRA_LOG']):
    src += Glob('iotkit-embedded/src/infra/infra_log.c')
if GetDepend(['INFRA_MD5']):
    src += Glob('iotkit-embedded/src/infra/infra_md5.c')
if GetDepend(['INFRA_MEM_STATS']):
    src += Glob('iotkit-embedded/src/infra/infra_mem_stats.c')
if GetDepend(['INFRA_NET']):
    src += Glob('iotkit-embedded/src/infra/infra_net.c')
if GetDepend(['INFRA_PREAUTH']):
    src += Glob('iotkit-embedded/src/infra/infra_preauth.c')
if GetDepend(['INFRA_LOG_NETWORK_PAYLOAD']):
    src += Glob('iotkit-embedded/src/infra/infra_prt_nwk_payload.c')
if GetDepend(['INFRA_REPORT']):
    src += Glob('iotkit-embedded/src/infra/infra_report.c')
if GetDepend(['INFRA_SHA1']):
    src += Glob('iotkit-embedded/src/infra/infra_sha1.c')
if GetDepend(['INFRA_SHA256']):
    src += Glob('iotkit-embedded/src/infra/infra_sha256.c')
if GetDepend(['INFRA_STRING']):
    src += Glob('iotkit-embedded/src/infra/infra_string.c')
if GetDepend(['INFRA_TIMER']):
    src += Glob('iotkit-embedded/src/infra/infra_timer.c')

CPPPATH += [cwd + '/iotkit-embedded/src/infra']
#### infra end ####

#
# mqtt
#
if GetDepend(['MQTT_COMM_ENABLED']):
    src += Split("""
    iotkit-embedded/src/mqtt/mqtt_api.c
    iotkit-embedded/src/mqtt/impl/iotx_mqtt_client.c
    iotkit-embedded/src/mqtt/impl/MQTTConnectClient.c
    iotkit-embedded/src/mqtt/impl/MQTTDeserializePublish.c
    iotkit-embedded/src/mqtt/impl/MQTTPacket.c
    iotkit-embedded/src/mqtt/impl/MQTTSerializePublish.c
    iotkit-embedded/src/mqtt/impl/MQTTSubscribeClient.c
    iotkit-embedded/src/mqtt/impl/MQTTUnsubscribeClient.c
    """)
    CPPPATH += [cwd + '/iotkit-embedded/src/mqtt']
    CPPPATH += [cwd + '/iotkit-embedded/src/mqtt/impl']
#### mqtt end ####

#
# coap model
#

#### coap end ####

#
# device model
#
if GetDepend(['DEVICE_MODEL_ENABLED']):
    src += Split("""
    iotkit-embedded/src/dev_model/client/dm_client.c
    iotkit-embedded/src/dev_model/client/dm_client_adapter.c
    iotkit-embedded/src/dev_model/dm_api.c
    iotkit-embedded/src/dev_model/dm_cota.c
    iotkit-embedded/src/dev_model/dm_fota.c
    iotkit-embedded/src/dev_model/dm_ipc.c
    iotkit-embedded/src/dev_model/dm_manager.c
    iotkit-embedded/src/dev_model/dm_message_cache.c
    iotkit-embedded/src/dev_model/dm_message.c
    iotkit-embedded/src/dev_model/dm_opt.c
    iotkit-embedded/src/dev_model/dm_ota.c
    iotkit-embedded/src/dev_model/dm_msg_process.c
    iotkit-embedded/src/dev_model/dm_utils.c
    iotkit-embedded/src/dev_model/dm_log_report.c
    iotkit-embedded/src/dev_model/iotx_cm_mqtt.c
    iotkit-embedded/src/dev_model/impl_linkkit.c
    iotkit-embedded/src/dev_model/iotx_cm.c
    """)
    CPPPATH += [cwd + '/iotkit-embedded/src/dev_model']
    CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/client']
    CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/server']
    CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/client']
#### device model end ####

#
# device sign
#
if GetDepend(['DEV_SIGN']):
    src += Glob('iotkit-embedded/src/dev_sign/dev_sign_mqtt.c')
    CPPPATH += [cwd + '/iotkit-embedded/src/dev_sign']
#### device sign end ####

#
# dynamic register
#
if GetDepend(['DYNAMIC_REGISTER']):
    CPPPATH += [cwd + '/iotkit-embedded/src/dynamic_register']
#### dynamic register end ####

#
# ota
#
if GetDepend(['OTA_ENABLED']):
    src += Split("""
    iotkit-embedded/src/ota/iotx_ota.c
    iotkit-embedded/src/ota/ota_fetch.c
    iotkit-embedded/src/ota/ota_lib.c
    """)
    CPPPATH += [cwd + '/iotkit-embedded/src/ota']
#### ota end ####

#
# wrappers
#
if GetDepend(['SUPPORT_TLS']):
    src += Glob('iotkit-embedded/certs/root_ca.c')
    src += Glob('iotkit-embedded/wrappers/tls/HAL_TLS_mbedtls.c')
if GetDepend(['COAP_DTLS_SUPPORT']):
    src += Glob('iotkit-embedded/certs/root_ca.c')
    src += Glob('iotkit-embedded/wrappers/tls/HAL_DTLS_mbedtls.c')
CPPPATH += [cwd + '/iotkit-embedded/wrappers']
CPPPATH += [cwd + '/iotkit-embedded/wrappers/tls']
#### wrappers end ####

#
# samples
#
if GetDepend(['PKG_USING_ALI_IOTKIT_DEV_MODEL_SAMPLE']):
    src += Split("""
    samples/dev_model/cJSON.c
    samples/dev_model/linkkit_example_solo.c
    """)
    CPPPATH += [cwd + '/iotkit-embedded/samples/dev_model']
#### samples end ####

group = DefineGroup('ali-iotkit', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
