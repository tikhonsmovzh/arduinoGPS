class Regulator {
    const int Speed = 125;
    const int PKoef = 1;
    const int DKoef = 1;

    int oldErr = 0;

  public:
    double Regulate(SphereCoords RegDirection) {
      SphereDirection dir = sphareMath.CountDirection(*navigation.GetCoord(), RegDirection);

      int err = (dir.GetAzimut() - navigation.GetAzimut()) * PKoef;

      err += (err - oldErr) * DKoef;

      motor.SetSpeeds(Speed - err, Speed + err);

      oldErr = err;

      return dir.GetDistance();
    }
};
