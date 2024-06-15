#pragma once
#include "String.h"
#include "Account.h"
#include "Message.h"
#include "Vector.hpp"
#include "BankWorker.h"
#include "Client.h"
//bankata znae za svoite klienti i rabotnivi

class Bank {
private:
	String name;       // name of the bank

	Account** accounts;
	unsigned size;
	unsigned capacity;
	String CheckSums[1024]; //every index indicates an account with the checks value they have received, if its 0 => no check received

	Vector<Message> messages;
	Vector<Task> tasks;
	Vector<BankWorker*> employees;
	Vector<Client*> clients;
	void free();
	void resize();
public:
	Bank();
	Bank(String n);

	Account* get_account(const String& account_id)const;
	Account* get_account_by_index(unsigned idx)const {
		return accounts[idx];
	}

	void print_account_by_index(unsigned idx)const {
		accounts[idx]->printAccount();
	}

	unsigned getSize()const;
	String getCheckAtIdx(unsigned idx)const;
	String getName()const;

	String create_account(const String& owner, UserRoles role, const String& UCN, unsigned age);

	bool close_account(const String& account_number);

	bool validateUser(const Client* client)const {
		for (size_t i = 0; i < clients.getCount(); i++)
		{
			if (clients[i] == client) {
				return true;
			}
		}
		return false;
	}

	int getLeastBusyWorker()const;

	int getTaskSize()const {
		return tasks.getCount();
	}

	void receiveTask(const Task& toDo) {
		tasks.push_back(toDo);
	}

	BankWorker* getEmployeeByIndex(int index)const {
		return employees[index];
	}

	void sendAnswerToClient(const Message& message, Client* client) {
		client->addMessage(message);
	
	}

	Bank(const Bank& other) = delete;
	Bank& operator=(const Bank& other) = delete;
	~Bank();
};
