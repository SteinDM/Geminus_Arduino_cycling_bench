#include "plcLib.h"  // "" for local library

/* Programmable Logic Controller Library for the Arduino and Compatibles
   Pulsed Output - Creating a repeating pulse using the timerCycle command
   Connections:
   Input - Enable input connected to input X0 (Arduino pin A0)
   Output - Pulse Waveform on LED connected to output Y0 (Arduino pin 3)
   Software and Documentation:
   https://github.com/wditch/plcLib
*/

// Variables:
unsigned long AUX0 = 0;                 // Pulse low timer variable
unsigned long AUX1 = 0;                 // Pulse high timer variable

unsigned long AUX2 = 0;                 // Pulse low timer variable
unsigned long AUX3 = 0;                 // Pulse high timer variable
Counter ctr(100, 1);                    // Counts down, starting at 100

void setup() {
  setupPLC();                           // Define inputs and outputs
  Serial.begin(9600);      // Open serial connection over USB
  in (0);
  out(Y0);
}

void loop() {
if (X0){                          // Read Enable input (1 = enable)
  inNot ((ctr.lowerQ()));
  inNot(timerCycle(AUX0, 100, AUX1, 100));     // Repeating pulse, low = 0.9 s, high = 0.1 s
  out(Y0);                              // Send pulse waveform to Output 0
  ctr.countDown();                      // Count down


//  ctr.lowerQ();            // Display Count Up output on Y1
//  out(Y1);
/*  inNot (X0);                           // Read Enable input (1 = enable)
  timerCycle(AUX2, 750, AUX3, 500);     // Repeating pulse, low = 0.9 s, high = 0.1 s
  out(Y1);                              // Send pulse waveform to Output 0
  ctr.countDown();                      // Count down
*/
  Serial.println(ctr.count());          // Send count to serial port
}
}
