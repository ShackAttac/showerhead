#include <Arduino.h>

// Motor controller pins for four actuators
const int motorPins[8] = {33, 32, 19, 21, 25, 26, 27, 14};
// pins 32 and 33 control top actuator. motorPins[0] and motorPins[1]
// pins 19 and 21 control left actuator. motorPins[2] and motorPins[3]
// pins 25 and 26 control bottom Actuator. motorPins[4] and motorPins[5]
// pins 27 and 14 control right Actuator. motorPins[6] and motorPins[7]

// Input pins for signals from the touchscreens
const int Up_In = 15;
const int Down_In = 2;
const int Left_In = 4;
const int Right_In = 16;
const int Cooler_In = 17;
const int Hotter_In = 5;
const int Reset_In = 18;

// input pin for signal from touchscreen on whether or not any button is pressed
const int Button_Pressed = 19;

// Counter for actuator position
// int actuatorCounter[4] = {0, 0, 0, 0}; // Four counters for four actuators
// const int counterMin = 0;  // Adjust these based on your tests
// const int counterMax = 40;  // Estimate this value through experimentation 150 full range


void setup() {
  // Initialize motor pins 1-8 as outputs
  // All start with LOW value
  for (int i = 0; i < 8; i++) {
    pinMode(motorPins[i], OUTPUT); 
  }

  // Initialize the input pins
  pinMode(Up_In, INPUT_PULLUP);
  pinMode(Down_In, INPUT_PULLUP);
  pinMode(Left_In, INPUT_PULLUP);
  pinMode(Right_In, INPUT_PULLUP);
  pinMode(Cooler_In, INPUT_PULLUP);
  pinMode(Hotter_In, INPUT_PULLUP);
  pinMode(Reset_In, INPUT_PULLUP);
  pinMode(Button_Pressed, INPUT_PULLUP);

  // Start serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  //Low state means button was pressed. High state means it wasn't pressed

  // Read current values for the buttons
  int Up_State = digitalRead(Up_In);
  int Down_State = digitalRead(Down_In);
  int Left_State = analogRead(Left_In);
  int Right_State = analogRead(Right_In);
  int Hotter_State = digitalRead(Hotter_In);
  int Cooler_State = digitalRead(Cooler_In);
  int Reset_State = digitalRead(Reset_In);

  //Checks seperate signal to see if any button was pressed.
  int button_pressed = digitalRead(Button_Pressed);
  
  //Variable 

  // Check if any button is pressed. If not nothing should happen regardless of what other signals say
  if (button_pressed == LOW) {
      //Debounce to make sure not getting noise.
      delay(100);

      //Reread inputs
      int Up_State = digitalRead(Up_In);
      int Down_State = digitalRead(Down_In);
      int Left_State = analogRead(Left_In);
      int Right_State = analogRead(Right_In);
      int Hotter_State = digitalRead(Hotter_In);
      int Cooler_State = digitalRead(Cooler_In);
      int Reset_State = digitalRead(Reset_In);
      int button_pressed = digitalRead(Button_Pressed);

      if (button_pressed == LOW) {
        //Was not reading noise
      
        //Check to see which button was pressed.
        //Pressed button should cause showerhead to move in that direction until reach max length or button released
        if (Up_State == LOW){
          //Make top actuator retract
          // digitalWrite(motorPins[0], LOW);
          digitalWrite(motorPins[1], HIGH);

          //Make bottom actuator extend
          digitalWrite(motorPins[4], HIGH);
          // digitalWrite(motorPins[5], LOW);
          
          //Reads the state of the up button until it is released
          while (Up_State == LOW){
            Up_State = digitalRead(Up_In);
          }
          
          //Resets output pins so that actuators will stop moving
          digitalWrite(motorPins[1], LOW);
          digitalWrite(motorPins[4], LOW);
        }
        else if (Down_State == LOW) {
          //Make top actuator extend
          digitalWrite(motorPins[0], HIGH);
          // digitalWrite(motorPins[1], LOW);

          //Make bottom actuator retract
          // digitalWrite(motorPins[4], LOW);
          digitalWrite(motorPins[5], HIGH);
          
          //Reads the state of the down button until it is released
          while (Down_State == LOW){
            Down_State = digitalRead(Down_In);
          }
          
          //Resets output pins so that actuators will stop moving
          digitalWrite(motorPins[0], LOW);
          digitalWrite(motorPins[5], LOW);
        }
        else if (Left_State == LOW) {
          //Make left actuator retract
          digitalWrite(motorPins[2], HIGH);
          // digitalWrite(motorPins[3], LOW);

          //Make right actuator extend
          // digitalWrite(motorPins[6], LOW);
          digitalWrite(motorPins[7], HIGH);
          
          //Reads the state of the left button until it is released
          while (Left_State == LOW){
            Left_State = analogRead(Left_In);
          }
          
          //Resets output pins so that actuators will stop moving
          digitalWrite(motorPins[2], LOW);
          digitalWrite(motorPins[7], LOW);
        }
        else if (Right_State == LOW) {
          // Make left actuator extend
          // digitalWrite(motorPins[2], LOW);
          digitalWrite(motorPins[3], HIGH);

          //Make right actuator retract
          digitalWrite(motorPins[6], HIGH);
          // digitalWrite(motorPins[7], LOW);
          
          //Reads the state of the left button until it is released
          while (Left_State == LOW){
            Left_State = analogRead(Left_In);
          }
          
          //Resets output pins so that actuators will stop moving
          digitalWrite(motorPins[3], LOW);
          digitalWrite(motorPins[6], LOW);
        }
        
        //For when temperature control will be later added.
        // else if (Hotter_State == LOW) {

        // }
        // else if (Cooler_State == LOW) {

        // }

        //If get this far, should always be reset, but not just putting else just in case
        // else if (Reset_State == LOW) {

        // }
      }
    }

   // digitalWrite(motorPins[0], LOW);
    //digitalWrite(motorPins[1], HIGH);
   // digitalWrite(motorPins[2], LOW);
   // digitalWrite(motorPins[3], HIGH);
   // digitalWrite(motorPins[4], LOW);
   // digitalWrite(motorPins[5], HIGH);
   // digitalWrite(motorPins[6], LOW);
   // digitalWrite(motorPins[7], HIGH);
   // for (int i = 0; i < 4; i++) {
   //   if (actuatorCounter[i] > 0){
   // actuatorCounter[i]--;
   //   }
  //}
 // delay(7000);

  //  digitalWrite(motorPins[1], LOW);
   // digitalWrite(motorPins[0], HIGH);
   // digitalWrite(motorPins[3], LOW);
   // digitalWrite(motorPins[2], HIGH);
  //  digitalWrite(motorPins[5], LOW);
  //  digitalWrite(motorPins[4], HIGH);
  //  digitalWrite(motorPins[7], LOW);
  //  digitalWrite(motorPins[6], HIGH);

//for (int i = 0; i < 4; i++) {
//if(actuatorCounter[i] > counterMax/2)

  
 //  while(!allTrue(middle)){
  //for (int j = 0; j < 4; j++){
   //     if(actuatorCounter[j] > counterMax/2){
   // digitalWrite(motorPins[j*2], LOW);
   // digitalWrite(motorPins[j*2+1], LOW);
   // middle[j]=true;
        //}
  //}
  //}
}




// void actuator1(int xValue) {
// //standby
//   if (xValue < 3800 && xValue > 200) {
//     digitalWrite(motorPins[0], LOW); 
//     digitalWrite(motorPins[1], LOW);
//   }
// //Forward
//  else if ( xValue > 1500 && actuatorCounter[0] <= counterMax) {
//     digitalWrite(motorPins[0], HIGH);
//     digitalWrite(motorPins[1], LOW);
//       actuatorCounter[0]++;
//   }
// //Reverse
//   else if (xValue < 1300 && actuatorCounter[0] >= counterMin) {
//     digitalWrite(motorPins[0], LOW);
//     digitalWrite(motorPins[1], HIGH);
//       actuatorCounter[0]--;
//   }
//   //BRAKE
// if (actuatorCounter[0] >= counterMax || actuatorCounter[0] <= counterMin) {
//     //Stop the actuator if at limits
//     digitalWrite(motorPins[0], HIGH);
//     digitalWrite(motorPins[1], HIGH);  // Stop the motor
// }
// }

// void actuator2(int yValue) {
//   //standby
//   if (yValue < 3800 && yValue > 200) {
//     digitalWrite(motorPins[2], LOW); 
//     digitalWrite(motorPins[3], LOW);
//   }
// //Forward
//  else if (yValue > 2000 && actuatorCounter[1] <= counterMax) {
//     digitalWrite(motorPins[2], HIGH);
//     digitalWrite(motorPins[3], LOW);
//       actuatorCounter[1]++;
//   }
// //Reverse
//   else if (yValue < 1800 && actuatorCounter[1] >= counterMin) {
//     digitalWrite(motorPins[2], LOW);
//     digitalWrite(motorPins[3], HIGH);
//       actuatorCounter[1]--;
//   }
//   //BRAKE
// if (actuatorCounter[1] >= counterMax || actuatorCounter[1] <= counterMin) {
//     //Stop the actuator if at limits
//     digitalWrite(motorPins[2], HIGH);
//     digitalWrite(motorPins[3], HIGH);  // Stop the motor
// }
// }

// void actuator3(int xValue) {
//   //standby
//   if (xValue < 3800 && xValue > 200) {
//     digitalWrite(motorPins[4], LOW); 
//     digitalWrite(motorPins[5], LOW);
//   }
// //Forward
//  else if ( xValue < 1300 && actuatorCounter[2] <= counterMax) {
//     digitalWrite(motorPins[4], HIGH);
//     digitalWrite(motorPins[5], LOW);
//       actuatorCounter[2]++;
//   }
// //Reverse
//   else if (xValue > 1500 && actuatorCounter[2] >= counterMin) {
//     digitalWrite(motorPins[4], LOW);
//     digitalWrite(motorPins[5], HIGH);
//       actuatorCounter[2]--;
//   }
//   //BRAKE
// if (actuatorCounter[2] >= counterMax || actuatorCounter[2] <= counterMin) {
//     //Stop the actuator if at limits
//     digitalWrite(motorPins[4], HIGH);
//     digitalWrite(motorPins[5], HIGH);  // Stop the motor
// }
// }

// void actuator4(int yValue) {
//     //standby
//   if (yValue < 3800 && yValue > 200) {
//     digitalWrite(motorPins[6], LOW); 
//     digitalWrite(motorPins[7], LOW);
//   }
// //Forward
//  else if (yValue < 1800 && actuatorCounter[3] <= counterMax) {
//     digitalWrite(motorPins[6], HIGH);
//     digitalWrite(motorPins[7], LOW);
//       actuatorCounter[3]++;
//   }
// //Reverse
//   else if (yValue > 2000 && actuatorCounter[3] >= counterMin) {
//     digitalWrite(motorPins[6], LOW);
//     digitalWrite(motorPins[7], HIGH);
//       actuatorCounter[3]--;
//   }
//   //BRAKE
// if (actuatorCounter[3] >= counterMax || actuatorCounter[3] <= counterMin) {
//     //Stop the actuator if at limits
//     digitalWrite(motorPins[6], HIGH);
//     digitalWrite(motorPins[7], HIGH);  // Stop the motor
// }
// }

// void reverseMotors() {
//   digitalWrite(motorPins[0], LOW);
//   digitalWrite(motorPins[1], HIGH);
//   digitalWrite(motorPins[2], LOW);
//   digitalWrite(motorPins[3], HIGH);
//   digitalWrite(motorPins[4], LOW);
//   digitalWrite(motorPins[5], HIGH);
//   digitalWrite(motorPins[6], LOW);
//   digitalWrite(motorPins[7], HIGH);

//   // Decrement actuator counters
//   for (int i = 0; i < 4; i++) {
//     if (actuatorCounter[i] > 0) {
//       actuatorCounter[i]--;
//     }
//   }
// }

// void extendActuators() {
//   while (!allActuatorsAtMax()) {
//     for (int i = 0; i < 4; i++) {
//       if (actuatorCounter[i] < counterMax/2) {
//         digitalWrite(motorPins[i * 2], HIGH);
//         digitalWrite(motorPins[i * 2 + 1], LOW);
//         actuatorCounter[i]++;
//       } else {
//         digitalWrite(motorPins[i * 2], LOW);
//         digitalWrite(motorPins[i * 2 + 1], LOW);
//       }
//     }
//     delay(250); // Small delay to allow for motor updates
//   }
// }

// bool allActuatorsAtMax() {
//   for (int i = 0; i < 4; i++) {
//     if (actuatorCounter[i] < counterMax/2) {
//       return false;
//     }
//   }
//   return true;
// }
