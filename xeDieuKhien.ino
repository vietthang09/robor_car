#include <Servo.h>

Servo servoFront;
Servo servoHight;
Servo servo;
Servo servoDrag;

const int motorA1  = 7;    // Pin  6 of L298.
const int motorA2  = 8;    // Pin  7 of L298.
const int motorB1  = 12;   // Pin 9 of L298.
const int motorB2  = 13;   // Pin 10 of L298.

const int buzzer = 12 ;

const int BTState = 2;

int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;
char state;

// servo tới lui
int posHight = 90;
int openHight = 100;
int closeHight = 90;

// servo lên xuống
int posServo = 106;
int posServoLevel1 = 82;
int posServoLevel2 = 110;
int posServoLevel3 = 121;
int posServoLevel4 = 136;

// servo đóng mở cánh tay
int posFront = 100;
int openFront = 140;
int closeFront = 100;

int posDrag = 10;
int posDragClose = 0;
int posDragOpen = 90;


void setup() {
  Serial.begin(9600);

  pinMode(motorA1, OUTPUT); // bánh phải đi lui
  pinMode(motorA2, OUTPUT); // bánh phải đi tới
  pinMode(motorB1, OUTPUT); // bánh trái đi lui
  pinMode(motorB2, OUTPUT); // bánh trái đi lui
  pinMode(buzzer, OUTPUT);
  pinMode(BTState, INPUT);

  servoHight.attach(A5);
  servoFront.attach(A4);
  servo.attach(A3);
  servoDrag.attach(A2);
  
}

void loop() {

  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }


  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }

  if (state != 'S') {
    Serial.print(state);
  }


 if (state == 'F') { // đi thẳng
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed+10);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }

    else if (state == 'I') {  // đi thẳng rẽ phải
    analogWrite(motorA1, 0); 
    analogWrite(motorA2, 75);
    analogWrite(motorB1, 0);    
    analogWrite(motorB2, 150);
    delay(20);
    state = 'F';
  }

    else if (state == 'G') {   // đi thẳng rẽ trái
    analogWrite(motorA1, 0); 
    analogWrite(motorA2, 150);
    analogWrite(motorB1, 0);    
    analogWrite(motorB2, 75);
    delay(20);
    state = 'F';
  }

  else if (state == 'B') {  // đi lùi
    analogWrite(motorA1, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
    analogWrite(motorA2, 0);
  }

   else if (state == 'H') {  // đi lùi rẽ trái
    analogWrite(motorA1, 150);   
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 75); 
    analogWrite(motorB2, 0);
  }
  
  else if (state == 'J') {  // đi lùi rẽ phải
    analogWrite(motorA1, 75);   
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 150);   
    analogWrite(motorB2, 0);
  }

  else if (state == 'L') {   // rẽ trái
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }
  else if (state == 'R') {   // rẽ phải
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }
  else if (state == 'S') {   
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }
  // icon đầu tiên, dong mo canh tay, keo
  else if (state == 'W') {
    if (posFront < openFront) {
      while (posFront < openFront) {
        posFront += 5;
        delay(15);
        servoFront.write(posFront);
      }
    }
    
    if (posDrag < 90) {
      while (posDrag < 90) {
        posDrag += 5;
        delay(15);
        servoDrag.write(posDrag);
      }
    } }
  else if (state == 'w') {
    if (posFront > closeFront) {
      while (posFront > closeFront) {
        posFront -= 5;
        delay(15);
        servoFront.write(posFront);
      }
    }
    
    if (posDrag > 0) {
      while (posDrag > 0) {
        posDrag -= 5;
        delay(15);
        servoDrag.write(posDrag);
      }
    }
  }
  // icon thứ 2, dua xuong level 1
  else if (state == 'U') {
    if (posServo > posServoLevel1 && posServo < posServoLevel3) {
      while (posServo > posServoLevel1) {
        posServo -= 1;
        delay(8);
        servo.write(posServo);
      }
    }
  }
  else if (state == 'u') {
    if (posServo < posServoLevel2) {
      while (posServo < posServoLevel2) {
        posServo += 1;
        delay(8);
        servo.write(posServo);
      }
    }
  }
  // icon thứ 3, đưa từ tầng 2 lên tầng 3
  else if (state == 'V') {
    if (posServo < posServoLevel3 && posServo > posServoLevel1) {
      while (posServo < posServoLevel3) {
        posServo += 5;
        delay(35);
        servo.write(posServo);
      }
    }
    
  }
  else if (state == 'v') {
    
    if (posServo > posServoLevel2) {
      while (posServo > posServoLevel2) {
        posServo -= 1;
        delay(8);
        servo.write(posServo);
      }
    }
    
  }
  // icon thử 4, đưa từ tầng 2 len tang 4
  else if (state == 'X') {
    if(posServo > posServoLevel1 && posServo < posServoLevel3){
      while (posServo < posServoLevel4) {
        posServo += 1;
        delay(8);
        servo.write(posServo);
      }
    }   
    
  }
  else if (state == 'x') {
    
    if(posServo > posServoLevel2){
      while (posServo > posServoLevel2) {
        posServo -= 1;
        delay(8);
        servo.write(posServo);
      }
    }
    
  }


}
