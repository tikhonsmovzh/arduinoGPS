#include "include.h"

const int button = 2;

unsigned long millises = millis(), previusUpdate = 0;

const byte GetGPSP = 198;
const byte CompasParameters = 199;
const byte ZeroingCompassP = 1;
const byte saveP = 2;
const byte StopManualP = 8;
const byte SetMotorsP = 7;
const byte StartManualP = 5;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  Wire.begin();

  motor.Init();
  navigation.Init();

  motor.SetSpeeds(0, 0);
}

void loop() {
  millises = millis();

  if (previusUpdate < millises) {
    navigation.Update();

    previusUpdate = millises + 50;
  }

  if (Serial2.available() > 0) {
    byte buf[1];

    Serial2.readBytes(buf, 1);

    switch (buf[0]) {
      case GetGPSP:
        {
          tools.WriteLong(navigation.GetLongLat());
          tools.WriteLong(navigation.GetLongLong());
          tools.WriteInt(navigation.GetAzimut());

          break;
        }

      case CompasParameters:
        for (int i = 0; i < 6; i++)
          Serial2.write(navigation.buf[i]);
        break;

      case SetMotorsP:
        {
          byte bufer[4];
          Serial2.readBytes(bufer, 4);

          if (!isAuto)
            motor.SetSpeeds(tools.ByteToInt(bufer[1], bufer[0]), tools.ByteToInt(bufer[3], bufer[2]));

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

      case StartManualP:
        {
          isAuto = false;
          break;
        }

      case StopManualP:
        {
          if (isStart)
            isAuto = true;

          break;
        }

      default:
        break;
    }
  }
}
