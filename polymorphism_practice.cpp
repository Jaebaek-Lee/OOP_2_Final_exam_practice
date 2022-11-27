#include <iostream>

using namespace std;

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