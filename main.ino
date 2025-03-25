#include <IRremote.h>

#define IR_TX_PIN 6

int _delay = 5;

void send_nec_ir_code(uint32_t code)
{
    IrSender.sendNEC(code, 32);
    delay(_delay);
}

void send_nec_ir_code(uint32_t addr, uint32_t cmd)
{
    IrSender.sendNEC(addr, cmd, true);
    delay(_delay);
}

void send_rc5_ir_code(uint32_t code)
{
    IrSender.sendRC5(code, 12);
    delay(_delay);
}

void send_rc5_ir_code(uint32_t addr, uint32_t cmd, int bits)
{
    IrSender.sendRC5(addr, cmd, bits);
    delay(_delay);
}

void send_rc6_ir_code(uint32_t code, int b)
{
    IrSender.sendRC6(code, b);
    delay(_delay);
}

void send_jvc_ir_code(uint32_t code, int bits)
{
    IrSender.sendJVC(code, 16, false);
    delay(_delay);
}

void send_samsung_ir_code(uint32_t code)
{
    IrSender.sendSAMSUNG(code, 32);
    delay(_delay);
}

void send_samsung_ir_code(uint32_t code, uint32_t func)
{
    IrSender.sendSamsung(code, func, 1);
    delay(_delay);
}

void send_sony_ir_code(uint32_t code, int bits)
{
    for (int i = 0; i < 3; ++i)
    {
        IrSender.sendSony(code, bits);
        delay(40);
    }
    delay(_delay);
}

void send_panasonic_ir_code(uint32_t x, uint32_t y)
{
    IrSender.sendPanasonic(x, y, 1);
    delay(_delay);
}

void send_philips_ir_code(uint32_t addr, uint32_t cmd)
{
  IrSender.sendRC6(addr, cmd, 20);
  delay(_delay);
}

void setup() {

}

void loop() {
  pinMode(IR_TX_PIN, OUTPUT);
  IrSender.begin(IR_TX_PIN);

  send_sony_ir_code(0xA90, 12); //SONY, NEC
  send_nec_ir_code(0x20DF10EF); //LG, SAMSUNG, VIZIO, HISENSE, KENWOOD, PROSCAN, ZENITH
  send_rc5_ir_code(0x80C); //PHILIPS, MAGNAVOX, GRUNDIG, MEDION, SILVERCREST
  send_rc5_ir_code(0xC); //PHILIPS, GRUNDIG, MEDION, WATSON, AEG, SILVERCREST, THOMSON, LG
  send_rc5_ir_code(0x84C); //TELEFUNKEN, SHARP, SANYO
  send_rc5_ir_code(0x4C); //SHARP, TOSHIBA, MEDION
  send_rc5_ir_code(0x44C); //PANASONIC
  send_nec_ir_code(0x2FD48B7); //TOSHIBA, HISENSE, SAMSUNG, APEX, AKAI
  send_samsung_ir_code(0xE0E040BF); //SAMSUNG TV1
  send_samsung_ir_code(0xE0E019E6); //SAMSUNG TV2
  send_samsung_ir_code(0x909040BF); //SAMSUNG
  send_samsung_ir_code(0x07, 0x02); // SAMSUNG UNIVERSAL
  send_rc5_ir_code(0x0F, 0x2A, 12); // TCL
  send_jvc_ir_code(3, 23); // JVC
  send_samsung_ir_code(0x909C837); //SAMSUNG TV3
  send_nec_ir_code(0x8E7152AD); //TOSHIBA
  send_rc6_ir_code(0xC, 20); //PHILIPS RC6
  send_sony_ir_code(0xF50, 12); //SONY
  send_nec_ir_code(0x4, 0x0B); // SENCOR
  send_nec_ir_code(0x40000000, 0x0B000000); // SENCOR
  send_jvc_ir_code(0xF8EB, 16); //SONY, JVC
  send_rc6_ir_code(0x1000C, 20); //PHILIPS RC6
  send_rc5_ir_code(0x301); //SHARP
  send_rc5_ir_code(0xB01); //SHARP
  send_rc5_ir_code(0x9CC); //PHILIPS ITV
  send_nec_ir_code(0x55AA38C7); //PIONEER, SHARP
  send_nec_ir_code(0x00BF, 0x0DF2); // HISENSE
  send_nec_ir_code(0x18E710EF); //NEC TV
  send_nec_ir_code(0x20DFBE41); //LG TV3

  send_panasonic_ir_code(0x800220, 0xD003); // PANASONIC
  send_panasonic_ir_code(0x80022000, 0xD0030000); // PANASONIC

  for (int i = 0; i < 2; ++i) {
    send_panasonic_ir_code(0x4004, 0x100BCBD); //PANASONIC TV1
    delay(40);
  }

  send_nec_ir_code(0x0030, 0x4FB0);

  delay(30);

  for (int i = 0; i < 2; ++i) {
    send_nec_ir_code(0x4CB340BF); //OPTOMA PROJECTOR
    send_nec_ir_code(0xC1AA09F6); //EPSON PROJECTOR/TV
    send_nec_ir_code(0x189728D7); //NEC PROJECTOR    

    send_nec_ir_code(0x0813, 0x8778); // ACER PROJECTOR

    send_nec_ir_code(0x4040, 0x0AF5); // BENQ PROJECTOR
    send_nec_ir_code(0x0030, 0x4EB1); // BENQ PROJECTOR
  
    send_nec_ir_code(0xe8174587); // HITACHI PROJECTOR

    delay(100);
  }

  send_jvc_ir_code(0xC0E8, 16); //JVC, THOMSON
  send_samsung_ir_code(0x6060F00F); //AIKO
  send_nec_ir_code(0x86C6807F); //ACER
  send_samsung_ir_code(0x1010D02F); //HAIER
  send_nec_ir_code(0x6F900FF); //BENQ
  send_nec_ir_code(0x1FE41BE); //TELEFUNKEN
  send_nec_ir_code(0x7B6B4FB0); //LG
  send_nec_ir_code(0x986718E7); //MEDION
  send_nec_ir_code(0x4B36E21D); //ONKYO
  send_nec_ir_code(0x4B36D32C); //ONKYO
  send_nec_ir_code(0x189710EF); //NEC PROJECTOR ON
  send_nec_ir_code(0x1897639C); //NEC PROJECTOR [INPUT=SVIDEO] (No one uses S-video)
  send_nec_ir_code(0xAB500FF); //YAMAHA
  send_nec_ir_code(0x1FE48B7); //FUJITSU
  send_nec_ir_code(0x3E060FC0); //AIWA
  send_rc5_ir_code(0xC3D); //GRUNDIG FINE ARTS
  send_nec_ir_code(0xFB38C7); //GRUNDIG, MEDION
  send_nec_ir_code(0x1CE348B7); //SANYO
  send_nec_ir_code(0x1CE338C7); //HITACHI, SANYO, GRUNDIG
  send_nec_ir_code(0x10EFEB14); //AOC
  send_nec_ir_code(0xAF5FC03); //DENON
  send_nec_ir_code(0xBD807F); //PHILIPS LCD MONITOR
  send_nec_ir_code(0xC18F50AF); //VIEWSONIC
  send_nec_ir_code(0x8C73817E); //LENOVO
  send_nec_ir_code(0x38C7AC0A); //MALATA
  send_nec_ir_code(0xDE010FC0); //AIWA
  send_nec_ir_code(0xFD00FF); //TELEFUNKEN
  delay(500);
}
