#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "CorrectInput.h"
#include "StreamIn.h"
#include "DateTime.h"
#include "Schedule.h"
#include "Development.h"
#include "Order.h"
#include "Company.h"

void menu(std::unordered_map <std::string, Company*> companyDict, std::string filename)
{
	int action = 0;
	do
	{
		std::cout << "Enter action (0 - quit, 1 - add company, 2 - add order to a company, 3 - set a completion date of an order / task, 4 - print all companies and orders, 5 - save date, 6 - load data, 7 - make default companies): ";
		action = getIntNumber();
		switch (action)
		{
		case 1:
		{
			Company* newComp = new Company();
			bool flag = 0;
			do
			{
				std::cin >> *newComp;
				//newComp->getConsole();
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
			int flag = 2;
			std::unordered_map <std::string, Company*>::iterator someComp;
			do
			{
				std::cout << "Enter name of a company you want to make an order for: ";
				std::string name;
				std::getline (std::cin, name);
				someComp = companyDict.find(name);
				if (someComp == companyDict.end())
				{
					std::cout << "Couldn't find this company. Wrong name. Quit - 0, Retry - default: ";
					flag = getIntNumber();
					if (flag != 0)
						flag = 1;
				}
			} while (flag == 1);
			if (flag == 0)
				break;
			Order* newOrder = new Order();
			newOrder->getConsole();
			someComp->second->addOrder(newOrder);
			break;
		}
		case 3:
		{
			int flag = 2;
			std::unordered_map <std::string, Company*>::iterator someComp;
			do
			{
				std::cout << "Enter name of a company you work for: ";
				std::string name;
				std::getline(std::cin, name);
				someComp = companyDict.find(name);
				if (someComp == companyDict.end())
				{
					std::cout << "Couldn't find this company. Wrong name. Quit - 0, Retry - default: ";
					flag = getIntNumber();
					if (flag != 0)
						flag = 1;
				}
			} while (flag == 1);
			if (flag == 0)
				break;
			std::string orderName;
			std::cout << "Enter an order name: ";
			getline(std::cin, orderName);

			std::cout << "Have you finished an order? 0 - No, 1 - Yes: ";
			bool hasFinished = getBool();
			if (hasFinished)
			{
				someComp->second->setOrderCompleted(orderName);
			}
			else
			{
				someComp->second->setTaskCompleted(orderName);
			}
			break;
		}
		case 4:
		{
			if (companyDict.empty())
				std::cout << "No data stored";
			for (auto it = companyDict.begin(); it != companyDict.end(); it++)
			{
				std::cout  << *(it->second);
			}
			break;
		}
		case 5:
		{
			std::ofstream out(filename, std::ofstream::binary);
			for (std::unordered_map<std::string, Company*>::iterator it = companyDict.begin(); it != companyDict.end(); it++)
			{
				out << (char)6;
				(*it).second->toStream(out);
			}
			out.close();
			break;
		}
		case 6:
		{
			companyDict.clear();
			std::ifstream in(filename, std::ifstream::binary);
			while (in.get() == 6)
			{
				Company* someComp = new Company();
				someComp->fromStream(in);
				companyDict.try_emplace(someComp->getName(), someComp);
			}
			break;
		}
		case 7:
		{
			std::unordered_map<std::string, Company*>::iterator it;
			Company* someComp = new Company(*(companyDict.begin()->second));
			for (it = companyDict.begin(); it != companyDict.end(); it++)
			{
				it->second = someComp;
			}
			for (it = companyDict.begin(); it != companyDict.end(); it++)
			{
				std::cout << it->first << "\n";
			}
			break;
		}
		}
	} while (action != 0);
}

int main()
{
	std::unordered_map <std::string, Company*> companyDict;
	std::string filename = "C:/Users/Лаврентий Гусев/source/repos/Goose6/Goose6/Goose6Data.bin";
	menu(companyDict, filename);
	return 0;
}