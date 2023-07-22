
/* REG_ADDR*/
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_0 = 0x40;
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_1 = 0x50;
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_2 = 0x60;
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_3 = 0x70;
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_4 = 0x80;
constexpr uint8_t PB_HUB_BASE_ADDR_PORT_5 = 0xA0;

typedef enum{
    PB_HUB_DIGITAL_WRITE0 = 0, // R/W 1 byte
    PB_HUB_DIGITAL_WRITE1, // R/W 1 byte
    PB_HUB_PWM_0, // R/W 1 byte
    PB_HUB_PWM_1, // R/W 1 byte
    PB_HUB_DIGITAL_READ0, // R 1 byte
    PB_HUB_DIGITAL_READ1, // R 1 byte
    PB_HUB_DIGITAL_ANALOG, // R/W 2 Bytes (ADC width 12bit(0-4095))
    PB_HUB_RESERVE,
    PB_HUB_SET_RGB_LED_NUMBER, // r/w 2 Bytes(Default 64)
    PB_HUB_SET_ONE_LED_COLOR, // 5 bytes
    PB_HUB_SET_MORE_LED_COLOR, // 7 bytes r /w
}PbHubRegAddrOffset_e;

class PbHub
{


};