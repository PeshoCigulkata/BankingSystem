#include <iostream>
#include "Login.h"



//DUE TO LIMITED TIME THERE ISNT ERROR HANDLING!

int main() {
	std::cout << "*---------------------------------------------*" << std::endl;
	std::cout << "The command to stop creating banks is:  " << std::endl;
	std::cout << "-'No'" << std::endl;
	std::cout << "*---------------------------------------------*";
	std::cout<<std::endl;
	std::cout << std::endl;

	Login system;
	String str = "";
	int index = 0;
	while (str != "No") {
		std::cout << "Create a bank: " << std::endl;
		std::cin >> str;
		if (str == "No" && index == 0) {
			std::cout << "But you haven't created any banks?"<<std::endl;
			break;
		}
		else {
			index++;
		}
		system.create_bank(str);
	}

	if (index == 0) {
		std::cout << "End the program with 'end_program' "<<std::endl;
	}
	else {
		std::cout << "You have created banks! Procceed with further commands. " << std::endl;
	}

	while (true) {
		String commands = "";
		std::cin >> commands;
		if (commands == "signup") {
			std::cout << "Enter role: ";
			String role;
			std::cin >> role;
			if (role == "Client") {
				String firstName, lastName, UCN, bankName;
				unsigned age;
				std::cout << "Enter first name,last name,UCN, age and bank association " << std::endl;
				std::cout << "First name: ";
				std::cin >> firstName;
				std::cout << "Last name: ";
				std::cin >> lastName;
				std::cout << "UCN: ";
				std::cin >> UCN;
				std::cout << "Age: ";
				std::cin >> age;
				std::cout << "Bank association: ";
				std::cin >> bankName;
				std::cout << "Enter password: ";
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, role, password, bankName);

			}
			else if (role == "BankWorker") {
				String firstName, lastName, UCN, bankName;
				unsigned age;
				std::cout << "Enter first name,last name,UCN, age and bank association " << std::endl;
				std::cout << "First name: ";
				std::cin >> firstName;
				std::cout << "Last name: ";
				std::cin >> lastName;
				std::cout << "UCN: ";
				std::cin >> UCN;
				std::cout << "Age: ";
				std::cin >> age;
				std::cout << "Bank association: ";
				std::cin >> bankName;
				std::cout << "Enter password: ";
				String password;
				std::cin >> password;
				system.signup(firstName, lastName, UCN, age, role, password, bankName);

			}
			else if (role == "OtherFirmWorker") {
				String firstName, lastName, UCN, bankName;
				unsigned age;
				std::cout << "Enter first name,last name,UCN, age and bank association " << std::endl;
				std::cout << "First name: ";
				std::cin >> firstName;
				std::cout << "Last name: ";
				std::cin >> lastName;
				std::cout << "UCN: ";
				std::cin >> UCN;
				std::cout << "Age: ";
				std::cin >> age;
				std::cout << "Bank association: ";
				std::cin >> bankName;
				std::cout << "Enter password: ";
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
		else if (commands == "redeem") {
			String bankName, accountNumber, verificationCode;
			std::cout << "Enter the name of the bank where the check was sent to: ";
			std::cin >> bankName;
			std::cout << "Enther your account ID: ";
			std::cin >> accountNumber;
			std::cout << "Enter the verification code: ";
			std::cin >> verificationCode;
			system.userRedeem(bankName, accountNumber, verificationCode);
		}
		else if (commands == "messages") {
			system.userMessages();
		}
		else if (commands == "tasks") {
			system.userTasks();
		}
		else if (commands == "view") {
			std::cout << "Enter the index of the task you wish you view: ";
			int index;
			std::cin >> index;
			system.userView(index);
		}
		else if (commands == "approve") {
			std::cout << "Enter the index of the task you want to approve: ";
			int index;
			std::cin >> index;
			system.userApprove(index);
		}
		else if (commands == "disapprove") {
			std::cout << "Enter the index of the task you want to disapprove: ";
			int index;
			std::cin >> index;
			std::cout << "Write details for the response.";
			std::cout << "First name of worker: ";
			String firstName, lastName;
			std::cin >> firstName;
			std::cout << "Last name of worker: ";
			std::cin >> lastName;
			std::cout << "Reason: ";
			String content;
			std::cin >> content;
			String bankName;
			std::cout << "Bank sent from: ";
			std::cin >> bankName;
			String str="";
			str.concat(firstName);
			str += lastName;
			Message message(str, content, bankName);
			system.userDisapprove(index, message);
		}
		else if (commands == "validate") {
			std::cout << "Enter the index of the task you want to validate: ";
			int index;
			std::cin >> index;
			system.userValidate(index);
			}
		else if (commands == "send_check") {
			std::cout << "Enter the sum you wish to send: ";
			String sum;
			std::cin >> sum;
			std::cout << "Enter verification code: ";
			String verCode;
			std::cin >> verCode;
			std::cout << "Enter the UCN of the receiver: ";
			String UCN;
			std::cin >> UCN;
			std::cout << "Enter the name of the bank of the receiver you wish to send to: ";
			String bankName;
			std::cin >> bankName;
			system.userSendCheck(sum, verCode, bankName, UCN);
			}
		else if (commands == "end_program") {
			std::cout << "Program ended! ";
			return 0;
		}
	}
}

