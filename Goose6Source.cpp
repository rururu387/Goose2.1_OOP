#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CorrectInput.h"
#include "DateTime.h"
#include "Schedule.h"
#include "Development.h"
#include "Order.h"
#include "Company.h"

void menu(std::unordered_map <std::string, Company*> companyDict)
{
	int action = 0;
	do
	{
		std::cout << "Enter action (0 - quit, 1 - add company, 2 - add order to a company, 3 - print all companies and orders): ";
		action = getIntNumber();
		switch (action)
		{
		case 1:
		{
			Company* newComp = new Company();
			bool flag = 0;
			do
			{
				newComp->getConsole();
				if (!companyDict.try_emplace(newComp->getName(), newComp).second)
				{
					std::cout << "Couldn't add a company. Remember: you can't add two companies with the same name";
					flag = 1;
				}
			} while (flag);
			break;
		}
		case 2:
		{
			bool flag = 0;
			std::unordered_map <std::string, Company*>::iterator someComp;
			do
			{
				std::cout << "Enter name of a company you want to make an order for: ";
				std::string name;
				std::cin >> name;
				someComp = companyDict.find(name);
				if (someComp == companyDict.end())
				{
					std::cout << "Couldn't find this company. Wrong name. Retry: ";
					flag = 1;
				}
			} while (flag);
			Order* newOrder = new Order();
			newOrder->getConsole();
			someComp->second->addOrder(newOrder);
			break;
		}
		case 3:
		{
			for (auto it = companyDict.begin(); it != companyDict.end(); it++)
			{
				std::cout << it->second->toString();
			}
			break;
		}
		}
	} while (action != 0);
}

int main()
{
	std::unordered_map <std::string, Company*> companyDict;
	menu(companyDict);
	return 0;
}