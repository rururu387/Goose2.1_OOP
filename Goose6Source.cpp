#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
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
		std::cout << "Enter action (0 - quit, 1 - add company, 2 - add order to a company, 3 - print all companies and orders, 4 - save date, 5 - load data): ";
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
				std::getline (std::cin, name);
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
		case 4:
		{
			std::ofstream out("C:/Users/Лаврентий Гусев/Олег/МИЭТ/Информатика/C++ (OOP)/Files/Goose6Data.bin", std::ofstream::binary);
			for (std::unordered_map<std::string, Company*>::iterator it = companyDict.begin(); it != companyDict.end(); it++)
			{
				out << (char)4;
				(*it).second->toStream(out);
				/*const char* tmpstr = (*it).second->toFile().c_str();
				out.write(tmpstr, sizeof (tmpstr));
				char a = 4;
				out.write(&a, sizeof(char));*/
			}
			out.close();
		}
		case 5:
		{
			companyDict.clear();
			std::ifstream in("C:/Users/Лаврентий Гусев/Олег/МИЭТ/Информатика/C++ (OOP)/Files/Goose6Data.bin", std::ifstream::binary);
			while (in.get() == 4)
			{
				Company* someComp = new Company();
				someComp->fromStream(in);
				companyDict.try_emplace(someComp->getName(), someComp);
			}
			/*char* a;
			std::string str = "";
			str.resize(100);
			do
			{
				in.read(a, sizeof(in));
				str += a;
			}while (*a != in.eof());

			str.shrink_to_fit();
			in.close();

			Company* someComp = new Company();
			int fPos = str.find(4);
			while (fPos != std::string::npos)
			{
				std::string substr = str.substr(0, str.find(4));
				str.erase(0, str.find(4));
				someComp->fromFile(substr);
				companyDict.try_emplace(std::pair<std::string, Company*>(someComp->getName(), someComp));
				fPos = str.find(4);*/
			//}


			/*for (int i = 0; i < str.size(); i++)
			{
				Company* someCmp = new Company();
				std::string substrtmp = str.;
					companyDict.try_emplace(std::pair<std::string, Company*>());
			}*/
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