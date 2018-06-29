#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);

#define countof(a) (sizeof(a) / sizeof(a[0]))
char time_stamp_string[20];
String Klogger_time_stamp = "";

void rtc_setup_func() {
  Rtc.Begin();
}

int rtc_month() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Month();
}
int rtc_day() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Day();
}
int rtc_year() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Year();
}
int rtc_hour() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Hour();
}
int rtc_minute() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Minute();
}
int rtc_second() {
  RtcDateTime now = Rtc.GetDateTime();
  return now.Second();
}
String rtc_timestamp() {
  RtcDateTime now = Rtc.GetDateTime();
  snprintf_P(time_stamp_string, countof(time_stamp_string), PSTR("%04u-%02u-%02u_%02u:%02u:%02u"),
             now.Year(),
             now.Month(),
             now.Day(),
             now.Hour(),
             now.Minute(),
             now.Second() );
  return (time_stamp_string);
}
String rtc_file_name_time_stamp() {
  RtcDateTime now = Rtc.GetDateTime();
  snprintf_P(time_stamp_string, countof(time_stamp_string), PSTR("%04u%02u%02u"),
             now.Year(),
             now.Month(),
             now.Day()
            );
  return (time_stamp_string);
}

void self_rtc_checkup() {
  if (rtc_year() >= CURRENT_YEAR)
  {
    if (!QUICK_BOOT) {
      led_blynk_func(WARNING_LED, 2, 500);
    }
  }
  else
  {
    led_on(WARNING_LED);
  }
}
