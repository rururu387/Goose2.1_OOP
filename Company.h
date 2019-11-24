#pragma once

class Company
{
	std::string name;
	std::vector<Order*> orders;
public:
	void getConsole();
	void addOrder(Order* someOrder);
	std::string getName() { return name; };
	void setString(std::string _name) { name = _name; };
	Company();
	~Company();
	void toStream(std::ofstream& out);
	std::string toString();
	void fromStream(std::ifstream& in);
};

void Company::fromStream(std::ifstream& in)
{
	in >> name;
	while (in.get() == (char)4)
	{
		Order* someOrder = new Order();
		someOrder->fromStream(in);
		orders.push_back(someOrder);
	}
}

void Company::toStream(std::ofstream& out)
{
	/*std::string str = "";
	str += name + "\n";*/
	out << name.c_str();
	for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); it++)
	{
		//str += (*it)->toFile();
		out << (char)4;
		(*it)->toStream(out);
	}
	//return str;
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