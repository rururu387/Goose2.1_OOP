#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

#include "CorrectInput.h"
#include "myFIO.h"
#include "baseWorker.h"
#include "WorkerClass.h"
#include "WorkerClass2.h"
#include "WorkerDatabaseInteract.h"

/*typedef struct Employee
{
	std::string secondName; 		//Работник: Фамилия
	std::string name;				//Имя
	int department;					//Отдел
	double salary;					//Оклад
} emp;*/

void menu(wd data, std::string fileName)
{
	/*FIO someFIO;
	int department;
	double salary;
	std::cin >> someFIO >> department >> salary;
	++data;
	++data;
	++data;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == someFIO)
			std::cout << "!!!111!!!\n";
	}
	data.push_back(someFIO, department, salary);
	++data;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == someFIO)
			std::cout << "!!!222!!!\n";
	}
	
	wd data2;
	std::cin >> department;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].getDepartment() == department)
		{
			try
			{
				Worker1 someWorker;
				someWorker = (Worker1)data[i];
				data2.push_back(someWorker);
			}
			catch (std::string str)
			{}
		}
	}
	data2.printWorkerList();
	data2.saveDataBin(fileName + ".txt");
	data.DDB();
	data2.DDB();
	int action = 0;
	do
	{
		std::cout << "Enter needed action. Quit - 0. Add employees - 1. Print emplyee list - 2. Search for an Employee - 3. List of a department employees - 4. Sort in salary order - 5. Save data - 6. Load data - 7. Save data in bin file - 8. Load data from bin file - 9. Clear data - 10: ";
		action = getIntNumber();
		//std::cin >> action;
		//std::cin.ignore();
		switch (action)
		{
		default:
			std::cout << "Goose Gogha\n";
			break;
		case 0:
			data.saveData(fileName + ".txt");

			while (data.size() != 0)
				data.pop_back();
			return;
		case 1:
			data.addEmployees();
			break;
		case 2:
			data.printWorkerList();
			break;
		case 3:
		{
			std::pair <emp, int> swaggyPair = data.searchEmp();
			if (swaggyPair.second != -1)
				swaggyPair.first.printWorker(swaggyPair.second);

			break;
		}
		case 4:
			searchDepartment(data);
			break;
		case 5:
			data.salarySort();
			break;
		case 6:
			if (data.size() == 0)
				std::cout << "Database is empty. Nothig will be stored";
			data.saveData(fileName + ".txt");
			break;
		case 7:
			while (data.size() != 0)
				data.pop_back();
			data.loadData(fileName + ".txt");
			break;
		case 8:
			if (data.size() == 0)
				std::cout << "Database is empty. Nothig will be stored";
			data.saveDataBin(fileName + ".bin");
			break;
		case 9:
			while (data.size() != 0)
				data.pop_back();
			data.loadDataBin(fileName + ".bin");
			break;
		case 10:
			while (data.size() != 0)
				data.pop_back();
			break;
		}
	} while (action != 0);*/
	char a;
	std::cin >> a;
}

/*void equivEmp(emp* data, int i, emp someEmp)
{
	data[i].department = someEmp.department;
	data[i].fio.setName(someEmp.fio.getName());
	data[i].salary = someEmp.salary;
	data[i].fio.setSecondName(someEmp.fio.getSecondName());
}*/

//Bug in loadBin
int main()
{
	std::string fileName = "H:\Goose3_OOP/employeeProject";
	wd data;
	menu(data, fileName);

	return 0;
}