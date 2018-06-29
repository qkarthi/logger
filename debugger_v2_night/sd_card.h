#include <SPI.h>
#include <SD.h>

bool sd_card_mount_pass_var = false;
String current_file_name;
bool card_removed_run_state = false;
String card_removed_time_stamp = "";

Sd2Card sd_mmc_card;

File dataFile;

void sys_logger(String data_str) {
  dataFile = SD.open("syslog.txt", FILE_WRITE);
  dataFile.println(data_str);
  dataFile.close();
}
void self_sd_checkup() {
  if (!SD.begin(CHIP_SELECT))
  {
    led_on(ERROR_LED);
  }
  else
  {
    if (!QUICK_BOOT) {
      led_blynk_func(ERROR_LED, 2, 500);
    }
    sd_card_mount_pass_var = 1;
    led_off(ERROR_LED);
  }
}
void file_create_func(String file_name) {
  dataFile = SD.open(file_name, FILE_WRITE);
  dataFile.close();
  sys_logger(rtc_timestamp() + "=F_CRE:" + ( file_name ));
}

void default_file_checkup() {
  if (SD.exists(FILE_NAME_DEFAULT)) {
    if (!QUICK_BOOT) {
      led_blynk_func(ACK_LED, 2, 500);
    }
    sys_logger(rtc_timestamp() + "=F_EX:" + String(FILE_NAME_DEFAULT ));
  } else {
    file_create_func(FILE_NAME_DEFAULT);
  }
}

void data_logger(String data_str) {
  if (FILE_NAME_TIME_STAMP) {
    dataFile = SD.open(current_file_name, FILE_WRITE);
  } else {
    dataFile = SD.open(FILE_NAME_DEFAULT, FILE_WRITE);
  }
  if (dataFile) {
    dataFile.println(data_str);
    dataFile.close();
  }
  else {
    led_on(ACK_LED);
  }
}


void sd_mmc_unplugged_check() {
  if (!sd_mmc_card.init(SPI_HALF_SPEED, CHIP_SELECT)) {
    if (!card_removed_run_state) {
      card_removed_time_stamp = (String(rtc_timestamp()));
    }
    digitalWrite(ERROR_LED, HIGH);
    card_removed_run_state = true ;
  } else {
    if (card_removed_run_state) {
      digitalWrite(ERROR_LED, LOW);
      card_removed_run_state = false ;
      if (!FILE_NAME_TIME_STAMP) {
        default_file_checkup();
      } else {
        delay(200);
       sys_logger("<_"+rtc_timestamp()+"_>");
       sys_logger("=LGR_STD_T-" + Klogger_time_stamp);
       sys_logger("=RM-" + card_removed_time_stamp);
       sys_logger("=IN @" + String(millis()));
        current_file_name = (String(rtc_file_name_time_stamp()) + ".txt");
        if (!SD.exists(current_file_name)) {
          sys_logger("=NO_F:" + current_file_name );
          file_create_func(current_file_name);
        }
      }
    }
  }
}

