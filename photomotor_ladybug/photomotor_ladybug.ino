/*
Adafruit Arduino - Lesson 13. DC Motor
*/
#define MOT_A1_PIN 5
#define MOT_A2_PIN 6
#define MOT_B1_PIN 9
#define MOT_B2_PIN 10

int photocellPinA = 0;     // the cell and 10K pulldown are connected to a0
int photocellPinB = 1;  
int photocellReadingA;     // the analog reading from the analog resistor divider
int photocellReadingB;  
int roomLight;
int lightThreshold;
int speedF1 = 0;
int speedF2 = 0;
int D1 = 0;
int D2 = 0; 
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int T1 = 0;
int T2 = 0; 

void setup() 
{ 
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);

   // Start with drivers off, motors coasting.
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);
  
  pinMode(photocellPinA, INPUT);
  pinMode(photocellPinB, INPUT);
  
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
  photocellReadingA = analogRead(photocellPinA);  
  photocellReadingB = analogRead(photocellPinB);  
  roomLight = (photocellReadingA + photocellReadingB)/2;
} 
 
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}

// ================================================================================
/// Set the current on both motors.
///
/// \param pwm_A  motor A PWM, -255 to 255
/// \param pwm_B  motor B PWM, -255 to 255

void set_motor_currents(int pwm_A, int pwm_B)
{
  set_motor_pwm(pwm_A, MOT_A1_PIN, MOT_A2_PIN);
  set_motor_pwm(pwm_B, MOT_B1_PIN, MOT_B2_PIN);

  // Print a status message to the console.
  Serial.print("Set motor A PWM = ");
  Serial.print(pwm_A);
  Serial.print(" motor B PWM = ");
  Serial.println(pwm_B);
}

// ================================================================================
/// Simple primitive for the motion sequence to set a speed and wait for an interval.
///
/// \param pwm_A  motor A PWM, -255 to 255
/// \param pwm_B  motor B PWM, -255 to 255
/// \param duration delay in milliseconds

void spin_and_wait(int pwm_A, int pwm_B, int duration)
{
  set_motor_currents(pwm_A, pwm_B);
  delay(duration);
}


void loop() 
{ 
  photocellReadingA = analogRead(photocellPinA);  
  photocellReadingB = analogRead(photocellPinB);  
  lightThreshold = roomLight + 14;
  
  Serial.print("Analog reading = ");
  Serial.print(photocellReadingA);     // the raw analog reading
  // We'll have a few threshholds, qualitatively determined
  if (photocellReadingA < 10) {
    Serial.println(" - Dark");
  } else if (photocellReadingA < 200) {
    Serial.println(" - Dim");
  } else if (photocellReadingA < 500) {
    Serial.println(" - Light");
  } else if (photocellReadingA < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  Serial.print("Analog reading = ");
  Serial.print(photocellReadingB);     // the raw analog reading
  // We'll have a few threshholds, qualitatively determined
  if (photocellReadingB < 10) {
    Serial.println(" - Dark");
  } else if (photocellReadingB < 200) {
    Serial.println(" - Dim");
  } else if (photocellReadingB < 500) {
    Serial.println(" - Light");
  } else if (photocellReadingB < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  D1 = photocellReadingA-photocellReadingB;
  D2 = photocellReadingB-photocellReadingA;

  T1 = photocellReadingA-roomLight;
  T2 = photocellReadingB-roomLight;
   
  if (D1 > 25){
     speedF1 = 200;
     speedF2 = 240;
     counter1++;
  } else if (D2 > 25) {
     speedF1 = 240;
     speedF2 = 200;
     counter2++;
  }else if (T1 > 15 && T2 > 15)  {
     if (counter3 > 3){
      speedF1 = 200;
      speedF2 =  200;
     }else {
      speedF1 = 200;
      speedF2 = 200;
      counter3++;
     }
  } else {
     speedF1 = 0;
     speedF2 = 0;
  }
  spin_and_wait(-speedF1, speedF2, 2000);
  //spin_and_wait(speedF1, speedF2, 2000);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
   spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(0, 0, 150);
  spin_and_wait(-255, 255, 150);
  spin_and_wait(255, -255, 2000);
  //spin_and_wait(0, 255, 60);
  //spin_and_wait(255, 0, 60);
  //spin_and_wait(0, 255, 60);
  //spin_and_wait(255, 0, 60);
  //spin_and_wait(0, 255, 2000);
  Serial.print("Motor Speed = ");
  Serial.print(speedF1);             
  Serial.print(" ");
  Serial.print(speedF2);   
  Serial.print(" ");
  Serial.print(D1);   
  Serial.print(" ");
  Serial.print(D2);  
  Serial.print(" ");
  Serial.print(T1);  
  Serial.print(" ");
  Serial.print(T2);  
  Serial.println(" ");
  Serial.print(counter1); 
  Serial.print(" ");
  Serial.print(counter2); 
  Serial.print(" ");
  Serial.print(counter3); 
  Serial.println(" ");
  Serial.print(roomLight); 
  Serial.print(" ");
  Serial.print(photocellReadingA); 
  Serial.print(" ");
  Serial.print(photocellReadingB); 
  Serial.println(" ");

  if (counter1 > 1 || counter2 > 1 || counter3 > 5){
     D1 = 0;
     D2 = 0;
     T1 = 0;
     T2 = 0;
     counter1 = 0;
     counter2 = 0;
     counter3 = 0;
  }
  delay(100);
} 
