#include "dVector.h"
#include <cmath>

dVector::dVector() {
	dX = 0.0;
	dY = 0.0;
}

dVector::~dVector() {

}

dVector::dVector(double dX, double dY) {
	this->dX = dX;
	this->dY = dY;
}

double dVector::length() {
	return sqrt(dX * dX + dY * dY);
}

dVector dVector::add(dVector dV) {
	dVector dV2 = dVector(dX + dV.dX, dY + dV.dY);
	return dV2;
}

dVector dVector::sub(dVector dV) {
	dVector dV2 = dVector(dX - dV.dX, dY - dV.dY);
	return dV2;
}

dVector dVector::scale(double factor) {
	dVector dV2 = dVector(dX * factor, dY * factor);
	return dV2;
}

dVector dVector::normalize() {
	dVector dV2 = dVector();

	double length = this->length();
	if (length != 0) {
		dV2.dX = dX / length;
		dV2.dY = dY / length;
	}

	return dV2;
}

double dVector::dotProduct(dVector dV) {
	return dX * dV.dX + dY * dV.dY;
}

std::string dVector::toString() {
	return "dVector(" + std::to_string(dX) + ", " + std::to_string(dX) + ")";
}
