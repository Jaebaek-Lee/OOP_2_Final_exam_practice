#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class MyInteger {
public:
	MyInteger(int num) {
		this->num = num;
	}
	friend fstream& operator<<(fstream& out, const MyInteger& myint) {
		out << setw(7) << right << setfill('0') << myint.num << '\n';
		return out;
	}
	friend ifstream& operator>>(ifstream& in, MyInteger& myint) {
		int temp;
		in >> temp; //파일에 0000001 처럼 문자 '0'이 들어가있음. cin >> temp에서 temp가 int형일때 문자가 들어오면 fail 되는 것 처럼
		//오류가 날 것이라는 기대. 하지만 이건 cin이랑 다른 파일 스트림임. eof가 아니라면 >>로 화이트스페이스가 나올 때 까지 int형 temp에 담음.
		// 
		// 1. 이 경우, 파일은 0을 어떻게 인식하는가? 실제로는 0000001 중에서 1만 temp에 저장되었다.
		// 왜 그런가? setfill로 파일에 넣었던 '0'을 여기서는 정수로 취급하는가?

		/*while (!in) { //위 주석의 첫 줄과 같은 오류를 기대를 하고 만들었지만, 이게 존재하면 main에서의 조건문이 무한루프를 돈다..
			in.clear();
			in.ignore();
			in >> temp;
		}*/
		if (in) {
			myint.num = temp;
		}
		//cout << in.gcount();// 2. gcount는 왜 계속 0만 출력하는가? 위에서 나온 in >> temp로 인해 0이 아닌 무언가를 출력해야 하는게 아닌가?
		return in;
	}
	int getNum() {
		return num;
	}
private:
	int num;
};

int main() {
	//1번
	int num;
	fstream out{ "integers.txt", ios::out };

	cout << "Enter the integer.\n";
	cout << "Enter end-of-file to end input.\n";
	cout << "? ";
	while (cin >> num) {
		MyInteger tempInt(num);
		out << tempInt;
		cout << "? ";
	}
	out.close();

	ifstream in{ "integers.txt", ios::in}; // 3. 실제로 파일에서 하나씩 하나씩 읽어오는 것인가? 아니면 실제 파일의 내용을 통째로 버퍼로 옮겨오는 것인가?
	cout << '\n';
	while (in) {
		MyInteger tempInt(0);
		cout << in.tellg();
		in >> tempInt;
		if (in) {
			cout << setw(7) << setfill('0') << tempInt.getNum() << '\n';
		}
	}
	in.close();

	//2번
	ifstream in("integers.txt", ios::in);
	MyInteger integer(0);
	int no;
	in.seekg(0, ios::end);
	int size = in.tellg();//63
	in.seekg(0);
	while (cin >> no) {
		if (no != 0 && no * 9 <= size)
		{
			cout << "Line <" << no << "> number: ";
			int num;
			in >> num;
			cout << setw(7) << right << setfill('0') << num << '\n';
		}
		else break;
	}
}

/*
1
12
123
1234
12345
123456
1234567
'\n'
*/