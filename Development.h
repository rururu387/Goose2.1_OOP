#pragma once

//int Development::amount = 0;	Not to forget =)

class Development
{
	std::string name;
	int stageAmount;
	std::vector <Schedule*> stageSch;
public:
	void getConsole();
	std::string getName() { return name; };
	void setName(std::string _name) { name = _name; };
	int getStageAm() { return stageAmount; };
	void setStageAm(int _stageAmount) { stageAmount = _stageAmount; };
	std::vector <Schedule*> getStageSch() { return stageSch; };
	std::vector<Schedule*>::iterator findTask(std::string nameToFind);
	void setTaskCompleted(std::string taskName);
	Development();
	Development(std::string _name, int _stageAmount, Schedule* _stageSch[]);
	~Development();
	std::string toString();
	void fromStream(std::ifstream& in);
	void toStream(std::ofstream& out);
};

std::vector<Schedule*>::iterator Development::findTask(std::string nameToFind)
{
	std::vector<Schedule*>::iterator it;
	std::vector<Schedule*>::reverse_iterator rit;
	for (it = stageSch.begin(); it != stageSch.end(); it++)
	{
		if (!std::strcmp((*it)->getName().c_str(), nameToFind.c_str()))
		{
			break;
		}
	}
	if (it == stageSch.end())
	{
		std::cout << "There is no orders with this name\n";
		return stageSch.end();
	}
	for (rit = stageSch.rbegin(); rit != stageSch.rend(); rit++)
	{
		if (!std::strcmp((*rit)->getName().c_str(), nameToFind.c_str()))
		{
			break;
		}
	}
	if (*it == *rit)
	{
		return it;
	}
	else
	{
		std::cout << "There are more thane one orders with this name:\n";
		int amount = 0;
		for (it = stageSch.begin(); it != stageSch.end(); it++)
		{
			if (!std::strcmp((*it)->getName().c_str(), nameToFind.c_str()))
			{
				std::cout << amount + 1 + ':\t';
				std::cout << (*it)->toString();
				amount++;
			}
		}
		int num = 1;
		std::cout << "Enter a number of the one you have worked for: ";
		do
		{
			if (num != 1)
				std::cout << "Enter a number between 1 and " + std::to_string(amount);
			num = getIntNumber();
		} while (num < 1 || num > amount);
		for (it = stageSch.begin(); it != stageSch.end(); it++)
		{
			if (!std::strcmp((*it)->getName().c_str(), nameToFind.c_str()))
			{
				num--;
				if (num == 0)
				{
					return it;
				}
			}
			throw("Algorithm error");
			return stageSch.end();
		}
	}
}

void Development::setTaskCompleted(std::string taskName)
{
	std::vector<Schedule*>::iterator it = findTask(taskName);
	DateTime* completionDate = new DateTime(2019, 1, 1);
	std::cout << "Enter date and time when you have completed an order";
	completionDate = getDateConsole(1);
	(*it)->setDateFact(*completionDate);
}

void Development::fromStream(std::ifstream& in)
{
	name = getStringFromStream(in, (char)5);
	stageAmount = getIntFromStream(in, (char)5);
	while (in.get() == (char)5)
	{
		Schedule* tmpSch = new Schedule();
		tmpSch->fromStream(in);
		stageSch.push_back(tmpSch);
	}
	in.unget();
}

void Development::toStream(std::ofstream& out)
{
	//std::string str = "";
	//str += name + '\n' + std::to_string(stageAmount) + '\n';
	out << name.c_str() << (char)5 << stageAmount << (char)5;
	for (std::vector<Schedule*>::iterator it = stageSch.begin(); it != stageSch.end(); it++)
	{
		//str += (*it)->toStream();
		out << (char)5;
		(*it)->toStream(out);
	}
	//return str;
}

std::string Development::toString()
{
	std::string str = name + "\n\tStages amount: " + std::to_string(stageAmount) + "\n";
	for (int i = 0; i < stageAmount; i++)
	{
		str += "\t\t-Stage name: " + stageSch[i]->getName() + "\n\t\t\t*Stage status: " + stageSch[i]->toString();
	}
	return str;
}

void Development::getConsole()
{
	std::cout << "Enter project name: ";
	//std::cin >> name;
	std::getline(std::cin, name);
	//std::cin.ignore();
	std::cout << "\t\t\tEnter amount of tasks to do: ";
	stageAmount = getIntNumber();
	for (int i = 0; i < stageAmount; i++)
	{
		std::cout << "\t\t\tEnter info about " + std::to_string(i + 1) << "th task to do.\n";
		Schedule* tempSched = new Schedule();
		tempSched->getConsole(4);
		stageSch.push_back(tempSched);
	}
}

Development::Development(std::string _name, int _stageAmount, Schedule* _stageSch[])
{
	name = _name;
	stageAmount = _stageAmount;
	for (int i = 0; i < stageAmount; i++)
	{
		stageSch.push_back(_stageSch[i]);
	}
}

Development::Development()
{
	name = "Goose task";
	stageAmount = 1;
}

Development::~Development()
{
	for (auto it = stageSch.begin(); it != stageSch.end(); it++)
	{
		delete *it;
	}
}