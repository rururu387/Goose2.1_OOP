#include "CorrectInput.h"
#include "myFIO.h"
#include "WorkerClass.h"
#include "StudentDatabase.h"
#include <vector>

/*typedef struct Employee
{
	std::string secondName; 		//Работник: Фамилия
	std::string name;				//Имя
	int department;					//Отдел
	double salary;					//Оклад
} emp;*/



void printEmp(emp someEmp, int i)
{
	std::cout << i << ": ";
	std::cout << someEmp.fio->getName() << '\t';
	std::cout << someEmp.fio->getSecondName() << '\t';
	std::cout << someEmp.getDepartment() << '\t';
	printf_s("%lf\n", someEmp.getSalary());
	//printf ("%s\t%s\t%d\t%lf", data[i]->name, data[i]->secondName, data[i]->department, data[i]->salary);
}

void printEmpList(std::vector <emp> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		printEmp(data[i], i);
	}
}

void menu(std::vector <emp> data)
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
			data.saveData();

			while (data[0].getCount() != 0)
				data.pop_back();
			return;
		case 1:
			data.addEmployees();
			break;
		case 2:
			printEmpList(data);
			break;
		case 3:
		{
			std::pair <emp, int> swaggyPair = data.searchEmp();
			if (swaggyPair.second != -1)
				printEmp(swaggyPair.first, swaggyPair.second);

			break;
		}
		case 4:
			data.searchDepartment();
			break;
		case 5:
			data.salarySort();
			break;
		case 6:
			data.saveData();
			break;
		case 7:
			while (data[0].getCount() != 0)
				data.pop_back();

			data.loadData();
			break;
		case 8:
			while (data[0].getCount() != 0)
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
	menu(data);
	return 0;
}