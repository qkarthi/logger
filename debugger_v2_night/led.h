void led_setup() {
  pinMode(ERROR_LED, OUTPUT);
  pinMode(WARNING_LED, OUTPUT);
  pinMode(SUCCESS_LED, OUTPUT);
  pinMode(ACK_LED, OUTPUT);

  digitalWrite(ERROR_LED, LOW);
  digitalWrite(WARNING_LED, LOW);
  digitalWrite(SUCCESS_LED, LOW);
  digitalWrite(ACK_LED, LOW);
}
void self_led_checkup(int x) {
  for (int i = 1; i <= x; i++) {
    digitalWrite(ERROR_LED, HIGH);
    digitalWrite(WARNING_LED, HIGH);
    digitalWrite(SUCCESS_LED, HIGH);
    digitalWrite(ACK_LED, HIGH);
    delay(500);
    digitalWrite(ERROR_LED, LOW);
    digitalWrite(WARNING_LED, LOW);
    digitalWrite(SUCCESS_LED, LOW);
    digitalWrite(ACK_LED, LOW);
    delay(1000);
  }
}

void led_blynk_func(int led_no, int blink_count, int intervel)
{
  for (int i = 1; i <= blink_count; i++) {
    digitalWrite(led_no, HIGH);
    delay(intervel);
    digitalWrite(led_no, LOW);
    delay(intervel);
  }
}

void led_on(int led_no) {
  digitalWrite(led_no, HIGH);
}

void led_off(int led_no) {
  digitalWrite(led_no, LOW);
}

