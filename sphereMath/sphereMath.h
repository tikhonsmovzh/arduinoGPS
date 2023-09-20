class SphereCoords {
	double _lactitude, _longtitude, _radLactitude, _radLongtitude;
public:
	SphereCoords(double lactitude, double longtitude, bool isRad = false)
	{
		if (isRad) {
			_lactitude = lactitude * 180 / PI;
			_longtitude = longtitude * 180 / PI;

			_radLactitude = lactitude;
			_radLongtitude = longtitude;

			return;
		}

		_lactitude = lactitude;
		_longtitude = longtitude;

		_radLactitude = lactitude * PI / 180;
		_radLongtitude = longtitude * PI / 180;
	}

	double GetLactitude() {
		return _lactitude;
	}

	double GetLongtitude() {
		return _longtitude;
	}

	double GetRadLactitude() {
		return _radLactitude;
	}

  double GetRadLongtitude() {
		return _radLongtitude;
	}
};

class SphereDirection {
	double _azimut, _distance;

public:
	SphereDirection(double azimut, double distance)
	{
		_azimut = azimut;
		_distance = distance;
	}

	double GetAzimut() {
		return _azimut;
	}

	double GetDistance() {
		return _distance;
	}
};

class SphereMath 
{
  const double _earthRadius = 6372795;
  
	double square(double val) {
		return val * val;
	}

public:
	SphereDirection CountDirection(SphereCoords coords1, SphereCoords coords2) {
		double radLatitude1 = coords1.GetRadLactitude(), radLatitude2 = coords2.GetRadLactitude();

		double cosLatitude1 = cos(radLatitude1), cosLatitude2 = cos(radLatitude2),
			sinlLatitude1 = sin(radLatitude1), sinLatitude2 = sin(radLatitude2);

		double delta = coords1.GetRadLongtitude() - coords2.GetRadLongtitude(), cosDelta = cos(delta), sinDelta = sin(delta);

		double distance = atan2(sqrt(square(cosLatitude2 * sinDelta) + square(cosLatitude1 * sinLatitude2 - sinlLatitude1 * cosLatitude2 * cosDelta)),
			sinlLatitude1 * sinLatitude2 + cosLatitude1 * cosLatitude2 * cosDelta) * _earthRadius;

		double x = cosLatitude1 * sinLatitude2 - sinlLatitude1 * cosLatitude2 * cosDelta, angle = atan2(-(sinDelta * cosLatitude2), x) * 180 / PI;

		angle = angle - (360 * floor(angle / 360));

		return SphereDirection(angle, distance);
	}

	SphereCoords CountVector(SphereCoords coords, double dist, double azimut) {
		double delta = dist / _earthRadius, sinDelta = sin(delta);

		double cosLactitude = cos(coords.GetRadLactitude()), sinLactitude = sin(coords.GetRadLactitude());

		double radAzimut = azimut * PI / 180, sinAzimut = sin(radAzimut), cosAzimut = cos(radAzimut);

    double finalCoordsLactitudeRad = asin(cos(delta) * sinLactitude + sinDelta * cosLactitude * cosAzimut);

		return SphereCoords(finalCoordsLactitudeRad,
     asin(sinDelta * sinAzimut / cos(finalCoordsLactitudeRad)) + coords.GetRadLongtitude(), true);
	}
};

SphereMath sphareMath;
