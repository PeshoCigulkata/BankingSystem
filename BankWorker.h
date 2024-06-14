#pragma once
#include "Account.h"
#include "Task.h"
#include "Vector.hpp"
#include "Bank.h"





// GRESHNI KONSTRUKTORI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class BankWorker : public Account, public Bank {
private:
	Vector<Task> tasks;

public:
	BankWorker(int acc_num, int _UCN, unsigned _age, String own)
		: Account(acc_num, own, _UCN, _age, UserRoles::BankWorker) {}

	void addTask(const Task& task) {
		tasks.push_back(task);
	}

	void showTasks() const {
		for (size_t i = 0; i < tasks.getCount(); ++i) {
			std::cout << "Task ID: " << tasks[i].getId()
				<< ", Type: " << tasks[i].getTypeName()
				<< ", Client: " << tasks[i].getClientName()
				<< std::endl;
		}
	}

	void viewTask(int task_id) {
		for (size_t i = 0; i < tasks.getCount(); i++) {
			if (tasks[i].getId() == task_id) {
				std::cout << "Task ID: " << tasks[i].getId()
					<< ", Type: " << tasks[i].getTypeName()
					<< ", Client: " << tasks[i].getClientName()
					<< ", Details: " << tasks[i].getDetails()
					<< std::endl;
				return;
			}
		}
		std::cout << "Task not found." << std::endl;
	}

	void approveTask(int task_id, Bank& oldBank) {
		for (size_t i = 0; i < tasks.getCount(); i++)
		{
			if (tasks[i].getId() == task_id) {
				if (tasks[i].getType() == TaskType::Open) {
					create_account(tasks[i].getClientName(), tasks[i].getRole(), tasks[i].getUCN(), tasks[i].getAge());
					Message message("Account opened for: " + tasks[i].getClientName());
					addMessage(message);
				}
				else if (tasks[i].getType() == TaskType::Close) {
					if (close_account(tasks[i].getAccountId())) {
						Message message("Account closed for: " + tasks[i].getClientName());
						addMessage(message);
					}

				}
				else if (tasks[i].getType() == TaskType::Change) {
					Account* account = oldBank.get_account(tasks[i].getAccountId());
					if (account && (account->getOwner() == tasks[i].getClientName())) {
						Message message("Account changed for: " + tasks[i].getClientName());
						addMessage(message);
					}
					else {
						Message message("Validation failed for account change for " + tasks[i].getClientName());
						addMessage(message);
					}

				}
				break;
			}
			tasks.remove(i);

		}
	}

	void disapproveTask(int task_id, const Message message) {
		for (size_t i = 0; i < tasks.getCount(); ++i) {
			if (tasks[i].getId() == task_id) {
				Message message("Task disapproved by " + getOwner() + ": " + message.getContent());
				addMessage(message);
				tasks.remove(i);
				return;
			}
		}
	}

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





	//cif, prah za prane, omekotitel, rolo, hlqb 

};
