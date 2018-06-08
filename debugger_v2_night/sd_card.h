#include <SPI.h>
#include <SD.h>

bool sd_card_mount_pass_var = false;
String current_file_name;

File myFile;
File dataFile;

void self_sd_checkup() {
  if (!SD.begin(CHIP_SELECT))
  {
    led_on(ERROR_LED);
  }
  else
  {
    if(!QUICK_BOOT){
    led_blynk_func(ERROR_LED, 2, 500);
    }
    sd_card_mount_pass_var = 1;
  }
}
void file_create_func(String file_name) {
  myFile = SD.open(file_name, FILE_WRITE);
  myFile.close();
  //Serial.println(file_name);
}

void default_file_checkup() {
  if (SD.exists(FILE_NAME_DEFAULT)) {
     if(!QUICK_BOOT){
    led_blynk_func(ACK_LED, 2, 500);
     }
  } else {
    file_create_func(FILE_NAME_DEFAULT);
  }
}

void data_logger(String data_str) {
  if(FILE_NAME_TIME_STAMP){
     dataFile = SD.open(current_file_name, FILE_WRITE); 
  }else{
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


