class SphereCoordsLeg {
    SphereCoords *data;
  public:
    SphereCoordsLeg *Next;

    SphereCoordsLeg(double lactitude, double longtitude) {
      data = new SphereCoords(lactitude, longtitude);
    }

    SphereCoords *GetData() {
      return data;
    }
};

class DynamicStructure
{
    SphereCoordsLeg *first, *last;

    int structSize = 0;

  public:
    SphereCoordsLeg* Dequeue()
    {
      if (structSize <= 0)
        return NULL;

      structSize--;

      SphereCoordsLeg *saveFirst = first;

      if (first != NULL)
      {
        first = first->Next;

        if (first == NULL)
          last = NULL;
      }

      return saveFirst;
    }

    void Enqueu(SphereCoordsLeg *data)
    {
      structSize++;

      if (first == NULL)
      {
        first = data;
        last = data;

        return;
      }

      last->Next = data;

      last = data;
    }

    int GetSize() {
      return structSize;
    }

    void Clear()
    {
      first = NULL;
      last = NULL;
    }
};
