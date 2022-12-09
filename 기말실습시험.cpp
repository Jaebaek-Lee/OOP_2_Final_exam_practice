#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Account {
public:
	Account(int = 0, const std::string& = "", double = 0);
	void setAccountNumber(int);
	int getAccountNumber() const;
	void setName(const std::string&);
	std::string getName() const;
	void setBalance(double);
	double getBalance() const;
private:
	int _accountNumber;
	char _name[15];
	double _balance;
};

Account::Account(int accountNumber, const std::string& name, double balance) {
	_accountNumber = accountNumber; setName(name), setBalance(balance);
}
void Account::setAccountNumber(int accountNumber) {
	_accountNumber = accountNumber;
}
int Account::getAccountNumber() const {
	return _accountNumber;
}
void Account::setName(const std::string& name) {
	for (int i = 0; name[i] != '\0'; ++i) {
		_name[i] = name[i];
	}
	_name[name.size()] = '\0';
}
std::string Account::getName() const {
	return _name;
}
void Account::setBalance(double balance) {
	_balance = balance;
}
double Account::getBalance() const {
	return _balance;
}

void interface();
void display(fstream&);
void update(fstream&);
void deletor(fstream&);
void adder(fstream&);

int main() {
	ifstream in("information.txt", ios::in);
	ofstream out("credit.bin", ios::out | ios::binary);

	if (!in) { cout << "error in"; }
	if (!out) { cout << "error out"; }
	//Account* credit = new Account[100];
	Account account;

	int num; char name[15]; double bal;

	for (int i = 0; i < 100; ++i) {
		//out.seekp(i * sizeof(account));
		out.write(reinterpret_cast<const char*>(&account), sizeof(account));
	}

	out.seekp(0); out.clear();

	while (in) {
		in >> num >> name >> bal;
		if (!in) { break; }
		out.seekp((num - 1) * sizeof(account));
		account.setAccountNumber(num); account.setName(name); account.setBalance(bal);
		out.write(reinterpret_cast<const char*>(&account), sizeof(account));
	}

	in.close();
	out.close();

	fstream newinout("credit.bin", ios::in | ios::out | ios::binary);
	if (!newinout) {
		cout << "!!!";
	}
	display(newinout); cout << endl;
	int order;

	interface();
	cin >> order;

	while (order != 5) {
		if (order == 1) {
			cout << "\n";
			update(newinout);
			cout << "\n";
			interface();
		}
		else if (order == 2) {
			cout << "\n";
			adder(newinout);
			cout << "\n";
			interface();
		}
		else if (order == 3) {
			cout << "\n";
			deletor(newinout);
			cout << "\n";
			interface();
		}
		else if (order == 4) {
			cout << "\n";
			display(newinout);
			cout << "\n";
			interface();
		}
		cin >> order;
	}
}

void interface() {
	cout << "1. update an account\n"
		<< "2. add a new account\n"
		<< "3. delete an account\n"
		<< "4. display information\n"
		<< "5. end program\n"
		<< "? ";
}

void display(fstream& newinout) {
	Account account;
	newinout.seekg(0);
	cout << "Accounts information.\n";
	while (newinout) {
		newinout.read(reinterpret_cast<char*>(&account), sizeof(account));
		if (!newinout) { break; }
		if (account.getAccountNumber() != 0) {
			cout << setw(3) << setfill('0') << right << account.getAccountNumber() << " "
				<< setw(15) << setfill(' ') << left << account.getName()
				<< setw(6) << setprecision(2) << fixed << account.getBalance() << "\n";
		}
	}
	newinout.clear();
}

void update(fstream& newinout) {
	int num; double bal;
	cout << "Enter account number to update (1 - 100): ";
	cin >> num;
	Account account;
	newinout.seekg((num - 1) * sizeof(account));
	newinout.read(reinterpret_cast<char*>(&account), sizeof(account));
	if (account.getAccountNumber() != 0) {
		cout << setw(3) << setfill('0') << right << account.getAccountNumber() << " "
			<< setw(15) << setfill(' ') << left << account.getName()
			<< setw(5) << setprecision(2) << fixed << account.getBalance() << "\n";
		cout << "Enter charge (+) or payment (-): ";
		cin >> bal;
		account.setBalance(account.getBalance() + bal);
		newinout.seekp((num - 1) * sizeof(account));
		newinout.write(reinterpret_cast<const char*>(&account), sizeof(account));
		cout << setw(3) << setfill('0') << right << account.getAccountNumber() << " "
			<< setw(15) << setfill(' ') << left << account.getName()
			<< setw(5) << setprecision(2) << fixed << account.getBalance() << "\n";
	}
	else
		cout << "Account has no information.\n";
	newinout.clear();
}

void adder(fstream& newinout) {
	int num;
	Account account;
	cout << "Enter new account number (1 - 100): ";
	cin >> num;
	newinout.seekg((num - 1) * sizeof(account));
	newinout.read(reinterpret_cast<char*>(&account), sizeof(account));
	if (account.getAccountNumber() != 0) {
		cout << "Account already exists.\n";
	}
	else {
		string name; double bal;
		cout << "Enter name and balance for add: ";
		cin >> name >> bal;
		account.setAccountNumber(num); account.setName(name); account.setBalance(bal);
		newinout.seekp((num - 1) * sizeof(account));
		newinout.write(reinterpret_cast<const char*>(&account), sizeof(account));
		display(newinout);
	}
	newinout.clear();
}

void deletor(fstream& newinout) {
	int num;
	cout << "Enter account number to delete (1 - 100): ";
	cin >> num;
	Account account;

	newinout.seekg((num - 1) * sizeof(account));
	newinout.read(reinterpret_cast<char*>(&account), sizeof(account));
	if (account.getAccountNumber() == 0) {
		cout << "Account #" << num << " is empty.\n";
	}
	else {
		account.setAccountNumber(0);
		newinout.seekp((num - 1) * sizeof(account));
		newinout.write(reinterpret_cast<char*>(&account), sizeof(account));
		cout << "Account #" << num << " deleted.\n";
	}
	newinout.clear();
}