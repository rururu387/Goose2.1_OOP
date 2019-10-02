#pragma once

typedef class StudentDatabase
{
	std::vector <emp> data;

	void searchDepartment(std::vector <emp> data);
	void addEmployees(std::vector <emp>* data);
	void saveData(std::vector <emp> data);
	void loadData(std::vector <emp>* data);
	std::pair <emp, int> searchEmp(std::vector <emp> data);
	void myRor(std::vector <emp>* data, int min, int max);
	void salarySort(std::vector <emp>* data);
};

void StudentDatabase::searchDepartment(std::vector <emp> data)
{
	int dep;
	std::cout << "Enter the needed department: ";
	std::cin >> dep;
	bool flag = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].getDepartment() == dep)
		{
			printEmp(data[i], i);
			flag = 1;
		}
	}
	if (flag == 0)
		std::cout << "No workers from this department known";
}

/*emp fillEmp()
{
	emp* someEmp = new emp();

	std::cout << "Enter name: ";
	//std::cin.clear();
	std::getline(std::cin, someEmp.name);
	std::cout << "Enter secondName: ";
	std::getline(std::cin, someEmp.fam);
	std::cout << "Enter department: ";
	getIntNumber(&(someEmp.department));
	std::cout << "Enter salary: ";
	getDoubleNumber(&(someEmp.salary));
	return someEmp;
}*/

void StudentDatabase::addEmployees(std::vector <emp>* data)
{
	int amount;
	std::cout << "The amount of employees to add: ";
	amount = getIntNumber();
	//std::cin >> amount;
	//std::cin.ignore(1);

	for (int i = 0; i < amount; i++)
	{
		emp* someEmp = new emp();
		data->push_back(*someEmp);
	}
}

void StudentDatabase::saveData(std::vector <emp> data)
{
	std::ofstream out;
	out.open("H:\database.txt");
	for (int i = 0; i < data.size(); i++)
	{
		if (out.is_open())
		{
			out << i << '\n' << data[i].fio->getName() << '\n' << data[i].fio->getSecondName() << '\n' << data[i].getDepartment() << '\n' << std::setprecision(7) << data[i].getSalary() << '\n';
		}
	}
	out.close();
}

void StudentDatabase::loadData(std::vector <emp>* data)
{
	std::string line;
	std::ifstream in;
	in.open("H:\database.txt");
	emp* someEmp = new emp(1);
	data->push_back(*someEmp);
	//(*data)[0].name = "A";
	if (in.is_open())
	{
		while (getline(in, line))
		{
			int j = line[0] - '0';
			if (j >= data->size())
			{
				for (int i = data->size(); i <= j; i++)
				{
					emp someEmp;
					data->push_back(someEmp);
				}
			}
			getline(in, line);
			(*data)[j].fio->setName(line);
			getline(in, line);
			(*data)[j].fio->setSecondName(line);
			try
			{
				getline(in, line);
				(*data)[j].setDepartment(stringToInt(line));
				getline(in, line);
				(*data)[j].setSalary(stringToDouble(line));
			}
			catch (std::string str)
			{
				std::cout << "Exception: data corrupted: " << str;
			}
		}
	}
	in.close();
}

std::pair <emp, int> StudentDatabase::searchEmp(std::vector <emp> data)
{
	std::string searchedSecondName;
	std::cout << "Print an employee's second name: ";
	std::cin.ignore();
	std::getline(std::cin, searchedSecondName);
	int i = 0;
	for (std::vector <emp> ::iterator it = data.begin(); it < data.end(); it++)
	{
		if (it->fio->getSecondName().compare(searchedSecondName) == 0)
		{
			std::pair <emp, int> swaggyPair(*it, i);
			return swaggyPair;
		}
		i++;
	}
	std::cout << "No such employee\n";
	std::pair <emp, int> swaggyPair(*data.begin(), -1);
	return swaggyPair;
}

void StudentDatabase::myRor(std::vector <emp>* data, int min, int max)
{
	emp t = (*data)[max];
	for (int i = max; i > min; i--)
		(*data)[i] = (*data)[i - 1];
	(*data)[min] = t;
}

void StudentDatabase::salarySort(std::vector <emp>* data)
{
	int len = data->size();
	/*for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if ((*data)[j - 1].salary < (*data)[j].salary)
			{
				emp temp = (*data)[j];
				(*data)[j] = (*data)[j - 1];
				(*data)[j - 1] = temp;
			}
		}
	}*/
	for (int i = 1; i < len; i++)
	{
		int max = i - 1, min = 0;
		while (max != min)
		{
			if ((*data)[(max + min) / 2].getSalary() <= (*data)[i].getSalary())
				if ((max - min) % 2 == 0)
					max -= (max - min) / 2;
				else
					max -= (max - min) / 2 + 1;
			else
				if ((max - min) % 2 == 0)
					min += (max - min) / 2;
				else
					min += (max - min) / 2 + 1;
		}
		if ((*data)[i].getSalary() >= (*data)[max].getSalary())
			myRor(data, max, i);
		/*while ((*data)[i].salary > (*data)[(max + min) / 2].salary || (*data)[i].salary < (*data)[(max + min) / 2 + 1].salary)
		{
			if (max + min / 2 == 0)
				break;
			if ((*data)[i].salary > (*data)[(max + min) / 2].salary)
				if ((max - min) % 2 == 0)
					max -= (max - min) / 2;
				else
					max -= (max - min) / 2 + 1;
			else
				if (max - min % 2 == 0)
					min += (max - min) / 2;
				else
					min += (max - min) / 2 + 1;
		}*/
	}
	std::cout << "Data was sorted\n";
}