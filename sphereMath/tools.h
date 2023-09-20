class Tools {
  public:
    int Sign(int val) {
      if (val < 0) return -1;
      if (val == 0) return 0;
      return 1;
    }

    int ByteToInt(byte a, byte b)
    {
      int val = a << 8;
      return b | val;
    }

    void WriteInt(int val)
    {
      Serial2.write((byte)(val >> 8));
      Serial2.write((byte)val);
    }

    void WriteLong(long val) {
      Serial2.write((byte)(val >> 24));
      Serial2.write((byte)(val >> 16));
      Serial2.write((byte)(val >> 8));
      Serial2.write((byte)val);
    }

    const int SaveBaseData = 0;
};

Tools tools;
