class Motor {
    const int shimMotorRight = 5;
    const int powerMotorRight1 = 22;
    const int powerMotorRight2 = 23;

    const int shimMotorLeft = 6;
    const int powerMotorLeft1 = 25;
    const int powerMotorLeft2 = 24;

  public:
    void Init()
    {
      pinMode(shimMotorRight, OUTPUT);
      pinMode(powerMotorRight1, OUTPUT);
      pinMode(powerMotorRight2, OUTPUT);

      digitalWrite(powerMotorRight1, HIGH);
      digitalWrite(powerMotorRight2, LOW);

      analogWrite(shimMotorRight, 0);

      pinMode(shimMotorLeft, OUTPUT);
      pinMode(powerMotorLeft1, OUTPUT);
      pinMode(powerMotorLeft2, OUTPUT);

      digitalWrite(powerMotorLeft1, HIGH);
      digitalWrite(powerMotorLeft2, LOW);

      analogWrite(shimMotorLeft, 0);
    }

    void SetSpeedRight(int speeds)
    {
      if (speeds <= 0)
      {
        digitalWrite(powerMotorRight1, HIGH);
        digitalWrite(powerMotorRight2, LOW);

        analogWrite(shimMotorRight, -speeds);
      }
      else
      {
        digitalWrite(powerMotorRight1, LOW);
        digitalWrite(powerMotorRight2, HIGH);

        analogWrite(shimMotorRight, speeds);
      }
    }

    void SetSpeeds(int speedsLeft, int speedsRight) {
      SetSpeedLeft(speedsLeft);
      SetSpeedRight(speedsRight);
    }

    void SetSpeedLeft(int speeds)
    {
      if (speeds <= 0)
      {
        digitalWrite(powerMotorLeft1, HIGH);
        digitalWrite(powerMotorLeft2, LOW);

        analogWrite(shimMotorLeft, -speeds);
      }
      else
      {
        digitalWrite(powerMotorLeft1, LOW);
        digitalWrite(powerMotorLeft2, HIGH);

        analogWrite(shimMotorLeft, speeds);
      }
    }
};

Motor motor;
