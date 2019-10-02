#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

#include "CorrectInput.h"
#include "myFIO.h"
#include "WorkerClass.h"
#include "WorkerDatabase.h"

/*typedef struct Employee
{
	std::string secondName; 		//Работник: Фамилия
	std::string name;				//Имя
	int department;					//Отдел
	double salary;					//Оклад
} emp;*/

void menu(wd data, std::string fileName)
{
	int action = 0;
	do
	{
		std::cout << "Enter needed action. Quit - 0. Add employees - 1. Print emplyee list - 2. Search for an Employee - 3. List of a department employees - 4. Sort in salary order - 5. Save data - 6. Load data - 7. Clear data - 8: ";
		action = getIntNumber();
		//std::cin >> action;
		//std::cin.ignore();
		switch (action)
		{
		default:
			std::cout << "Goose Gogha\n";
			break;
		case 0:
			data.saveData(fileName);

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
			data.searchDepartment();
			break;
		case 5:
			data.salarySort();
			break;
		case 6:
			if (data.size() == 0)
				std::cout << "Database is empty. Nothig will be stored";
			data.saveData(fileName);
			break;
		case 7:
			while (data.size() != 0)
				data.pop_back();
			data.loadData(fileName);
			break;
		case 8:
			while (data.size() != 0)
				data.pop_back();
			break;
		}
	} while (action != 0);
}

/*void equivEmp(emp* data, int i, emp someEmp)
{
	data[i].department = someEmp.department;
	data[i].fio.setName(someEmp.fio.getName());
	data[i].salary = someEmp.salary;
	data[i].fio.setSecondName(someEmp.fio.getSecondName());
}*/

int main()
{
	std::string fileName = "C:/Users/Лаврентий Гусев/Олег/МИЭТ/Информатика/Goose2_OOP/Goose2.1_OOP/database.txt";
	wd data;
	menu(data, fileName);

	return 0;
}