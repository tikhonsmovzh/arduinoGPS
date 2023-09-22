class Router {
    DynamicStructure *route;

    SphereCoords *targetCoord;

    Regulator regulator;

    const double sensitive = 1;

  public:
    void Start() {
      route = new DynamicStructure();

      route->Enqueu(new SphereCoordsLeg(50, 50));

      targetCoord = route->Dequeue()->GetData();
    }

    void Update() {
      if (isManual || targetCoord == NULL || !isStart)
        return;

      if (regulator.Regulate(*targetCoord) < sensitive) {
        if (route->GetSize() > 0) {
          delete targetCoord;

          targetCoord = route->Dequeue()->GetData();
        } else {
          targetCoord = NULL;
          motor.SetSpeeds(0, 0);
        }
      }
    }
};

Router router;
