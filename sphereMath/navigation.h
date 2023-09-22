class Navigation {
    const int addr = 0x1E;

    int maxX = 1, minX = 1, maxY = 1, minY = 1, centerX = 1, centerY = 1, north = 0, compass;

    TinyGPS gps;

    bool isGPSOpen = false;

    double latitude = 0, logatutde = 0;
    SphereCoords *coord;
    long longLatitude = 0, longLogatutde = 0;

    int GetCompaseValue()
    {
      Wire.beginTransmission(addr);
      Wire.write(0x03);
      Wire.endTransmission();

      Wire.requestFrom(addr, 6);

      for (int i = 0; i < 6; i++)
        buf[i] = Wire.read();

      int xC = tools.ByteToInt(buf[0], buf[1]);
      int yC = tools.ByteToInt(buf[4], buf[5]);

      int g = (int)(atan2(yC, xC) * 180 / PI) + 180 - north;

      if (g < 0)
        g += 360;

      return g;
    }

    void InitCompass()
    {
      EEPROM.get(tools.SaveBaseData, maxX);
      EEPROM.get(tools.SaveBaseData + 2, minX);
      EEPROM.get(tools.SaveBaseData + 4, maxY);
      EEPROM.get(tools.SaveBaseData + 6, minY);

      centerX = (maxX + minX) / 2;
      centerY = (maxY + minY) / 2;
    }

    bool readgps()
    {
      while (Serial1.available())
      {
        int b = Serial1.read();
        if ('\r' != b)
        {
          if (gps.encode(b))
            return true;
        }
      }
      return false;
    }

  public:
    byte buf[6];

    void Init() {
      Wire.beginTransmission(addr);
      Wire.write(0x00);
      Wire.write(0x70);
      Wire.write(0xA0);
      Wire.write(0x00);
      Wire.endTransmission();

      EEPROM.get(tools.SaveBaseData + 8, north);

      InitCompass();
    }

    void Update() {
      isGPSOpen = readgps();

      if (isGPSOpen)
      {
        long lat, lon;

        gps.get_position(&lat, &lon);

        if (coord != NULL)
          delete coord;

        coord = new SphereCoords((double)lat / (double)1000000, (double)lon / (double)1000000);

        longLatitude = lat;
        longLogatutde = lon;
      }

      compass = GetCompaseValue();
    }

    void ZeroingCompass()
    {
      north = (compass + north) % 360;

      EEPROM.put(tools.SaveBaseData + 8, north);
    }

    void SaveCompass()
    {
      InitCompass();
    }

    bool GetGPSOpened() {
      return isGPSOpen;
    }

    double GetLongLat() {
      return longLatitude;
    }

    SphereCoords *GetCoord() {
      return coord;
    }

    long GetLongLong() {
      return longLogatutde;
    }

    int GetAzimut() {
      return compass;
    }
};

Navigation navigation;
