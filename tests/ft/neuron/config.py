BASE_URL = "http://127.0.0.1:7000"
default_jwt = "Bearer eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJuZXVyb24iLCJib2R5RW5jb2RlIjowLCJleHAiOjE3MTc4MzUyNjIsImlhdCI6MTY4NjI5OTI2MiwiaXNzIjoibmV1cm9uIn0.tJ8Z12S5lzzyqvJedFr11w0FmQ8l9inFHuzcuA_3uKoNBJSZlQAkcWyDAO2XELyuZFtHPrk8pJFgEqTzwphtBAybVXbeHBRWED5XuHvYqznzwk1J2UCOuw_ehmHnLszZHRAcMoeLWIRIx0KM7BXvZAyFA2J1axJntxfRrurNMn6MbfnGGtza6hJfuQ6pG-h4cHhrBOogf8nw3f8RLfd16vbWobhEp8KBUrwsfn2Iv4hMXvZMekv_PXboLO74f7oMkEL6pdM9g6G6rDBTjTU8FssfeyJcAP7Xb9mS2G7GNW5B8twtPVLtpOQH9VNbLa4OQxdMb0WN86i9vSDiCOoN6A"

NEU_NODE_DRIVER = 1
NEU_NODE_APP = 2

NEU_CTL_START = 0
NEU_CTL_STOP = 1

NEU_NODE_STATE_INIT = 1
NEU_NODE_STATE_READY = 2
NEU_NODE_STATE_RUNNING = 3
NEU_NODE_STATE_STOPPED = 4

NEU_NODE_LINK_STATE_DISCONNECTED = 0
NEU_NODE_LINK_STATE_CONNECTED = 1

NEU_TAG_ATTRIBUTE_READ = 1
NEU_TAG_ATTRIBUTE_WRITE = 2
NEU_TAG_ATTRIBUTE_SUBSCRIBE = 4
NEU_TAG_ATTRIBUTE_STATIC = 8
NEU_TAG_ATTRIBUTE_RW = NEU_TAG_ATTRIBUTE_READ | NEU_TAG_ATTRIBUTE_WRITE
NEU_TAG_ATTRIBUTE_RW_STATIC = NEU_TAG_ATTRIBUTE_RW | NEU_TAG_ATTRIBUTE_STATIC
NEU_TAG_ATTRIBUTE_RW_SUBSCRIBE = NEU_TAG_ATTRIBUTE_RW | NEU_TAG_ATTRIBUTE_SUBSCRIBE
NEU_TAG_ATTRIBUTE_READ_SUBSCRIBE = NEU_TAG_ATTRIBUTE_READ | NEU_TAG_ATTRIBUTE_SUBSCRIBE

NEU_TYPE_INT8 = 1
NEU_TYPE_UINT8 = 2
NEU_TYPE_INT16 = 3
NEU_TYPE_UINT16 = 4
NEU_TYPE_INT32 = 5
NEU_TYPE_UINT32 = 6
NEU_TYPE_INT64 = 7
NEU_TYPE_UINT64 = 8
NEU_TYPE_FLOAT = 9
NEU_TYPE_DOUBLE = 10
NEU_TYPE_BIT = 11
NEU_TYPE_BOOL = 12
NEU_TYPE_STRING = 13
NEU_TYPE_BYTES = 14
NEU_TYPE_ERROR = 15
NEU_TYPE_WORD = 16
NEU_TYPE_DWORD = 17
NEU_TYPE_LWORD = 18

NEU_BAUD_115200 = 0
NEU_BAUD_57600 = 1
NEU_BAUD_38400 = 2
NEU_BAUD_19200 = 3
NEU_BAUD_9600 = 4
NEU_BAUD_4800 = 5
NEU_BAUD_2400 = 6
NEU_BAUD_1800 = 7
NEU_BAUD_1200 = 8
NEU_BAUD_600 = 9

NEU_PARITY_NONE = 0
NEU_PARITY_ODD = 1
NEU_PARITY_EVEN = 2
NEU_PARITY_MARK = 3
NEU_PARITY_SPACE = 4

NEU_STOP_1 = 0
NEU_STOP_2 = 1

NEU_DATA_5 = 0
NEU_DATA_6 = 1
NEU_DATA_7 = 2
NEU_DATA_8 = 3

PLUGIN_MODBUS_TCP = "Modbus TCP"
PLUGIN_MODBUS_RTU = "Modbus RTU"
PLUGIN_MQTT = "MQTT"