#include <Arduino.h>

#define MIN_COUNT1 20
#define MIN_COUNT2 20
#define STEPS_PER_ROTATION 8000
#define CLOCK_PERIOD 125 // 125 nanoseconds or 8MHz

void setup(void) {
  Serial.begin(115200);

  // Pin 9 used as output for PWM
  pinMode(9, OUTPUT);
  
  // Pin 2 used as output for direction control
  pinMode(2, OUTPUT);

  // Timer setup: Fast PWM mode, no prescaler
  TCCR1A = (1<<COM1A0);           // Toggle OC1A on compare match
  TCCR1B = (1<<WGM12) | (1<<CS10); // CTC mode, no prescaling (CS10 = 1)
  OCR1A = 10;                      // Initial OCR1A value to generate a pulse
}

void loop(void) {
  if (Serial.available() >= 4) { 
    uint8_t buffer[4]; 
    Serial.readBytes((char*)buffer, 4); 

    float rps; 
    memcpy(&rps, buffer, 4); // Convert bytes to float
    
    Serial.print("RECEIVED FLOAT: "); 
    Serial.println(rps, 10);

    bool direction = rps < 0;
    rps = abs(rps);
    
    // Epsilon check for very small values of rps
    float epsilon = 1e-6f;
    if (rps < epsilon) {
      // Stop the timer if rps is near zero
      TCCR1B &= ~(1<<CS10);  // Disable the clock (no prescaling)
      digitalWrite(9, LOW);   // Optionally, turn off pin 9 (if it's being used for something else)
      digitalWrite(2, LOW);   // Optionally, stop the direction signal on pin 2
      Serial.println("Timer stopped (rps is zero).");
      return; // No need to do further calculations
    }
    
    // Calculate period P (seconds per step pulse)
    float P = 1.0 / (rps * STEPS_PER_ROTATION); 

    // Calculate the timer value N to generate the desired pulse rate
    int N = int(round(P / (1.0 * CLOCK_PERIOD * pow(10, -9)))); // Convert to timer ticks
    
    // Ensure N is within bounds
    if (N > 65535) {
      N = 65535; // Max value for 16-bit timer register
    }

    Serial.print("Calculated N: ");
    Serial.println(N);

    // Set the direction based on the sign of rps
    if (direction) {
      digitalWrite(2, LOW); // Set LOW for one direction
    } else {
      digitalWrite(2, HIGH); // Set HIGH for the opposite direction
    }

    // Set the OCR1A register to control the frequency of the pulse
    OCR1A = N;
    
    // Restart the timer if it was stopped
    if (rps > epsilon) {
      TCCR1B |= (1<<CS10); // Restart the timer with no prescaling
      digitalWrite(9, HIGH); // Optionally, turn on pin 9
    }
  }
}


// #include <Arduino.h>

// #define MIN_COUNT1 20
// #define MIN_COUNT2 20
// #define STEPS_PER_ROTATION 8000
// #define CLOCK_PERIOD 125 // 125 nanoseconds or 8MHz

// void setup(void) {
//   Serial.begin(115200);
  
//   // Pin 9 used as output
//   pinMode(9, OUTPUT);

//   // Timer setup: Fast PWM mode, no prescaler
//   TCCR1A = (1<<COM1A0);           // Toggle OC1A on compare match
//   TCCR1B = (1<<WGM12) | (1<<CS10); // CTC mode, no prescaling (CS10 = 1)
//   OCR1A = 10;                      // Initial OCR1A value to generate a pulse
// }

// void loop(void) {
//   if (Serial.available() >= 4) { 
//     uint8_t buffer[4]; 
//     Serial.readBytes((char*)buffer, 4); 

//     float rps; 
//     memcpy(&rps, buffer, 4); // Convert bytes to float
    
//     Serial.print("RECEIVED FLOAT: "); 
//     Serial.println(rps, 10);

//     bool direction = rps < 0;
//     rps = abs(rps);
    
//     // Epsilon check for very small values of rps
//     float epsilon = 1e-6f;
//     if (rps < epsilon) {
//       // Stop the timer if rps is near zero
//       TCCR1B &= ~(1<<CS10);  // Disable the clock (no prescaling)
//       digitalWrite(9, LOW);   // Optionally, turn off pin 9 (if it's being used for something else)
//       Serial.println("Timer stopped (rps is zero).");
//       return; // No need to do further calculations
//     }
    
//     // Calculate period P (seconds per step pulse)
//     float P = 1.0 / (rps * STEPS_PER_ROTATION); 

//     // Calculate the timer value N to generate the desired pulse rate
//     int N = int(round(P / (1.0 * CLOCK_PERIOD * pow(10, -9)))); // Convert to timer ticks
    
//     // Ensure N is within bounds
//     if (N > 65535) {
//       N = 65535; // Max value for 16-bit timer register
//     }

//     Serial.print("Calculated N: ");
//     Serial.println(N);
    
//     // Change the direction
//     use digital write

//     // Set the OCR1A register to control the frequency of the pulse
//     OCR1A = N;
    
//     // Restart the timer if it was stopped
//     if (rps > epsilon) {
//       TCCR1B |= (1<<CS10); // Restart the timer with no prescaling
//       digitalWrite(9, HIGH); // Optionally, turn on pin 9
//     }
//   }
// }

// #include <Arduino.h> 

// #define MIN_COUNT1 20 

// #define MIN_COUNT2 20 

 

// #define STEPS_PER_ROTATION 8000 

 

// #define CLOCK_PERIOD 125 // 125 nanoseconds or 8MHz 
 

// void setup(void) 
// { 

//   Serial.begin(115200); 

//   // pinMode(LED_BUILTIN, OUTPUT); 

//   pinMode(9, OUTPUT); 

//   TCCR1A = (1<<COM1A0); 

//   TCCR1B = (1<<WGM12) | (1<<CS10); 

//   OCR1A = 10; 

// } 

// void loop(void) 

// { 
//   if (Serial.available() >= 4) { 
//   uint8_t buffer[4]; 
//   Serial.readBytes((char*)buffer, 4); 

//   float rps; 
//   memcpy(&rps, buffer, 4);  
//   Serial.print("RECEIVED FLOAT: "); 
//   Serial.println(rps, 10);  
  
//   bool direction = rps < 0;
//   rps = abs(rps);
  
//   float epsilon = 1e-6f;
//   if (rps < epsilon)
//   {
//      // We need to turn off the hardware clock
//   }

//   float P = 1.0 / (rps * STEPS_PER_ROTATION); 

//   int N = int(round(P / (1.0*CLOCK_PERIOD * pow(10, -9)))); 

//   Serial.println(N); 

//   OCR1A = N; 

//   } 

// } 