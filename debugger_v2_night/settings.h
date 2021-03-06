#define HW_SERIAL_BAUD_RATE 9600
#define CURRENT_YEAR 2018
#define FILE_NAME_DEFAULT "report.txt"   //  <~~~~ if FILE_NAME_TIME_STAMP is false it will make all log into a same file.
#define FILE_NAME_TIME_STAMP true        //  <~~~~ make ' true ' if you want the log report file in terms of time stamp.
#define QUICK_BOOT true                  //  <~~~~ skip all testing sequence when it set to ' true '.
#define LOGGER_NAME "lgr_02"         //  <~~~~ provide a new name here
/*******************************************************************************
  project name : debugger
  version : v1.0
  date of project start : 4-june-2018.
  developer : karthikeyan periyasamy
  email : qkarthi@gmail.com

  project requirements  :
  1.recording the serial (rx) data from external device / connections and write the data to sd card. <~~~~ done
  2.indicating the reading and writing of files in sd card by using the leds. <~~~~ done for writing
  3.utilizing RTC module to make the log with respect to time. <~~~~ done
  4.indicating the working status by blinking led. <~~~~ done
  5.if SD card failed to mount it should be indicated with an led. <~~~~ done
  6.project debug starting by using a button click and end by using a button click. <~~~~ done - only to make mark down
  7.posting the errors with MQTT as programmed ( fatal ) . <~~~~ pending !

*******************************************************************************/


