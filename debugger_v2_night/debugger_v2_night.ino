#include "settings.h"
#include "hw_pin.h"
#include "led.h"
#include "rtc.h"
#include "sd_card.h"
#include "reseter.h"
#include "button.h"
#include "sw_serial.h"

String serial_str;
unsigned long work_indicator_act_last_millis = 0;
int  work_indicator_status = false;
bool logging_init = false;

void setup() {
  
  Serial.begin(HW_SERIAL_BAUD_RATE);
  sw_serial.begin(SW_SERIAL_BAUD_RATE);
  
  led_setup();
  if (!QUICK_BOOT) {
    self_led_checkup(2);
    delay(2000);
  }
  rtc_setup_func();
  self_rtc_checkup();
  self_sd_checkup();
  button_setup();

  if (sd_card_mount_pass_var) {
    if (!FILE_NAME_TIME_STAMP) {
      default_file_checkup();
    } else {
      current_file_name = (String(rtc_file_name_time_stamp()) + ".txt");
      if (!SD.exists(current_file_name)) {
        file_create_func(current_file_name);
      }
    }
  }
}
void loop() {
  if (sd_card_mount_pass_var) {
  sw_serial.listen();
    if (!logging_init) {
      data_logger(rtc_timestamp() + "=AUTO_LOGGING_STARTED" + "@" + String(millis()) );
      //Serial.println(rtc_timestamp() + "=AUTO_LOGGING_STARTED" );
      if(RESET_SLAVE_AFTER_BOOT){
        reset_slave();
      }
      logging_init = true;
    }
    time_note();
    if ((millis() - work_indicator_act_last_millis) >= 300) {
      work_indicator_status = !work_indicator_status;
      digitalWrite(SUCCESS_LED, work_indicator_status);
      work_indicator_act_last_millis = millis();
    }
    if (sw_serial.available() > 0)
    {
      led_on(ACK_LED);
      serial_str = sw_serial.readString();
      delay(5);
      data_logger(rtc_timestamp() + ">" + serial_str);
      Serial.println(serial_str);
      led_off(ACK_LED);
    }
  }
}



