#pragma once
#include <string>
using namespace std;

class Customer
{
protected:
	string login;
	string password;
	int role = -1;

public:
	Customer(const string& _login, const string& _password) : login(_login), password(_password) {}
	Customer()
	{
		login = "";
		password = "";
	}
	~Customer() {}

	// геттеры
	string get_login() const
	{
		return login;
	}
	string get_password() const
	{
		return password;
	}

	// сеттеры
	void set_login(const string& login)
	{
		this->login = login;
	}
	void set_password(const string& password)
	{
		this->password = password;
	}
	virtual void set_role(const int& _role) {}

	bool operator <(const Customer& customer) const
	{
		return login < customer.login;
	}

	bool operator >(const Customer& customer) const
	{
		return login > customer.login;
	}

	bool operator ==(const Customer& customer) const
	{
		return login == customer.login;
	}

	/*virtual string to_string() { return ""; }*/

	virtual int get_role() const { return this->role; }

	virtual void show() {}
};