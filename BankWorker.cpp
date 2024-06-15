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

int BankWorker::getTasksSize()const {
	return tasks.getCount();
}

BankWorker::BankWorker(String acc_num, String _UCN, unsigned _age, String own, UserRoles role)
	: Account(acc_num, _UCN, _age, own, role) {}

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

	std::cout << "Task ID: " << tasks[task_id]->getAccountNumber()
		<< ", Type: " << tasks[task_id]->getTypeName()
		<< ", Client: " << tasks[task_id]->getClientName()
		<< std::endl;
}

void BankWorker::approveTask(int task_id) {
	Task* currentTask = getTaskByIndex(task_id);
	//TRQBVA DA IZPRATIM SUOBSHTENIE DO CLIENTA
	String str;
	Message message("You have opened an account in: " + bank->getName() + ". Your account ID is: " + toString(bank->getSize(), str));
	bank->sendAnswerToClient(message, currentTask->getClient());

	bank->create_account(currentTask->getClientName(), currentTask->getRole(), currentTask->getUCN(), currentTask->getAge());
}

void BankWorker::disapproveTask(int task_id, const Message message) {
	Task* currentTask = getTaskByIndex(task_id);
	//----------------------------------
	////// WE MUST VALIDATE THE USER!!!          DONE!!
	//----------------------------------

	if (bank->validateUser(currentTask->getClient())) {
		if (currentTask->getType() == TaskType::Open) {
			Message message("Your request is denied: ");
			bank->sendAnswerToClient(message, currentTask->getClient());
		}
		else if (currentTask->getType() == TaskType::Close) {
			Message message("Your request is denied: ");
			bank->sendAnswerToClient(message, currentTask->getClient());
		}
		else if (currentTask->getType() == TaskType::Change) {
			String str;
			Message message("You have opened an account in: " + bank->getName() + ". Your account ID is: " + toString(bank->getSize(), str));
			bank->sendAnswerToClient(message, currentTask->getClient());
		}
	}
	else {
		std::cout << "Such account doesnt exist!" << std::endl;
		return;
	}

}