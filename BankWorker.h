#pragma once
#include "Account.h"
#include "Task.h"
#include "Vector.hpp"
#include "Bank.h"





// GRESHNI KONSTRUKTORI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class BankWorker : public Account {
private:
	Vector<Task*> tasks;
	Bank* bank;


public:

	int getTasksSize()const;
	Task* getTaskByIndex(unsigned idx)const {
		return tasks[idx];
	}

	BankWorker(String acc_num, String _UCN, unsigned _age, String own, UserRoles role);

	void addTask(Task* task);

	void showTasks() const;

	void viewTask(int task_id)const;

	void approveTask(int task_id);

	void disapproveTask(int task_id, const Message message);

	bool validateUser(int task_id, const Bank& oldBank) {
		for (size_t i = 0; i < oldBank.getSize(); i++)
		{
			if (tasks[i].getType() == TaskType::Change) {
				Account* account = oldBank.get_account(tasks[i].getAccountId());
				if (account) {
					Message message("Task validated by " + getOwner());
					addMessage(message);
				}
				else {
					Message message("Validation failed by " + getOwner());
					addMessage(message);
				}
			}
		}
	}




};
