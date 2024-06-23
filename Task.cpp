#include "Task.h"

//enum class TaskType {
//	Open,
//	Close,
//	Change
//};

Task::Task(const String& type, Client* client) :type(type), client(client) {

}
Task::Task(const String& type, Client* _client, const String& accountID) :type(type), client(_client) {
	client->setAccountNumber(accountID);
}
Task::Task(const String& type, Client* _client, const String& accountNumber, const String& nameBank) {
	this->type = type;
	client = _client;
	client->setAccountNumber(accountNumber);

}

const String& Task::getBankName()const {
	return nameBank;
}

const String& Task::getUCN()const {
	return client->getUCN();
}

const String& Task::getFirstName() const
{
	return client->getFirstName();
}

const String& Task::getLastName() const
{
	return client->getLastName();
}

unsigned Task::getAge()const {
	return client->getAge();
}

const String& Task::getRole()const {
	return client->getRole();
}

const String& Task::getType() const {
	return type;
}

const String& Task::getAccountNumber()const {
	return client->getAccountNumber();
}

Client* Task::getClient()const {
	return client;
}

//const String& Task::getTypeName() const {
//	switch (type) {
//	case TaskType::Open:
//		return "Open";
//	case TaskType::Close:
//		return "Close";
//	case TaskType::Change:
//		return "Change";
//	default:
//		return "Unknown";
//	}
//}