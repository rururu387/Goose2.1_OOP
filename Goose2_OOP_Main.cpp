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
	} while (action != 0);
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
	std::string fileName = "C:/Users/Лаврентий Гусев/Олег/МИЭТ/Информатика/Goose2_OOP/Goose2.1_OOP/database";
	wd data;
	menu(data, fileName);

	return 0;
}