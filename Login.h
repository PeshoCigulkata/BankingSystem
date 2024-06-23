#pragma once
#include "Vector.hpp"
//#include "String.h"
#include "Bank.h"
#include "OtherFirmWorker.h"
#include "Account.h"
/*The idea is to have main space of all accounts and in case of exit we leave it, so every class inherits Login.*/


class Client;
class BankWorker;
class OtherFirmWorker;
class Bank;

class Login {
private:                                    //The static variables indicate the users we have at the moment!, CurrentUsers is live based pointers and in case of exiting the program we make the pointer of hte user in there nullPTR
	Vector<Client> clients;
	Vector<BankWorker> bankWorkers;
	Vector<OtherFirmWorker> otherFirmWorker;
	Vector<Bank> banks;

	int index = -1;
	Account* currentUser = nullptr;
	bool isClient = false;
	bool isBankWorker = false;
	bool isOtherFirmWorker = false;

	void getRole(const String& firstName, const String& lastName, const String& password,String& role);

	void getInfoOfExistingUser(String& balance, String& accountID, String& UCN, unsigned& age);

	Bank* getBankByName(const String& bankName);

	//Client* getLogged;
protected:
	String str = "";
public:
	Login() = default;
	void login(const String& firstName, const String& lastName, const String& password);

	void signup(const String& firstName, const String& lastName, const String& UCN, unsigned age, const String& role, const String& password, const String& bankName);

	void create_bank(const String& bankName);

	void userWhoami()const;

	void userHelp()const;

	void checkUser_avl(const String& bankName,const String& accNum)const;

	void userOpen(const String& bankName);

	void userCLose(const String& bankName,const String& accountNumber);

	void userChange(const String& neweBank,const String& currentBank,const String& accountNumber);

	void userList(const String& bankName);
	
	void userRedeem(const String& bankName,const String& accountID,const String& verificationCode);

	void userMessages()const;

	void userTasks()const;

	void userView(unsigned index)const;

	void userApprove(unsigned index);

	void userDisapprove(unsigned index,const Message& message);

	void userValidate(int index);

	void userSendCheck(const String& sum,const String& verificationCode, const String& bankName, const String& UCN);

	void exit();
};


