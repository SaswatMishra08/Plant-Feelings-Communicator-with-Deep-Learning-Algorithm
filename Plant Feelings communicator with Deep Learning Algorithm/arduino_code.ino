#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo0;
int cur[] = { 90, 90, 90, 90, 90, 90, 90 };
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo0.attach(3);
  myservo1.attach(4);
  myservo2.attach(5);
  myservo3.attach(6);
  myservo4.attach(7);
  myservo5.attach(8);
}

void loop() {

  int autom = digitalRead(9);
  int manual = digitalRead(10);

  if (autom == 1) {
    if (Serial.available() > 0) {         // Check if data is available to read
      char receivedChar = Serial.read();  // Read the incoming byte

      if (receivedChar == '1') {  // Check the received character
        delay(1000);
        armdown();
        delay(1000);
        armup();
        delay(1000);
      } 
      
    }

    
  }
  if (manual == 1) {
    delay(1000);
    armdown();
    delay(1000);
    armup();
    delay(1000);
  }
}
void armdown() {
  myservo0.write(120);
  delay(1000);
  move(myservo1, cur[1], 50, 1);
  delay(1000);
  move(myservo3, cur[3], 0, 3);
  delay(1000);
  move(myservo4, cur[4], 140, 4);
  delay(1000);
  myservo0.write(0);
  delay(1000);
}
void armup() {


  move(myservo4, cur[4], 90, 4);
  delay(1000);
  move(myservo3, cur[3], 90, 3);
  delay(1000);
  move(myservo1, cur[1], 180, 1);
  delay(1000);
  myservo0.write(120);
  delay(1000);
}

void move(Servo sm, int from, int to, int pos) {
  if (from < to) {
    for (int i = from; i <= to; i += 5) {
      sm.write(i);
      cur[pos] = i;
      delay(100);
    }
  }
  if (from > to) {
    for (int i = from; i >= to; i -= 5) {
      sm.write(i);
      cur[pos] = i;
      delay(100);
    }
  }
}
