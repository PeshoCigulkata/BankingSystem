#include <iostream>
#include "Login.h"


int main() {
	Login system;
	String str = "";
	while (str != "No") {
		std::cout << "Create a bank: " << std::endl;
		std::cin >> str;
		system.create_bank(str);
	}
	std::cout << "You have created banks! Procceed with further commands. " << std::endl;

	while (true) {
		String commands = "";
		std::cin >> commands;
		if (commands == "signup") {
			String firstName, lastName, UCN, role, bankName;
			unsigned age;
			std::cout << "Enter first name,last name,UCN,role and age and bank association "<<std::endl;
			std::cout << "First name: ";
			std::cin >> firstName;
			std::cout << "Last name: ";
			std::cin >> lastName;
			std::cout << "UCN: ";
			std::cin >> UCN;
			std::cout << "Role: ";
			std::cin >> role;
			std::cout << "Age: ";
			std::cin >> age;
			std::cout << "Bank association: ";
			std::cin >> bankName;
			if (role == "Client") {
				std::cout << "Enter password: ";
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, role, password, bankName);

			}
			else if (role == "BankWorker") {
				std::cout << "Enter bank name: " << std::endl;
				String bankName = "";
				std::cin >> bankName;
				std::cout << "Enter password: " << std::endl;
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, role, password, bankName);

			}
			else if (role == "OtherFirmWorker") {
				std::cout << "Enter bank name: " << std::endl;
				String bankName = "";
				std::cin >> bankName;
				std::cout << "Enter password: " << std::endl;
				String password = "";
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, role, password, bankName);
			}
			else {
				throw std::runtime_error("Problem man...");
			}
		}
		else if (commands == "login") {
			String firstName, lastName, password;
			std::cout << "Enter first name, last name and password. " << std::endl;
			std::cout << "First name: ";
			std::cin >> firstName;
			std::cout << "Last name: ";
			std::cin >> lastName;
			std::cout << "Password: ";
			std::cin >> password;
			system.login(firstName, lastName, password);
		}
		else if (commands == "whoami") {
			system.userWhoami();
		}
		else if (commands == "help") {
			system.userHelp();
		}
		else if (commands == "exit") {
			system.exit();
		}
		else if (commands == "check_avl") {
			String bankName, accountNumber;
			std::cout << "Bank Name: ";
			std::cin >> bankName;
			std::cout << "Account Number: ";
			std::cin >> accountNumber;
			system.checkUser_avl(bankName, accountNumber);
		}
		else if (commands == "list"){
			String bankName;
			std::cout << "Enter the name of your bank: ";
			std::cin >> bankName;
			system.userList(bankName);
		}
		else if (commands == "open") {
			String bankName;
			std::cout << "Enter the name of the bank: ";
			std::cin >> bankName;
			system.userOpen(bankName);
		}
		else if (commands == "close") {
			String bankName,accountNumber;
			std::cout << "Enter the name of the bank: ";
			std::cin >> bankName;
			std::cout << "Enter account id: ";
			std::cin >> accountNumber;
			system.userCLose(bankName, accountNumber);
		}
		else if (commands == "change") {
			String newbankName,currentBankName, accountNumber;
			std::cout << "Enter the name of the new bank: ";
			std::cin >> newbankName;
			std::cout << "Enter the name of the current bank";
			std::cin >> currentBankName;
			std::cout << "Enter account number: ";
			std::cin >> accountNumber;
			system.userChange(newbankName, currentBankName, accountNumber);
		}
	}
}

