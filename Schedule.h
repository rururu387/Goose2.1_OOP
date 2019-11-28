#pragma once

class Schedule
{
	std::string name;
	DateTime* dateSch;
	DateTime* dateFact;
	bool dateFactIsInitialized;
public:
	Schedule(std::string _name, DateTime _dateSch, DateTime _dateFact);
	Schedule(std::string _name, DateTime _dateSch);
	Schedule();
	~Schedule() { delete dateSch; delete dateFact; };
	std::string getName() { return name; };
	DateTime getDateSch() { return *dateSch; };
	std::pair <bool, DateTime> getDateFact();
	void initializeDateFact(DateTime* someDate);
	void setName(std::string _name) { name = _name; };
	void setDateSch(DateTime _dateSch);
	void setDateFact(DateTime _dateFact);
	//void getConsoleNoname(int tabAm);
	void getConsole(int tabAm);
	//DateTime* getDateConsole(int tabAm);
	std::string toString();
	void toStream(std::ofstream& out);
	void fromStream(std::ifstream& in);
};

void Schedule::fromStream(std::ifstream& in)
{
	name = getStringFromStream(in, (char)5);
	char a = in.get();
	if (a == '0')
		dateFactIsInitialized = false;
	else if (a == '1')
		dateFactIsInitialized = true;
	else
		throw ("Data was corrupted");
	dateSch->fromStream(in);
	dateFact->fromStream(in);
}

void Schedule::toStream(std::ofstream& out)
{
	//std::string str = "";
	//str += name + '\n' + dateSch->toString() + '\n' + dateFact->toString() + '\n' + std::to_string(dateFactIsInitialized) + '\n';
	out << name.c_str() << (char)5;
	if (dateFactIsInitialized)
		out << '1';
	else
		out << '0';
	dateSch->toStream(out);
	dateFact->toStream(out);
	//return str;
}

void Schedule::initializeDateFact(DateTime* someDate)
{
	dateFact = someDate;
	dateFactIsInitialized = true;
}

std::pair <bool, DateTime> Schedule::getDateFact()
{
	if (dateFactIsInitialized)
		return std::pair <bool, DateTime> (true, *dateFact);
	return std::pair <bool, DateTime>(false, *dateFact);
}

std::string Schedule::toString()
{
	std::string str = "";
	str += "Scheduled date ";
	if (dateSch->isCorrect())
		str += dateSch->toString();
	else
		str += dateSch->Date::toString();
	if (this->getDateFact().first)
	{
		str += "\tJob was completed at: ";
		if (dateFact->isCorrect())
			str += dateFact->toString();
		else
			str += dateFact->Date::toString();
		str += '\n';
	}
	else
	{
		str += "\tIsn't done yet\n";
	}
	return str;
}

std::string tabInsert(int a)
{
	std::string str = "";
	for (int i = 0; i < a; i++)
		str += "\t";
	return str;
}

DateTime* getDateConsole(int tabAm)
{
	int temp;
	std::string str = tabInsert(tabAm);
	std::cout << str + "\tSet date type. Shall I store both: date and time or date only?\n";
	do
	{
		std::cout << str + "\tPlease, enter one of theese: 1 - date, 2 - date and time: ";
		temp = getIntNumber();
	} while (temp <= 0 || temp >= 3);
	bool flag = 0;
	DateTime* newDate = new DateTime(1, 1, 1);
	switch (temp)
	{
	case 1:
	{
		newDate->Date::getConsole();
		break;
	}
	case 2:
	{
		newDate->getConsole();
		break;
	}
	}
	return newDate;
}

void Schedule::getConsole(int tabAm)
{
	std::string str = tabInsert(tabAm);
	std::cout << str + "Enter it's name: ";
	//std::cin >> name;
	std::getline(std::cin, name);
	//std::cin.ignore();
	std::cout << str + "Enter scheduled date to this task to be completed\n";
	delete dateSch;
	dateSch = getDateConsole(tabAm);
	std::cout << tabInsert(tabAm) + "Has it been done yet? Yes/No: ";
	std::string temp;
	std::cin >> temp;
	std::cin.ignore();
	if (temp.compare("Yes") == 0 || temp.compare("yes") == 0 || temp.compare("Y") == 0)
	{
		std::cout << tabInsert(tabAm) + "Enter when the job was done\n";
		dateFact = getDateConsole(tabAm);
		dateFactIsInitialized = true;
	}
}

void Schedule::setDateSch(DateTime _dateSch)
{
	delete dateSch;
	dateSch = new DateTime(_dateSch);
}

void Schedule::setDateFact(DateTime _dateFact)
{
	delete dateFact;
	dateFact = new DateTime(_dateFact);
	dateFactIsInitialized = true;
}

Schedule::Schedule()
{
	name = "";
	dateSch = new DateTime(2019, 11, 11, -1, -1, -1);
	dateFact = new DateTime(2019, 11, 11, -1, -1, -1);
	dateFactIsInitialized = false;
}

Schedule::Schedule(std::string _name, DateTime _dateSch)
{
	name = _name;
	this->setDateSch(_dateSch);
	dateFactIsInitialized = true;
}

Schedule::Schedule(std::string _name, DateTime _dateSch, DateTime _dateFact)
{
	name = _name;
	this->setDateSch(_dateSch);
	this->setDateFact(_dateFact);
	dateFactIsInitialized = true;
}