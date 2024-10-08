#pragma once
#include <string>

class Vec2
{
public:
	double x, y;

	Vec2(double x, double y);
	Vec2();

	void add(Vec2); // essentially +=
	void sub(Vec2); // -=
	void mul(int); // *=
	void mul(double); // *= f
	double dot(Vec2);
	double mag();
	double mag2();
	Vec2 getPerp();
	Vec2 getUnit();
	Vec2 getProjectionOn(Vec2);
	

	void operator+=(Vec2);
	void operator-=(Vec2);
	void operator*=(int);
	void operator*=(double);
	double operator*(Vec2); //dot product operator
	Vec2 operator+(Vec2); //addition operator
	Vec2 operator-(Vec2); //subtraction operator
	Vec2 operator*(double); //float multiplication
	Vec2 operator/(double c); //float div
	Vec2 operator*(int); //int multiplication

	std::string toString();
};

