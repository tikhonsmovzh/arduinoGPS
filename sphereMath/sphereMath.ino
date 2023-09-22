#include "include.h"

const int button = 2;

unsigned long millises = millis(), previusUpdate = 0;

const byte GetGPSP = 198;
const byte ZeroingCompassP = 1;
const byte saveP = 2;
const byte ManualStartP = 5;
const byte ManualStopP = 8;
const byte setMotorsP = 7;
const byte GetCompassDataP = 199;

bool prevButt = false;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(button, INPUT_PULLUP);

  Wire.begin();

  motor.Init();
  navigation.Init();

  motor.SetSpeeds(0, 0);
}

void loop() {
  millises = millis();

  if (previusUpdate < millises) {
    navigation.Update();

    router.Update();

    previusUpdate = millises + 50;
  }

  bool butt = !digitalRead(prevButt);

  if (butt && !prevButt) {
    router.Start();
    isStart = true;
  }

  prevButt = butt;

  if (Serial2.available() > 0)
  {
    byte buf[1];

    Serial2.readBytes(buf, 1);

    switch (buf[0]) {
      case GetGPSP: {
          tools.WriteLong(navigation.GetLongLat());
          tools.WriteLong(navigation.GetLongLong());
          tools.WriteInt(navigation.GetAzimut());

          break;
        }

      case GetCompassDataP: {
          for (int i = 0; i < 6; i++)
            Serial2.write(navigation.buf[i]);

          break;
        }

      case saveP:
        {
          byte bufer[8];
          Serial2.readBytes(bufer, 8);
          EEPROM.put(tools.SaveBaseData, bufer);

          navigation.SaveCompass();

          break;
        }

      case ZeroingCompassP:
        navigation.ZeroingCompass();
        break;

      case setMotorsP: {
          byte bufer[4];
          Serial2.readBytes(bufer, 4);

          if (isManual)
            motor.SetSpeeds(tools.ByteToInt(bufer[1], bufer[0]), tools.ByteToInt(bufer[3], bufer[2]));

          break;
        }

      case ManualStartP:
        isManual = true;
        break;

      case ManualStopP: {
          isManual = false;

          isStart = false;
          break;
        }
    }
  }
}
