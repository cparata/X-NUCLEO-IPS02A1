/**
 ******************************************************************************
 * @file    X_NUCLEO_IPS02A1_HelloWorld.ino
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    8 May 2020
 * @brief   Arduino test application for the STMicroelectronics X-NUCLEO-IPS02A1
 *          Power Switch Expansion Board.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/

/* Arduino specific header files. */
#include "Arduino.h"
#include "assert.h"
#include "XNucleoIPS02A1.h"

/* HW settings */
/* Pay attention before changing HW settings, they must be coherent with you HW design */
/* Power Switch Connection to Arduino connectors */
#define IPS02A1_PIN_IN_1             (D5)
#define IPS02A1_PIN_IN_2             (D6)
#define IPS02A1_PIN_FR_STBY          (D4)
#define IPS02A1_PIN_CURRENTSENSE1    (A2)
#define IPS02A1_PIN_CURRENTSENSE2    (A3)
 
/* V-Ref */
#define V_REF 3.3
/* Rsense Value */
#define R_SENSE 1e3
/* R_D1 */
#define R_D1 56e3
/* R_D2 */
#define R_D2 36e3

#define SerialPort Serial


/*** Variables ----------------------------------------------------------------- ***/

static XNucleoIPS02A1 &ips_expansion_board = XNucleoIPS02A1::instance(IPS02A1_PIN_IN_1,
                                                                      IPS02A1_PIN_IN_2,
                                                                      IPS02A1_PIN_FR_STBY,
                                                                      IPS02A1_PIN_CURRENTSENSE1,
                                                                      IPS02A1_PIN_CURRENTSENSE2,                                                                         
                                                                      V_REF,
                                                                      R_SENSE,
                                                                      R_D1,
                                                                      R_D2);
   
float multisense_signal = 0;    // Multisense pin - signal level
bool  button_pressed = 0;       // User Button
int   test_sequence = 1;        // Test sequence counter
#ifndef USER_BTN
const int buttonPin = PC13;
#else
const int buttonPin = USER_BTN;
#endif
int pushButtonState = LOW;
 
//------------------------------------
// Hyperterminal configuration
// 115200 bauds, 8-bit data, no parity
//------------------------------------
void led_blink (int test_sequence);
void write_serial (void);
void reset_pins (void);


/*** Functions ----------------------------------------------------------------- ***/

void setup() {
  // Led.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial for output.
  SerialPort.begin(115200);

  // configure the button pin as input
  pinMode(buttonPin, INPUT);
  pushButtonState = (digitalRead(buttonPin)) ?  LOW : HIGH;

  SerialPort.println("############################################################ ");
  SerialPort.println("###################  TEST PROCEDURE ######################## ");
  SerialPort.println("############################################################ ");
  SerialPort.println("");
  SerialPort.println("This demo performs current measurements on Ch1 and Ch2  ");
  SerialPort.println("in the following conditions: ");
  SerialPort.println("");
  SerialPort.println(" 1) Ch1 OFF, Ch2 OFF ");
  SerialPort.println(" 2) Ch1 ON,  Ch2 OFF ");
  SerialPort.println(" 3) Ch1 OFF, Ch2 ON ");
  SerialPort.println(" 4) Ch1 ON,  Ch2 ON ");
  SerialPort.println("");
    
  SerialPort.println("Start test Procedure.... ");
  SerialPort.println("");
  SerialPort.println("PRESS USER BUTTON (Blue One) on NUCLEO to perform single test ");
  SerialPort.println("");
  SerialPort.println("");
}

void loop() {
  if(digitalRead(buttonPin) == pushButtonState) {
    /* Debouncing */
    delay(50);

    /* Wait until the button is released */
    while (digitalRead(buttonPin) == pushButtonState);

    /* Debouncing */
    delay(50);

    test_sequence ++;
 
    digitalWrite(LED_BUILTIN, HIGH); // LED is ON
    delay(50);   // 50 ms
    digitalWrite(LED_BUILTIN, LOW); // LED is OFF
 
    button_pressed = 1;
  }

  if(button_pressed) {
    button_pressed = 0;

    led_blink(test_sequence);

    switch (test_sequence) {
      case (1):
        SerialPort.println("############################################################ ");
        SerialPort.println("###################  TEST PROCEDURE ######################## ");
        SerialPort.println("############################################################ ");
        SerialPort.println("");
        SerialPort.println("This demo performs current measurements on Ch1 and Ch2  ");
        SerialPort.println("in the following conditions: ");
        SerialPort.println("");
        SerialPort.println(" 1) Ch1 OFF, Ch2 OFF ");
        SerialPort.println(" 2) Ch1 ON,  Ch2 OFF ");
        SerialPort.println(" 3) Ch1 OFF, Ch2 ON ");
        SerialPort.println(" 4) Ch1 ON,  Ch2 ON ");
        SerialPort.println("");
        SerialPort.println("");
        SerialPort.println("");
        break;
 
      case (2):
        SerialPort.println("Test 1: StandBy");
        reset_pins();
        delay(100);
        write_serial();
        multisense_signal = ips_expansion_board.get_current(CHANNEL_1);
        SerialPort.print("Current Ch1 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        multisense_signal = ips_expansion_board.get_current(CHANNEL_2);
        SerialPort.print("Current Ch2 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        SerialPort.println("");
        SerialPort.println("");
        break;
 
      case(3):
        SerialPort.println("Test 2: Ch1=ON, CH2=OFF");
        digitalWrite(ips_expansion_board.vps2535h.In_1, HIGH);
        digitalWrite(ips_expansion_board.vps2535h.In_2, LOW);
        digitalWrite(ips_expansion_board.vps2535h.Fr_Stby, HIGH);
        delay(100);
        write_serial();
        multisense_signal = ips_expansion_board.get_current(CHANNEL_1);
        SerialPort.print("Current Ch1 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        multisense_signal = ips_expansion_board.get_current(CHANNEL_2);
        SerialPort.print("Current Ch2 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        delay(500);
        reset_pins();
        SerialPort.println("");
        SerialPort.println("");
        break;
 
      case(4):
        SerialPort.println("Test 3: Ch1=OFF, CH2=ON");
        digitalWrite(ips_expansion_board.vps2535h.In_1, LOW);
        digitalWrite(ips_expansion_board.vps2535h.In_2, HIGH);
        digitalWrite(ips_expansion_board.vps2535h.Fr_Stby, HIGH);
        delay(100);
        write_serial();
        multisense_signal = ips_expansion_board.get_current(CHANNEL_1);
        SerialPort.print("Current Ch1 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        multisense_signal = ips_expansion_board.get_current(CHANNEL_2);
        SerialPort.print("Current Ch2 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        delay(500);
        reset_pins();
        SerialPort.println("");
        SerialPort.println("");
        break;
 
      case(5):
        SerialPort.println("Test 4: Ch1=ON, CH2=ON");
        digitalWrite(ips_expansion_board.vps2535h.In_1, HIGH);
        digitalWrite(ips_expansion_board.vps2535h.In_2, HIGH);
        digitalWrite(ips_expansion_board.vps2535h.Fr_Stby, HIGH);
        delay(100);
        write_serial();
        multisense_signal = ips_expansion_board.get_current(CHANNEL_1);
        SerialPort.print("Current Ch1 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        multisense_signal = ips_expansion_board.get_current(CHANNEL_2);
        SerialPort.print("Current Ch2 = ");
        SerialPort.print(multisense_signal);
        SerialPort.println(" ");
        delay(500);
        reset_pins();
        SerialPort.println("");
        SerialPort.println("");
        break;
 
      default:
        SerialPort.println("End of Test Cycle. Press the user button to continue...");
        SerialPort.println("");
        SerialPort.println("");
        test_sequence = 0;
        reset_pins();
        break; 
    }
  }
}

void led_blink(int test_sequence) {
  for (int test = 0; test < test_sequence; test++) {
    digitalWrite(LED_BUILTIN, HIGH); // LED is ON
    delay(50);  // 50 ms
    digitalWrite(LED_BUILTIN, LOW); // LED is OFF
    delay(50);  // 50 msec
  }
  delay(1000- (test_sequence * 2 * 50));
}

void write_serial() {
  SerialPort.print("Input 1= ");
  SerialPort.print(digitalRead(ips_expansion_board.vps2535h.In_1));
  SerialPort.print("\t");
  SerialPort.print("Input 2= ");
  SerialPort.print(digitalRead(ips_expansion_board.vps2535h.In_2));
  SerialPort.print("\t");
  SerialPort.print("Fr_Stby= ");
  SerialPort.print(digitalRead(ips_expansion_board.vps2535h.Fr_Stby));
  SerialPort.print("\t");
  SerialPort.println("");
}

void reset_pins() {
  digitalWrite(ips_expansion_board.vps2535h.In_1, LOW);
  digitalWrite(ips_expansion_board.vps2535h.In_2, LOW);
  digitalWrite(ips_expansion_board.vps2535h.Fr_Stby, LOW);
}
