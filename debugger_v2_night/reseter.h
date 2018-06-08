void reseter_setup(){
   pinMode(IF_PIN_3, OUTPUT);
   digitalWrite(IF_PIN_3, RESETER_PIN_PULLUP);
}

void reset_slave(){
   digitalWrite(IF_PIN_3, !RESETER_PIN_PULLUP);
   delay(300);
   digitalWrite(IF_PIN_3, RESETER_PIN_PULLUP);
}

