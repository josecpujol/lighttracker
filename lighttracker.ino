#include <Servo.h>
 
struct ServoControl {
  int pin;  // Where the input voltage is
  int error = 0;
  int acum_error = 0;
  int pos;  // servo position
  int min_pos;
  int max_pos;
  int offset = 0;  // To bias the position
  int sign = 1;  // indicates if we sum (1) or substract (-1) the update to the current position (hardware dependant)
  String myname;
};

Servo myservo1;
Servo myservo2;   

ServoControl control1;
ServoControl control2;

void setup() {
  control1.pin = A1;
  control1.pos = 90;
  control1.min_pos = 45;
  control1.max_pos = 145;
  control1.sign = -1;
  control1.myname = "Control1";

  control2.pin = A0;
  control2.pos = 120;
  control2.min_pos = 90;
  control2.max_pos = 145;
  control2.offset = 70;
  control2.myname = "Control2";

  myservo1.attach(9);  
  myservo2.attach(10);
  myservo1.write(control1.pos); 
  myservo2.write(control2.pos);
  
  delay(200);
  Serial.begin(9600);
}

float k = 0.1;
float ki = 0.001;

void loop()
{
  readInput(&control1);
  readInput(&control2);

  computeNewPosition(&control1);
  computeNewPosition(&control2);
 
  myservo1.write(control1.pos);
  myservo2.write(control2.pos);
  
  // printState(&control1);
  // printState(&control2);
  delay(50);
}

void readInput(struct ServoControl* control) {
  control->error = analogRead(control->pin) - 512 + control->offset;
}

void computeNewPosition(struct ServoControl* control) {
  control->acum_error += control->error;  // integral part
  int pos_update = k * control->error + ki * control->acum_error;
  control->pos += (control->sign * pos_update);
  control->pos = constrain(control->pos, control->min_pos, control->max_pos);  // clamp the position
}

void printState(struct ServoControl* control) {
  String toprint = "";
  toprint += control->myname;
  toprint += ", error: ";
  toprint += control->error;
  toprint += ", pos: ";
  toprint += control->pos;
  Serial.println(toprint);
 }

