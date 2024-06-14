#pragma once
#include "String.h"


enum class TaskType {
    Open,
    Close,
    Change
};

enum class UserRoles {
    Client,
    BankWorker,
    OtherFirmWorker,
    undefined

};

class Task {
private:
    int id;
    TaskType type;
    String clientName;
    UserRoles role;
    int UCN;
    unsigned age;
    int account_id;
public:
    Task(TaskType type, const String& clientName)
        : /*id(id),*/ type(type), clientName(clientName) {}

    int getId() const {
        return id;
    }

    int getUCN()const {
        return UCN;
    }

    unsigned getAge()const {
        return age;
    }

    UserRoles getRole()const {
        return role;
    }

    TaskType getType() const {
        return type;
    }

    int getAccountId()const {
        return account_id;
    }

    String getClientName() const {
        return clientName;
    }

    String getDetails() const {
        return details;
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