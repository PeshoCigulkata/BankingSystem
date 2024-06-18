#pragma once
#include "Account.h"
#include "Task.h"
#include "Vector.hpp"
#include "Bank.h"



//User successfuly validated!
		// funckiq WANTS TO APPROVE, v konzolata pishem string i sravnqvame s "true" i "false"
		//if(approved){
		//-- send Message che e uspeshno
		//}else{
		//send message che ne e approved
		//}

// GRESHNI KONSTRUKTORI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class BankWorker : public Account {
private:
	Vector<Task*> tasks;
	Bank* bank;

	Task* getTaskByIndex(unsigned idx)const;

public:
	BankWorker(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& accNum, const UserRoles& role);

	void addTask(Task* task);

	void showTasks() const;

	void viewTask(int task_id)const;

	void approveTask(int task_id);

	void disapproveTask(int task_id, const Message message);

	bool validate(int task_id);

	int getTasksSize()const;

	virtual void exit()override; //TODO!!!!!!!!!!!!!!!!!
	virtual void whoami()const override;
	virtual void help()const override;
};
