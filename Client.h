#pragma once
#include "Account.h"
#include "Bank.h"
#include "Vector.hpp"
#include "Message.h"




//--------------------------------------------------------------------------
//   DA SE DOOPRAVI SUOBSHTENIQTA KOITO POLUCHAVA CLIENTA!!!!!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------



class Client : public Account {
private:
	Bank array[1024];
	Vector<Message> messages;

public:
	Client();

	void check_avl()const;

	void open(Bank& bank);

	void close(Bank& other,int account_number);

	void redeem(Bank& other, int verificationNum);

	void change(Bank& new_bank, const Bank& other_bank, int account_number);


	void list(const Bank& bank);

};