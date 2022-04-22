int trig1 = A0;
int echo1 = A1;
int trig2 = A2;
int echo2 = A3;
int trig3 = A4;
int echo3 = A5;

int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int ENA = 3;
int ENB = 11;
int khoang_cach_trai = 0, khoang_cach_phai = 0, khoang_cach_giua = 0;
long pingTime, distance;
float speedSound = 0.0343;
int DIS = 16;
int ADD_DIS_RIGHT = 0;
int ADD_DIS_LEFT = 5;
int ADD_DIS_FRONT = 19;

long line_trai()
{
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig1, LOW);
  pingTime = pulseIn(echo1, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

long line_giua()
{
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2, LOW);
  pingTime = pulseIn(echo2, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

long line_phai()
{
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig3, LOW);
  pingTime = pulseIn(echo3, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

void setup()
{
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  moveStop();
}

void loop()
{
  khoang_cach_trai = line_trai();
  khoang_cach_giua = line_giua();
  khoang_cach_phai = line_phai();
  if (khoang_cach_trai < DIS + ADD_DIS_LEFT && khoang_cach_giua > DIS && khoang_cach_phai > DIS)
  {
    turnRight();
  }
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS + ADD_DIS_FRONT && khoang_cach_phai > DIS)
  {
    if (khoang_cach_trai > khoang_cach_phai + 3)
    {
      turnLeft();
    }
    if (khoang_cach_trai < khoang_cach_phai + 3)
    {
      turnRight();
    }
    if (khoang_cach_trai == khoang_cach_phai) {
      turnRight();
    }
  }

  else if (khoang_cach_trai > DIS && khoang_cach_giua > DIS && khoang_cach_phai < DIS + ADD_DIS_RIGHT)
  {
    turnLeft();
  }
  else if (khoang_cach_trai < DIS + ADD_DIS_LEFT && khoang_cach_giua < DIS + ADD_DIS_FRONT && khoang_cach_phai > DIS)
  {
    turnRight();
  }
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS + ADD_DIS_FRONT && khoang_cach_phai < DIS + ADD_DIS_RIGHT)
  {
    turnLeft();
  }
  else if (khoang_cach_trai < DIS + ADD_DIS_LEFT && khoang_cach_giua > DIS && khoang_cach_phai < DIS)
  {
    if (khoang_cach_phai < 4)
    {
      turnLeft();
    }
    if (khoang_cach_trai < 7)
    {
      turnRight();
    }
    if (khoang_cach_trai == khoang_cach_phai) {
      turnRight();
    }
  }
  else if (khoang_cach_trai < DIS && khoang_cach_giua < DIS && khoang_cach_phai < DIS)
  {
    moveBackward();
    turnLeft();
  }
  else
  {
    moveForward();
  }
}

void moveForward()
{
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward()
{ 
  analogWrite(ENA, 90);
  analogWrite(ENB, 90);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight()
{
  analogWrite(ENA, 70);
  analogWrite(ENB, 70);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft()
{
  analogWrite(ENA, 70);
  analogWrite(ENB, 70);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveStop()
{
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
