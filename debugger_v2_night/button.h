unsigned long button_press_last_millis = 0;
void finish_log_write_up(){
  if(millis()-button_press_last_millis>10000){
     data_logger(rtc_timestamp()+ "=MANUAL_LOGGING_MARK" +"@"+String(millis()) );
     //Serial.println(rtc_timestamp() + "=MANUAL_LOGGING_MARK" );
     reset_slave();
     button_press_last_millis=millis();
  }
}
void button_setup(){
   pinMode(PUSH_BUTTON, INPUT);
}

void time_note(){
    if(digitalRead(PUSH_BUTTON)==HIGH){
    finish_log_write_up();
   }
}

