#ifndef OMATH_H
#define OMATH_H

#define _USE_MATH_DEFINES

#include <cmath>

class OMath {
public:
	static const double pi;
	static const double pitwo;
	static const double twopi;
	static const double deg2rad;
	static const double rad2deg;
};

const double OMath::pi = 3.1415926536;
const double OMath::pitwo = 0.5 * OMath::pi;
const double OMath::twopi = 2 * OMath::pi;
const double OMath::deg2rad = OMath::pi / 180;
const double OMath::rad2deg = 180 / OMath::pi;

#endif