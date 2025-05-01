#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Arduino.h>

extern int m_send_pin;

void fn_send_samsung(String address, String command);
void fn_send_sony(String address, String command, uint8_t bits);
void fn_send_rc6(String address, String command);
void fn_send_rc5(String address, String command);
void fn_send_nec_ext(String address, String command);
void fn_send_nec(String address, String command);
void fn_send_raw(uint16_t frequency, String rawData);
void fn_send_kaseikyo(String address, String command);