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




int BankWorker::getTasksSize()const {
	return tasks.getCount();
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
		std::cout << "Task ID: " << tasks[i]->getAccountNumber()
			<< ", Type: " << tasks[i]->getTypeName()
			<< ", Client: " << tasks[i]->getClientName()
			<< std::endl;
	}
}

void BankWorker::viewTask(int task_id)const {
	std::cout << "The task you have has type: " << tasks[task_id]->getTypeName() << std::endl;
	std::cout << "Task ID: " << tasks[task_id]->getAccountNumber()
		<< ", Client: " << tasks[task_id]->getClientName()
		<< std::endl;
}

void BankWorker::approveTask(int task_id) {
	Task* currentTask = getTaskByIndex(task_id);

	if (bank->validateUser(currentTask->getClient())) {
		if (currentTask->getType() == TaskType::Open) {
			String str;
			Message message(getFirstName(), "You have opened an account in: ", bank->getName(), ". Your account ID is: " + toString(bank->getSize(), str));
			bank->sendAnswerToClient(message, currentTask->getClient());

			bank->create_account(/*balance*/, currentTask->getClient());     //TODO!!!!!!!!!!!!!!1
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Close) {
			String str;
			Message message(getFirstName(), "You have closed an account in: ", bank->getName());
			bank->sendAnswerToClient(message, currentTask->getClient());

			bank->close_account(currentTask->getAccountNumber());
			tasks.remove(task_id);
		}
		else if (currentTask->getType() == TaskType::Change) {
			String str;
			Message message(getFirstName(), "You have successfuly changed to: ", bank->getName());
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

	if (currentTask->getClientName() == oldBank->getClientName(currentClient) && currentTask->getUCN() == oldBank->getClientUCN(currentClient) && currentTask->getAge() == oldBank->getClientAge(currentClient)) {

		return true;
	}

	return false;
}


