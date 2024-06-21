#pragma once
#include "String.h"
#include "Client.h"

enum class TaskType {
	Open,
	Close,
	Change
};

class Client;

class Task {
private:
	//int id;
	TaskType type;
	Client* client;
	String nameBank = "Unknown";
public:
	Task() = default;
	Task(TaskType type, Client* client);
	Task(TaskType type, Client* _client, const String& accountID);
	Task(const TaskType& type, Client* _client, const String& accountNumber, const String& nameBank);

	const String& getBankName()const;

	const String& getUCN()const;

	const String& getFirstName()const;

	const String& getLastName()const;

	unsigned getAge()const;

	const String& getRole()const;

	TaskType getType() const;

	const String& getAccountNumber()const;

	Client* getClient()const;

	const String& getTypeName() const;
};