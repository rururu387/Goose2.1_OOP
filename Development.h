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
	Development();
	Development(std::string _name, int _stageAmount, Schedule* _stageSch[]);
	~Development();
	std::string toString();
};

std::string Development::toString()
{
	std::string str = name + "\n\tStages amount: " + std::to_string(stageAmount) + "\n";
	for (int i = 0; i < stageAmount; i++)
	{
		str += "\t\t-Stage name: " + name + "\n\t\t-Stage status: " + stageSch[i]->toString();
	}
	return str;
}

void Development::getConsole()
{
	std::cout << "Enter project name: ";
	std::cin >> name;
	std::cin.ignore();
	std::cout << "\t\t\tEnter amount of tasks to do: ";
	std::cin >> stageAmount;
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
	stageSch.push_back(new Schedule[stageAmount]);
}

Development::~Development()
{
	for (auto it = stageSch.begin(); it != stageSch.end(); it++)
	{
		delete *it;
	}
}