#pragma once
#include "String.h"


enum class TaskType {
	Open,
	Close,
	Change
};


class Task {
private:
	//int id;
	TaskType type;
	Client* client;
	String nameBank = "Unknown";
public:
	Task(TaskType type, Client* client) :type(type), client(client) {}
	Task(const TaskType& type, Client* _client, const String& accountNumber, const String& nameBank) {
		this->type = type;
		client = _client;
		client->setAccountNumber(accountNumber);
		
	}

	const String& getBankName()const {
		return nameBank;
	}

	const String& getUCN()const {
		return client->getUCN();
	}

	unsigned getAge()const {
		return client->getAge();
	}

	UserRoles getRole()const {
		return client->getRole();
	}

	TaskType getType() const {
		return type;
	}

	const String& getAccountNumber()const {
		return client->getAccountNumber();
	}

	const String& getClientName() const {
		return client->getOwner();
	}

	Client* getClient()const {
		return client;
	}

	String getTypeName() const {
		switch (type) {
		case TaskType::Open:
			return "Open";
		case TaskType::Close:
			return "Close";
		case TaskType::Change:
			return "Change";
		default:
			return "Unknown";
		}
	}
};