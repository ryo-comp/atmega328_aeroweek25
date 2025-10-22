#include <Servo.h>
Servo servo;
const int pinoJoystick = A0;
const int pinoServo = 9;
void setup()
{
    servo.attach(pinoServo);
}
void loop()
{
    int leituraJoystick = analogRead(pinoJoystick);
    int angulo = map(leituraJoystick, 0, 1023, 0, 180);
    servo.write(180 - angulo);
    delay(15);
}
