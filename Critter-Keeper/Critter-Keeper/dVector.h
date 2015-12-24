#pragma once
#include <string>

class dVector {
	private:
		//double dX, dY;

	public:
		double dX, dY;

		dVector();
		dVector(double dX, double dY);

		double length();
		dVector add(dVector dV);
		dVector sub(dVector dV);
		dVector scale(double factor);
		dVector normalize();
		double dotProduct(dVector dV);
		std::string toString();
};

