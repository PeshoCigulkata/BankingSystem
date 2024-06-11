#pragma once
#include "Account.h"
#include "Bank.h"


class Client : public Account {
private:
	Bank array[1024];

public:
	Client();

	void check_avl()const;

	void open()const {
		//v main moje da se razpishe logikata!
		//samiqt  bank koito sme suzdali prosto uvelichavame size++ i pravim nov akaunt
	}

	void close()const {
		//v main moje da se razpishe logikata!
		//samiqt  bank koito sme suzdali prosto uvelichavame size-- i triem akaunt
	}

	void redeem(Bank& other, int verificationNum);

	void change(Bank& new_bank, const Bank& other_bank, int account_number);


	void list(const Bank& bank);

};