import os
from building import *
import rtconfig

cwd     = GetCurrentDir()

src  = []
CPPPATH = []

src     = Split("""
iotkit-embedded/src/infra/infra_log.c
iotkit-embedded/src/infra/infra_compat.c
iotkit-embedded/src/infra/infra_defs.c
iotkit-embedded/src/infra/infra_report.c
iotkit-embedded/src/infra/infra_string.c
iotkit-embedded/src/infra/infra_cjson.c
iotkit-embedded/src/infra/infra_timer.c
iotkit-embedded/src/infra/infra_md5.c
iotkit-embedded/src/infra/infra_sha256.c
iotkit-embedded/src/infra/infra_prt_nwk_payload.c
iotkit-embedded/src/infra/infra_net.c
iotkit-embedded/src/infra/infra_httpc.c
iotkit-embedded/src/infra/infra_json_parser.c
iotkit-embedded/src/mqtt/mqtt_api.c
iotkit-embedded/src/mqtt/impl/iotx_mqtt_client.c
iotkit-embedded/src/mqtt/impl/MQTTConnectClient.c
iotkit-embedded/src/mqtt/impl/MQTTDeserializePublish.c
iotkit-embedded/src/mqtt/impl/MQTTPacket.c
iotkit-embedded/src/mqtt/impl/MQTTSerializePublish.c
iotkit-embedded/src/mqtt/impl/MQTTSubscribeClient.c
iotkit-embedded/src/mqtt/impl/MQTTUnsubscribeClient.c
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
iotkit-embedded/src/dev_model/client/dm_client.c
iotkit-embedded/src/dev_model/impl_linkkit.c
iotkit-embedded/src/dev_model/iotx_cm.c
iotkit-embedded/src/dev_sign/dev_sign_mqtt.c
iotkit-embedded/src/ota/iotx_ota.c
iotkit-embedded/src/ota/ota_fetch.c
iotkit-embedded/src/ota/ota_lib.c
iotkit-embedded/certs/root_ca.c
ports/rtthread/HAL_OS_rtthread.c
ports/rtthread/HAL_TCP_rtthread.c
ports/rtthread/HAL_UDP_rtthread.c
iotkit-embedded/samples/dev_model/cJSON.c
iotkit-embedded/samples/dev_model/linkkit_example_solo.c
""")

if GetDepend(['FEATURE_SUPPORT_TLS']):
    src += Glob('iotkit-embedded/wrappers/tls/HAL_TLS_mbedtls.c')

CPPPATH += [cwd + '/iotkit-embedded/src/dev_model']
CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/client']
CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/server']
CPPPATH += [cwd + '/iotkit-embedded/src/dev_model/client']
CPPPATH += [cwd + '/iotkit-embedded/wrappers']
CPPPATH += [cwd + '/iotkit-embedded/wrappers/tls']
CPPPATH += [cwd + '/iotkit-embedded/src/infra']
CPPPATH += [cwd + '/iotkit-embedded/src/dev_sign']
CPPPATH += [cwd + '/iotkit-embedded/src/mqtt']
CPPPATH += [cwd + '/iotkit-embedded/src/ota']
CPPPATH += [cwd + '/iotkit-embedded/src/dynamic_register']
CPPPATH += [cwd + '/iotkit-embedded/src/mqtt/impl']

CPPPATH += [cwd + '/ports/config']
CPPPATH += [cwd + '/iotkit-embedded/samples/dev_model']

group = DefineGroup('ali-iotkit', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
