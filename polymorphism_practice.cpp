#include <iostream>

using namespace std;

//1
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

//2번
class  Person {
public:
	Person(string name) : name{name} {}
	virtual void display() {
		cout << "Name: " << name << '\n';
	}
private:
	string name;
};

class Student : public Person {
public:
	Student(string name, int num, string major) 
		: Person(name), studentNumber{ num }, major{ major } {}
	void display() override {
		Person::display();
		cout << "Student ID: " << studentNumber << '\n';
		cout << "Department: " << major << '\n';
	}
private:
	int studentNumber;
	string major;
};

class Professor : public Person {
public:
	Professor(string name, string major, string field)
		: Person(name), major{major}, field{field} {}
	void display() override {
		Person::display();
		cout << "Department: " << major << '\n';
		cout << "Field: " << field << '\n';
	}
private:
	string major;
	string field;
};

int main() {
	Person* person[3] = {
		new Student("홍길동", 12345678, "컴퓨터공학과"),
		new Student("김철수", 87654321, "컴퓨터공학과"),
		new Professor("김인하", "컴퓨터공학과", "머신러닝")
	};
	for (int i = 0; i < 3; ++i) {
		person[i]->display();
		cout << endl;
	}
}
