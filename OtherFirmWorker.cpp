#include "OtherFirmWorker.h"
//const String& RoleToString(UserRoles userRoles) {
//	String str = "";
//	switch (userRoles) {
//	case UserRoles::Client:
//		str = "Client";
//		break;
//	case UserRoles::BankWorker:
//		str = "BankWorker";
//		break;
//	case UserRoles::OtherFirmWorker:
//		str = "OtherFirmWorker";
//		break;
//	default:
//		str = "Unknown";
//		break;
//	}
//	return str;
//}


OtherFirmWorker::OtherFirmWorker(const String& _firstName, const String& _lastName, const String& _UCN, unsigned _age, const String& password, const String& role) :Account(_firstName, _lastName, _UCN, _age, password, role) {}

Bank* OtherFirmWorker::getBankByName(const String& bankName)const {
	for (size_t i = 0; i < banks.getCount(); i++)
	{
		if (banks[i]->getName() == bankName) {
			return banks[i];
		}
	}
	return nullptr;
}

Client* OtherFirmWorker::getClientByUCN(const String& UCN)const {
	for (size_t i = 0; i < clients.getCount(); i++)
	{
		if (clients[i]->getUCN() == UCN) {
			return clients[i];
		}
	}
	return nullptr;
}

bool OtherFirmWorker::validateSum(const String& sum) {
	return sum[0] == '-' || sum[0] == '0';

}

void OtherFirmWorker::addBank( Bank* bank) 
{
	banks[banks.getCount()] = bank;
}

void OtherFirmWorker::send_check(const String& sum, const String& verificationCode, const String& BankName, const String& UCN) {
	Check check(verificationCode, sum);
	Bank* getBank = getBankByName(BankName);
	Client* getClient = getClientByUCN(UCN);
	Message message(getFirstName() + getLastName(), "You have a check assigned to you ", getBank->getName(), verificationCode);
	getClient->addMessage(message);
	getClient->receiveCheck(check);
}

void OtherFirmWorker::whoami() const
{
	std::cout << "Name: " << getFirstName() << " " << getLastName() << std::endl;
	std::cout << "Role: " << getRole() << std::endl;
	std::cout << "Age: " << getAge() << std::endl;
	std::cout << "UCN: " << getUCN() << std::endl;
}

void OtherFirmWorker::exit()const {
	std::cout << "Exited.";
}

void OtherFirmWorker::setBank(Bank* bank) {
	banks.push_back(bank);
}

void OtherFirmWorker::help() const
{
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

