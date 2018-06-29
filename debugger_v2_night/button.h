unsigned long button_press_last_millis = 0;
void mark_write_up(){
  led_on(ACK_LED);
  if(millis()-button_press_last_millis>10000){
     data_logger(rtc_timestamp()+ "=MAN_LOG_MARK" +"@"+String(millis()) );
     button_press_last_millis=millis();
  }
   led_off(ACK_LED);
}
void button_setup(){
   pinMode(PUSH_BUTTON, INPUT);
}

void time_note(){
    if(digitalRead(PUSH_BUTTON)==HIGH){
    mark_write_up();
   }
}

