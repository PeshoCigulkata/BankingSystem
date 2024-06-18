#include "BankWorker.h"

unsigned getNumberLength(unsigned  n)
{

	if (n == 0)
		return 1;
	unsigned int res = 0;

	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return res;
}

char getCharFromDigit(int digit)
{
	if (digit < 0 || digit > 9)
		return '\0';

	return digit + '0';
}

String toString(unsigned number, String str) {
	unsigned length = getNumberLength(number);
	for (int i = length - 1; i >= 0; i--) {
		str += getCharFromDigit(number % 10);
	}

	return str;
}

const String& TypeToString(TaskType type) {
	String str = "";
	switch (type) {
	case TaskType::Open:
		str = "Open";
		break;
	case TaskType::Close:
		str = "Close";
		break;
	case TaskType::Change:
		str = "Change";
		break;
	default:
		str = "Unknown";
		break;
	}
	return str;
}

const String& RoleToString(UserRoles userRoles) {
	String str = "";
	switch (userRoles) {
	case UserRoles::Client:
		str = "Client";
		break;
	case UserRoles::BankWorker:
		str = "BankWorker";
		break;
	case UserRoles::OtherFirmWorker:
		str = "OtherFirmWorker";
		break;
	default:
		str = "Unknown";
		break;
	}
	return str;
}



int BankWorker::getTasksSize()const {
	return tasks.getCount();
}

void BankWorker::help() const {
	std::cout << "Commands available: " << std::endl;
	std::cout << "-check_avl [bank_name] [account_number] " << std::endl;
	std::cout << "-open [bank_name] " << std::endl;
	std::cout << "-close [bank_name] [account_number]  " << std::endl;
	std::cout << "-redeem [bank_name] [account_number] [verification_code]  " << std::endl;
	std::cout << "-change [new_bank_name] [current_bank_name] [account_number] " << std::endl;
	std::cout << "-list [bank_name] " << std::endl;
	std::cout << "-messages " << std::endl;
	std::cout << "-whoami " << std::endl;
	std::cout << "-exit " << std::endl;
}

void BankWorker::whoami() const
{
	std::cout << "Name: " << getFirstName() << " " << getLastName() << std::endl;
	std::cout << "Role: " << RoleToString(getRole()) << std::endl;
	std::cout << "Age: " << getAge() << std::endl;
	std::cout << "UCN: " << getUCN() << std::endl;
}

Task* BankWorker::getTaskByIndex(unsigned idx)const {
	return tasks[idx];
}

BankWorker::BankWorker(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& accNum, const UserRoles& role) :Account(_firstName, _lastName, _UCN, _age, accNum, role) {}

void BankWorker::addTask(Task* task) {
	tasks.push_back(task);
}

void BankWorker::showTasks() const {
	for (size_t i = 0; i < tasks.getCount(); ++i) {
		std::cout << "[" << i << "]" << " " << tasks[i]->getTypeName();
		std::cout << " Name: " << tasks[i]->getClient()->getFirstName() << " " << tasks[i]->getClient()->getLastName() << std::endl;
	}
}

void BankWorker::viewTask(int task_id)const {
	std::cout << "Task ID: " << tasks[task_id]->getAccountNumber() << std::endl;
	std::cout << "Type: " << tasks[task_id]->getTypeName() << std::endl;
	std::cout << "Client: " << tasks[task_id]->getClient()->getFirstName() << " " << tasks[task_id]->getClient()->getLastName() << std::endl;
	std::cout << "Age: " << tasks[task_id]->getClient()->getAge() << std::endl;
	std::cout << "UCN: " << tasks[task_id]->getClient()->getUCN() << std::endl;
}

void BankWorker::approveTask(int task_id) {
	Task* currentTask = getTaskByIndex(task_id);

	if (bank->validateUser(currentTask->getClient())) {
		if (currentTask->getType() == TaskType::Open) {
			String str;
			Message message(getFirstName() + " " + getLastName(), "You have opened an account in: ", bank->getName(), ". Your account ID is: " + toString(bank->getSize(), str));
			bank->sendAnswerToClient(message, currentTask->getClient());

			bank->create_account("0", currentTask->getClient());
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Close) {
			String str;
			Message message(getFirstName() + " " + getLastName(), "You have closed an account in: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());

			bank->close_account(currentTask->getAccountNumber());
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Change) {
			String str;
			Message message(getFirstName() + " " + getLastName(), "You have successfuly changed to: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());
			bank->create_account(/*balance*/, currentTask->getClient());     //TODO!!!!!!!!!!!!!!1
			tasks.remove(task_id);
		}
	}
	else {
		throw std::exception("The account doesnt exist! ");
	}
}

void BankWorker::disapproveTask(int task_id, const Message message) {
	Task* currentTask = getTaskByIndex(task_id);

	if (bank->validateUser(currentTask->getClient())) {
		if (currentTask->getType() == TaskType::Open) {
			Message message(getFirstName(), "Your request is denied: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Close) {
			Message message(getFirstName(), "Your request is denied: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Change /*&& hasApproved()*/) {
			String str;
			Message message(getFirstName(), "Your request is denied: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());
			tasks.remove(task_id);
		}
	}
	else {
		throw std::exception("The account doesnt exist! ");
		return;
	}
}

bool BankWorker::validate(int task_id) {
	Task* currentTask = getTaskByIndex(task_id);

	Client* currentClient = currentTask->getClient();
	String BankName = currentTask->getBankName();
	Bank* oldBank = currentClient->getBankByName(BankName);

	if (currentTask->getClient() == oldBank->getClient(currentClient) && currentTask->getUCN() == oldBank->getClientUCN(currentClient) && currentTask->getAge() == oldBank->getClientAge(currentClient)) {

		return true;
	}

	return false;
}


