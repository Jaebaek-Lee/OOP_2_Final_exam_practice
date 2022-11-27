#include <iostream>

using namespace std;

class Circle {
public:
	Circle(double radius) {
		this->radius = new double(radius);
	}
	double area() {
		return *radius * *radius * 3.14;
	}
	~Circle() {
		cout << "Circle's radius: " << *radius << "cm\n";
		delete radius;
	}
private:
	double* radius;
};

class Cone : public Circle {
public:
	Cone(double radius, double high) : Circle(radius), high { new double(high) } {}
	~Cone() {
		cout << "Cone's volume: " << area() * *high / 3 << " cm^3\n";
		delete high;
	}
private:
	double* high;
};

class Cylinder : public Circle {
public:
	Cylinder(double radius, double high) : Circle(radius), high{ new double(high) } {}
	~Cylinder() {
		cout << "Cylinder's volume: " << area() * *high << " cm^3\n";
		delete high;
	}
private:
	double* high;
};

int main() {
	Cone cone(4, 5);
	Cylinder cylinder(5, 4);
}