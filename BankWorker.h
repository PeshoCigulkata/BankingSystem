#pragma once
#include "Account.h"
#include "Task.h"
#include "Vector.hpp"
#include "Bank.h"

class Account;
class Bank;
class Task;


class BankWorker : public Account {
private:
	Vector<Task*> tasks;
	Bank* bank;

	Task* getTaskByIndex(unsigned idx)const;

public:
	BankWorker(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& password,  const String& role);

	void setBank(Bank* bank);

	void addTask(Task* task);

	void showTasks() const;

	void viewTask(int task_id)const;

	void approveTask(int task_id);

	void disapproveTask(int task_id, const Message message);

	bool validate(int task_id);

	int getTasksSize()const;

	virtual void exit() const override; //TODO!!!!!!!!!!!!!!!!!
	virtual void whoami() const override;
	virtual void help() const override;
};
