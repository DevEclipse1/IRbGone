#include "send.h"

int m_send_pin = -1;

uint32_t swap32(uint32_t value) {
    return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) | ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24);
}

uint64_t reverse_bits(uint64_t input, uint16_t nbits) {
    if (nbits <= 1) return input;

    nbits = std::min(nbits, (uint16_t)(sizeof(input) * 8));
    uint64_t output = 0;
    for (uint16_t i = 0; i < nbits; i++) {
      output <<= 1;
      output |= (input & 1);
      input >>= 1;
    }

    return (input << nbits) | output;
  }

void fn_send_samsung(String address, String command) {
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    uint8_t addressValue = strtoul(address.substring(0, 2).c_str(), nullptr, 16);
    uint8_t commandValue = strtoul(command.substring(0, 2).c_str(), nullptr, 16);
    uint64_t data = irsend.encodeSAMSUNG(addressValue, commandValue);

    irsend.sendSAMSUNG(data, 32);
}

void fn_send_sony(String address, String command, uint8_t nbits) {
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    address.replace(" ", "");
    command.replace(" ", "");

    uint32_t addressValue = strtoul(address.c_str(), nullptr, 16);
    uint32_t commandValue = strtoul(command.c_str(), nullptr, 16);

    uint16_t swappedAddr = static_cast<uint16_t>(swap32(addressValue));
    uint8_t swappedCmd = static_cast<uint8_t>(swap32(commandValue));

    uint32_t data;

    if (nbits == 12) {
        data = ((swappedAddr & 0x1F) << 7) | (swappedCmd & 0x7F);
    } else if (nbits == 15) {
        data = ((swappedAddr & 0xFF) << 7) | (swappedCmd & 0x7F);
    } else if (nbits == 20) {
        data = ((swappedAddr & 0x1FFF) << 7) | (swappedCmd & 0x7F);
    } else {
        Serial.println("Invalid Sony (SIRC) protocol bit size.");
        return;
    }

    data = reverse_bits(data, nbits);
    irsend.sendSony(data, nbits, 2);
}

void fn_send_rc5(String address, String command)
{
    IRsend irsend(m_send_pin, true);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    uint8_t addressValue = strtoul(address.substring(0, 2).c_str(), nullptr, 16);
    uint8_t commandValue = strtoul(command.substring(0, 2).c_str(), nullptr, 16);
    uint16_t data = irsend.encodeRC5(addressValue, commandValue);
    irsend.sendRC5(data, 13);
}

void fn_send_rc6(String address, String command)
{
    IRsend irsend(m_send_pin, true);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    address.replace(" ", "");
    command.replace(" ", "");
    uint32_t addressValue = strtoul(address.substring(0, 2).c_str(), nullptr, 16);
    uint32_t commandValue = strtoul(command.substring(0, 2).c_str(), nullptr, 16);
    uint64_t data = irsend.encodeRC6(addressValue, commandValue);

    irsend.sendRC6(data, 20);
}

void fn_send_nec_ext(String address, String command)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    int first_zero_byte_pos = address.indexOf("00", 2);
    if (first_zero_byte_pos != -1) address = address.substring(0, first_zero_byte_pos);
    first_zero_byte_pos = command.indexOf("00", 2);
    if (first_zero_byte_pos != -1) command = command.substring(0, first_zero_byte_pos);

    address.replace(" ", "");
    command.replace(" ", "");

    uint16_t addressValue = strtoul(address.c_str(), nullptr, 16);
    uint16_t commandValue = strtoul(command.c_str(), nullptr, 16);

    uint16_t newAddress = (addressValue >> 8) | (addressValue << 8);
    uint16_t newCommand = (commandValue >> 8) | (commandValue << 8);

    uint16_t lsbAddress = reverse_bits(newAddress, 16);
    uint16_t lsbCommand = reverse_bits(newCommand, 16);

    uint32_t data = ((uint32_t)lsbAddress << 16) | lsbCommand;
    irsend.sendNEC(data, 32);
}

void fn_send_nec(String address, String command)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    uint16_t addressValue = strtoul(address.substring(0, 2).c_str(), nullptr, 16);
    uint16_t commandValue = strtoul(command.substring(0, 2).c_str(), nullptr, 16);
    uint64_t data = irsend.encodeNEC(addressValue, commandValue);
    irsend.sendNEC(data, 32);
}

void fn_send_nec_code(uint32_t cmd)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);
    irsend.sendNEC(cmd, 32);
}

void fn_send_raw(uint16_t frequency, String rawData)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    uint16_t dataBufferSize = 1;
    for (int i = 0; i < rawData.length(); i++) {
        if (rawData[i] == ' ') dataBufferSize += 1;
    }
    uint16_t *dataBuffer = (uint16_t *)malloc((dataBufferSize) * sizeof(uint16_t));

    uint16_t count = 0;
    while (rawData.length() > 0 && count < dataBufferSize) {
        int delimiterIndex = rawData.indexOf(' ');
        if (delimiterIndex == -1) { delimiterIndex = rawData.length(); }
        String dataChunk = rawData.substring(0, delimiterIndex);
        rawData.remove(0, delimiterIndex + 1);
        dataBuffer[count++] = (dataChunk.toInt());
    }

    irsend.sendRaw(dataBuffer, count, frequency);

    free(dataBuffer);
}

void fn_send_kaseikyo(String address, String command)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    address.replace(" ", "");
    command.replace(" ", "");

    uint32_t addressValue = strtoul(address.c_str(), nullptr, 16);
    uint32_t commandValue = strtoul(command.c_str(), nullptr, 16);

    uint32_t newAddress = swap32(addressValue);
    uint16_t newCommand = static_cast<uint16_t>(swap32(commandValue));

    uint8_t id = (newAddress >> 24) & 0xFF;
    uint16_t vendor_id = (newAddress >> 8) & 0xFFFF;
    uint8_t genre1 = (newAddress >> 4) & 0x0F;
    uint8_t genre2 = newAddress & 0x0F;

    uint16_t data = newCommand & 0x3FF;

    byte bytes[6];
    bytes[0] = vendor_id & 0xFF;
    bytes[1] = (vendor_id >> 8) & 0xFF;

    uint8_t vendor_parity = bytes[0] ^ bytes[1];
    vendor_parity = (vendor_parity & 0xF) ^ (vendor_parity >> 4);

    bytes[2] = (genre1 << 4) | (vendor_parity & 0x0F);
    bytes[3] = ((data & 0x0F) << 4) | genre2;
    bytes[4] = ((id & 0x03) << 6) | ((data >> 4) & 0x3F);

    bytes[5] = bytes[2] ^ bytes[3] ^ bytes[4];

    uint64_t lsb_data = 0;
    for (int i = 0; i < 6; i++) { lsb_data |= (uint64_t)bytes[i] << (8 * i); }

    uint64_t msb_data = reverse_bits(lsb_data, 48);

    irsend.sendPanasonic64(msb_data, 48);
}

void fn_send_rca(String address, String command)
{
    IRsend irsend(m_send_pin);
    irsend.begin();
    pinMode(m_send_pin, OUTPUT);

    address.replace(" ", "");
    command.replace(" ", "");

    uint8_t addressValue = strtoul(address.substring(0, 2).c_str(), nullptr, 16);
    uint8_t commandValue = strtoul(command.substring(0, 2).c_str(), nullptr, 16);

    uint16_t addr = addressValue & 0xF;
    uint16_t cmd = commandValue & 0xFF;
    uint16_t addr_inv = (~addressValue) & 0xF;
    uint16_t cmd_inv = (~commandValue) & 0xFF;

    uint32_t rca_data = addr | (cmd << 4) | (addr_inv << 12) | (cmd_inv << 16);

    const uint16_t bit_mark = 560;
    const uint16_t zero_space = 560;
    const uint16_t one_space = 1690;

    uint16_t raw[40];
    for (int i = 0; i < 20; i++) {
        raw[i*2] = bit_mark;
        raw[i*2+1] = (rca_data & (1 << (19-i))) ? one_space : zero_space;
    }

    irsend.sendRaw(raw, 40, 38);
}
