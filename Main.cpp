#include <iostream>
#include "Login.h"
UserRoles StringToRole(const String& str) {
	if (str == "Client") {
		return UserRoles::Client;
	}
	else if (str == "BankWorker") {
		return UserRoles::BankWorker;
	}
	else if (str == "OtherFirmWorker") {
		return UserRoles::OtherFirmWorker;
	}
	else {
		return UserRoles::undefined;
	}
}



int main() {
	Login system;
	while (true) {
		String commands = "";
		std::cin >> commands;
		if (commands == "signup") {
			String firstName, lastName, UCN, role;
			unsigned age;
			std::cout << "Enter first name,last name,UCN,age and role: ";
			std::cin >> firstName >> lastName >> UCN >> role >> age;
			UserRoles _role = StringToRole(role);

			if (_role == UserRoles::Client) {
				std::cout << "Enter password: ";
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, _role, password, "No bank");

			}
			else if (_role == UserRoles::BankWorker) {
				std::cout << "Enter bank name: " << std::endl;
				String bankName = "";
				std::cin >> bankName;
				std::cout << "Enter password: " << std::endl;
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, _role, password, bankName);

			}
			else if (_role == UserRoles::OtherFirmWorker) {
				std::cout << "Enter bank name: " << std::endl; 
				String bankName = "";
				std::cin >> bankName;
				std::cout << "Enter password: " << std::endl;
				String password = "";
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, _role, password, bankName);
			}
			else {
				throw std::runtime_error("Problem man...");
			}
		}
	}
}

