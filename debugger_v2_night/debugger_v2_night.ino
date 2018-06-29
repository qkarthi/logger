#include "settings.h"
#include "hw_pin.h"
#include "led.h"
#include "rtc.h"
#include "sd_card.h"
#include "button.h"

String serial_str;
unsigned long work_indicator_act_last_millis = 0;
int  work_indicator_status = false;
bool logging_init = false;
char buffer_char;
int serial_char_count = 0;
//unsigned long rst_limit_millis = 108000000;

unsigned long rst_limit_millis = 60000;
bool card_delayed_to_insert = false ;
void(* rstFunc) (void) = 0;
void setup() {

  Serial.begin(HW_SERIAL_BAUD_RATE);

  led_setup();
  if (!QUICK_BOOT) {
    self_led_checkup(2);
    delay(2000);
  }
  rtc_setup_func();
  self_rtc_checkup();
  Klogger_time_stamp = String(rtc_file_name_time_stamp());
  self_sd_checkup();
  button_setup();


}
void loop() {
  if (sd_card_mount_pass_var) {
    if (!logging_init) {
      if (!FILE_NAME_TIME_STAMP) {
        default_file_checkup();
      } else {
        current_file_name = (String(rtc_file_name_time_stamp()) + ".txt");
        if (!SD.exists(current_file_name)) {
          file_create_func(current_file_name);
        }
      }
      data_logger(rtc_timestamp() + "=LOGGER_STARTED_TIME" + "  -  " + Klogger_time_stamp);
      if (card_delayed_to_insert) {
        data_logger(rtc_timestamp() + "=CARD_NOT_PRESENT_DURING_BOOT" );
      } else {
        data_logger(rtc_timestamp() + "=CARD_PRESENT_DURING_BOOT" );
      }
      data_logger(rtc_timestamp() + "=AUTO_LOGGING_STARTED" + "  -  " + "millis -> " + String(millis()) );
      logging_init = true ;
    }
    time_note();
    if ((millis() - work_indicator_act_last_millis) >= 300) {
      work_indicator_status = !work_indicator_status;
      digitalWrite(SUCCESS_LED, work_indicator_status);
      work_indicator_act_last_millis = millis();
    }
    if (Serial.available()) {
      while (Serial.available() > 0) {
        {
          led_on(ACK_LED);
          buffer_char = (char(Serial.read()));
          serial_str = serial_str + buffer_char;
          if (buffer_char == '\n') {
            data_logger(rtc_timestamp() + " > " + serial_str);
            serial_str = "";
          }
          led_off(ACK_LED);
        }
      }
    }
    sd_mmc_unplugged_check();
  } else {
    card_delayed_to_insert = true ;
    self_sd_checkup();
  }

  if (millis() > rst_limit_millis) {
    data_logger(rtc_timestamp() + " = SYSTEM_REBOOT" + "@" + String(millis()) );
    rstFunc();
  }

}




