#include <FlexCAN.h>

/******* PIN definitions ***********/
#define BTN_TOGGLE 9
#define BTN_CYCLE 10
#define BTN_BOOST 11
#define BTN_START 12
#define LED_START 7
#define LED_BMS 6
#define LED_IMD 5
#define READY_SOUND 8
#define PEDAL_SIGNAL_A A3
#define PEDAL_SIGNAL_B A4
#define PEDAL_SIGNAL_C A5

/*****Dashboard States and Fault Flags********/
bool imd_fault;
bool bms_fault;
bool bspd_fault;
bool cool_fault;
bool comm_fault;
bool motor_fault;
bool pedal_fault;
bool general_fault;

Metro timer_btn_start = Metro(10);

unsigned long lastDebounceTOGGLE = 0;  // the last time the output pin was toggled
unsigned long lastDebounceBOOST = 0;  // the last time the output pin was toggled
unsigned long lastDebounceSTART = 0;  // the last time the output pin was toggled
bool btn_start_pressed = false;
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

/*************** BUTTON TYPES ****************
 *  Start Button
 *  Toggle Button
 *  Select Button
 *  Boost Button
*/
int count;

/**
 * CAN Variables
 */
FlexCAN can(500000);
FlexCAN CAN(500000);
static CAN_message_t msg;

void setup() {
    // put your setup code here, to run once:
    imd_fault = false;
    bms_fault = false;
    bspd_fault = false;
    cool_fault = false;
    comm_fault = false;
    motor_fault = false;
    pedal_fault = false;
    general_fault = false;
    Serial.begin(115200);
    can.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  pollForButtonPress();
}

void pollForButtonPress {
  /*
   * Handle start button press and depress
   */
  if (digitalRead(BTN_START) == btn_start_pressed && !btn_start_debouncing) { // Value is different than stored
    btn_start_debouncing = true;
    timer_btn_start.reset();
  }
  if (btn_start_debouncing && digitalRead(BTN_START) != btn_start_pressed) { // Value returns during debounce period
    btn_start_debouncing = false;
  }
  if (btn_start_debouncing && timer_btn_start.check()) { // Debounce period finishes without value returning
    btn_start_pressed = !btn_start_pressed;
    if (btn_start_pressed) {
      lastDebounceSTART++;
      Serial.print("Start button pressed id ");
      Serial.println(lastDebounceSTART);
    }
  }
}

void toggleButtonInterrupt {

}

void startButtonInterrupt {
}
