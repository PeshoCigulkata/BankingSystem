#pragma once
#include "String.h"
#include "Account.h"
#include "Message.h"
#include "Vector.hpp"
#include "BankWorker.h"
#include "Client.h"
//bankata znae za svoite klienti i rabotnici


//TODO: FIX CLIENTS!	

class Bank {
private:
	String name="";       // name of the bank

	Vector<Account*> accounts;
	Vector<Message> messages;
	Vector<Task> tasks;
	Vector<BankWorker*> employees;
	Vector<Client*> clients;
	
public:
	Bank()=default;
	Bank(String n);

	const String& getName()const;

	void create_account(const String& balance,Client* client);
	void close_account(const String& account_number);

	bool validateUser(const Client* client)const;

	int getLeastBusyWorker()const;

	void receiveTask(const Task& toDo);

	BankWorker* getEmployeeByIndex(int index)const;

	void sendAnswerToClient(const Message& message, Client* client);

	const Client* getClient(const Client* client)const;

	int getTaskSize()const;
	Client* getClientByAccNum(const String& accountNumber)const;
	Bank(const Bank& other) = delete;
	Bank& operator=(const Bank& other) = delete;
	~Bank()=default;
};
