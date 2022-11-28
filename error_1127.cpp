#include <iostream>
#include <string>
#include <sstream>

using namespace std;
//
//class Animal {
//public:
//	Animal(string kingdom) : kingdom { kingdom } {}
//	virtual void display() = 0;
//private:
//	string kingdom;
//};
//
//void Animal::display() {
//	cout << kingdom;
//}
//
//class Pisces : public Animal{
//public:
//	Pisces(string kingdom, string name) : Animal(kingdom), name{name} {}
//	virtual void display() override {
//		Animal::display();
//		cout << "->" << "Pisces->" << name << '\n';
//	}
//private:
//	string name;
//};
//
//class Amphibian : public Animal {
//public:
//	Amphibian(string kingdom, string name) : Animal(kingdom), name{name} {}
//	virtual void display() override {
//		Animal::display();
//		cout << "->" << "Amphibian" << "->" << name << '\n';
//	}
//private:
//	string name;
//};
//
//int main() {
//	Pisces carp("Animalia", "Carp");
//	Amphibian frog("Animalia", "Frog");
//	carp.display();
//	cout << endl;
//	frog.display();
//}

class Beverage {
public:
	Beverage(int q, int p) : q{ q }, p{ p } {
	}
	int getp() { return p; }
	virtual string tostring() = 0;
private:
	int q;
	int p;
};

string Beverage::tostring() {
	stringstream temp;
	temp << "Drink capacity: " << q << " ml\n"
		<< "Price: " << p << " W";
	return temp.str();
}

class Juice : public Beverage {
public:
	Juice(string flavor, int q, int p) : Beverage(q, p), flavor{ flavor } {}
	virtual string tostring() override {
		ostringstream temp;
		temp << "<" << flavor << "-flavored juice's info>\n" << Beverage::tostring();
		return temp.str();
	}
private:
	string flavor;
};

class Alcohol : public Beverage {
public:
	Alcohol(string category, int q, int p) : Beverage(q, p), category{category} {}
	virtual string tostring() override {
		ostringstream temp;
		temp << "<" << category << "-categoryed alcohol's info>\n" << Beverage::tostring();
		return temp.str();
	}
private:
	string category;
};

int main() {
	Beverage* _most_expensive = nullptr;
	Beverage* shoping_list[] = {
		new Juice("Orange", 200, 1000),
		new Juice("Grapefruit", 220, 18000),
		new Alcohol("Beer", 740, 35000)
	};

	for (int i{ 0 }; i < 3; ++i) {
		static int temp = shoping_list[0]->getp();
		if (shoping_list[i]->getp() >= temp) {
			temp = shoping_list[i]->getp();
			_most_expensive = shoping_list[i];
		}
	}
	
	cout << _most_expensive->tostring() << endl;
}