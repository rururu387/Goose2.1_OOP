#pragma once

class FIO
{
	std::string secondName;				//AAAAA!!!
	std::string name;
	std::string patronymic;

public:
	FIO(int var = 0);
	FIO(std::string _secondName, std::string _name, std::string _patronymic);
	FIO(FIO &someFIO);
	void setSecondName(std::string _secondName);
	std::string getSecondName();
	void setName(std::string _name);
	std::string getName();
	void setPatronymic(std::string _patronymic);
	std::string getPatronymic();
};

void FIO::setSecondName(std::string _secondName)
{
	this->secondName = _secondName;
}

std::string FIO::getSecondName()
{
	return this->secondName;
}

void FIO::setName(std::string _name)
{
	this->name = _name;
}

std::string FIO::getName()
{
	return this->name;
}

void FIO::setPatronymic(std::string _patronymic)
{
	this->patronymic = _patronymic;
}

std::string FIO::getPatronymic()
{
	return this->patronymic;
}

FIO::FIO(int var)
{
	if (var == 0)
	{
		secondName = "";
		name = "";
		patronymic = "";
	}
	else if (var == 1)
	{
		std::string _str;
		std::cout << "Enter second name: ";
		std::getline(std::cin, _str);
		secondName = _str;
		std::cout << "Enter name: ";
		std::getline(std::cin, _str);
		name = _str;
		std::cout << "Enter patronym: ";
		std::getline(std::cin, _str);
		patronymic = _str;
	}
}

FIO::FIO(std::string _secondName, std::string _name, std::string _patronymic)
{
	secondName = _secondName;
	name = _name;
	patronymic = _patronymic;
}

FIO::FIO(FIO&someFIO)
{
	secondName = someFIO.secondName;
	name = someFIO.name;
	patronymic = someFIO.patronymic;
}