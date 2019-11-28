#pragma once

class Company
{
	std::string name;
	std::vector<Order*> orders;
public:
	void getConsole();
	void addOrder(Order* someOrder);
	std::vector<Order*>::iterator findOrder(std::string nameToFind);
	void setOrderCompleted(std::string orderName);
	void setTaskCompleted(std::string orderName);
	std::string getName() { return name; };
	void setString(std::string _name) { name = _name; };
	Company();
	~Company();
	void toStream(std::ofstream& out);
	std::string toString();
	void fromStream(std::ifstream& in);
};

std::vector<Order*>::iterator Company::findOrder(std::string nameToFind)
{
	std::vector<Order*>::iterator it;
	std::vector<Order*>::reverse_iterator rit;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		if (!std::strcmp((*it)->getSch()->getName().c_str(), nameToFind.c_str()))
		{
			break;
		}
	}
	if (it == orders.end())
	{
		std::cout << "There is no orders with this name\n";
		return orders.end();
	}
	for (rit = orders.rbegin(); rit != orders.rend(); rit++)
	{
		if (!std::strcmp((*rit)->getSch()->getName().c_str(), nameToFind.c_str()))
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
		for (it = orders.begin(); it != orders.end(); it++)
		{
			if (!std::strcmp((*it)->getSch()->getName().c_str(), nameToFind.c_str()))
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
		for (it = orders.begin(); it != orders.end(); it++)
		{
			if (!std::strcmp((*it)->getSch()->getName().c_str(), nameToFind.c_str()))
			{
				num--;
				if (num == 0)
				{
					return it;
				}
			}
			throw("Algorithm error");
			return orders.end();
		}
	}
}

void Company::setOrderCompleted(std::string orderName)
{
	std::vector<Order*>::iterator it = findOrder(orderName);
	if (it == orders.end())
		return;
	DateTime* completionDate = new DateTime(2019, 1, 1);
	std::cout << "Enter date and time when you have completed an order.\n";
	completionDate = getDateConsole(1);
	(*it)->getSch()->setDateFact(*completionDate);
}

void Company::setTaskCompleted(std::string orderName)
{
	std::vector<Order*>::iterator it = findOrder(orderName);
	if (it == orders.end())
		return;
	std::string taskName;
	std::cout << "Enter task name: ";
	std::getline(std::cin, taskName);
	(*it)->getDevelopment()->setTaskCompleted(taskName);
}

void Company::fromStream(std::ifstream& in)
{
	if (in.get() != (char)4)
		throw ("Data file is corrupted");
	name = getStringFromStream(in, (char)5);
	char a = in.get();
	while (a == (char)4)
	{
		Order* someOrder = new Order();
		someOrder->fromStream(in);
		orders.push_back(someOrder);
		a = in.get();
	}
	in.unget();
}

void Company::toStream(std::ofstream& out)
{
	out << (char)4 << name.c_str() << (char)5;
	for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); it++)
	{
		out << (char)4;
		(*it)->toStream(out);
	}
}

void Company::addOrder(Order* someOrder)
{
	orders.push_back(someOrder);
}

std::string Company::toString()
{
	std::string str = "Company: " + name + "\n";
	for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); it++)
	{
		str += (*it)->toString() + "\n";
	}
	return str;
}

Company::Company()
{
	name = "";
}

Company::~Company()
{
	for (auto it = orders.begin(); it != orders.end(); it++)
		delete *it;
}

void Company::getConsole()
{
	std::cout << "Enter company name: ";
	//std::cin >> name;
	std::getline(std::cin, name);
	int n;
	std::cout << "Enter amount of company's orders: ";
	std::cin >> n;
	std::cin.ignore();
	for (int i = 0; i < n; i++)
	{
		std::cout << "\tOrder " + std::to_string(i + 1) + ":\n";
		Order* someOrder = new Order();
		someOrder->getConsole();
		orders.push_back(someOrder);
	}
}