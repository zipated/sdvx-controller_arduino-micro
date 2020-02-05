#include <Joystick.h>
#include <Encoder.h>

const int keylist[] =
{
  18,
  11, 13, 23, 21,
  12, 22,
  7, 6,
};
const int Keys = sizeof(keylist) / sizeof(keylist[0]);

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  Keys, 0,
  true, true, false,
  false, false, false,
  false, false,
  false, false, false
);

Encoder encoder1(10, 4);
Encoder encoder2(20, 19);


void setup() {
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i], INPUT_PULLUP);
  }
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Joystick.setXAxisRange(-64, 63);
  Joystick.setYAxisRange(-64, 63);
  Joystick.begin();
}
boolean lastStatus[Keys];
int o_ec1 = encoder1.read();
int o_ec2 = encoder2.read();


void loop() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  for (int i = 0; i < Keys; i++) {
    boolean Status = !digitalRead(keylist[i]);
    if (Status != lastStatus[i]) {
      Joystick.setButton(i, Status);
      lastStatus[i] = Status;
    }
  }
  int ec1 = encoder1.read();
  if (ec1 != o_ec1) {
        if (ec1 > 63) {
          ec1 -= 128;
          encoder1.write(ec1);
        } else if (ec1 < -64) {
          ec1 += 128;
          encoder1.write(ec1);
        }
    Joystick.setXAxis(ec1);
    o_ec1 = ec1;
  }

  int ec2 = encoder2.read();
  if (ec2 != o_ec2) {
    if (ec2 > 63) {
      ec2 -= 128;
      encoder2.write(ec2);
    } else if (ec2 < -64) {
      ec2 += 128;
      encoder2.write(ec2);
    }
    Joystick.setYAxis(ec2);
    o_ec2 = ec2;
  }
}
