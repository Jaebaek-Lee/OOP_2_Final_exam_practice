#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX_LEN 20

using namespace std;

//연습문제1
class MyInteger {
public:
	MyInteger(int temp) {
		num = temp;
	}
	friend ofstream& operator<<(ofstream& out, MyInteger& myright) {
		out << setw(7) << setfill('0') << right << myright.num << '\n';
		return out;
	}
	friend ifstream& operator>>(ifstream& in, MyInteger& right) {
		in >> right.num;
		return in;
	}
private:
	int num = 0;
};

int main() {
	ofstream out("myInt.txt", ios::out);
	cout << "Enter the integer.\n"
		<< "Enter end-of-file to end input.\n"
		<< "? ";
	int temp;

	while (cin >> temp) {
		MyInteger myint(temp);
		out << myint;
		cout << "? ";
	}

	out.close();

	ifstream in("myint.txt", ios::in);
	in.seekg(0, ios::end);
	int size = in.tellg();
	
	int no;
	cin.clear();
	cin.ignore(); //eof는 버퍼에 안들어가는구나...
	while (cin >> no) {
		if (no == 0 || no > size / 9) { break; }
		in.seekg((no - 1) * 9);
		cout << "Line <" << no << "> number: ";
		int num;
		in >> num;
		cout << setfill('0') << setw(7) << right << num << '\n';
		cout << setfill(' ');
	}
}

//과제6
int main() {
	ifstream read("C:\\Windows\\system.ini", ios::in);

	ofstream out("이재백.ini", ios::out);

	while (read) {
		string temp = "";
		getline(read, temp);
		out << temp;
		if (read) {
			out << "\n";
		}
	}
}

//연습문제2
class Cipher {
public:
	Cipher() {}
	Cipher(int key, const char* text) : key{key} {
		for (int i = 0; text[i] != '\0'; ++i) {
			bcd[i] = text[i];
		}
	}
	void decode() {
		for (int i = 0; bcd[i] != '\0'; ++i) {
			if (bcd[i] - key < 65) {
				bcd[i] = bcd[i] - key + 26;
			}
			else {
				bcd[i] = bcd[i] - key;
			}
		}
	}
	char* bcdout() { return bcd; }
private:
	int key = 0;
	char bcd[MAX_LEN] = "";
};

int main() {
	int key;
	char text[MAX_LEN + 1];
	
	ofstream out("code.bin", ios::out | ios::binary);
	while (cin >> key >> text) {
		Cipher temp(key, text);
		out.write(reinterpret_cast<const char*>(&temp), sizeof(Cipher));
	}

	out.close();

	ifstream in("code.bin", ios::in | ios::binary);
	Cipher code;
	in.read(reinterpret_cast<char*>(&code), sizeof(code));
	while (in) {
		cout << "Decode output: ";
		code.decode();
		cout << code.bcdout() << '\n';
		in.read(reinterpret_cast<char*>(&code), sizeof(code));
	}
}