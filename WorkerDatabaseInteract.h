#pragma once

typedef class WorkerDatabaseInteract
{
	std::vector <emp> data;

public:
	friend void searchDepartment(WorkerDatabaseInteract _data);
	void addEmployees();
	void saveData(std::string fileName);
	void loadData(std::string fileName);
	void saveDataBin(std::string fileName);
	void loadDataBin(std::string fileName);
	std::pair <emp, int> searchEmp();
	void myRor(int min, int max);
	void salarySort();
	emp operator [] (int i);
	void printWorkerList();
	void pop_back();
	int size();
}wd;

int WorkerDatabaseInteract::size()
{
	return data.size();
}

void WorkerDatabaseInteract::pop_back()
{
	data.pop_back();
}

emp WorkerDatabaseInteract::operator [] (int i)
{
	if (i >= 0 && i <= data.size())
	{
		return data[i];
	}
	else
	{
		std::string str = "Tryed to access data out of bounds";
		throw (str);
	}
}

void searchDepartment(WorkerDatabaseInteract _data)
{
	int dep;
	std::cout << "Enter the needed department: ";
	std::cin >> dep;
	bool flag = 0;
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].getDepartment() == dep)
		{
			_data[i].printWorker(i);
			flag = 1;
		}
	}
	if (flag == 0)
		std::cout << "No workers from this department known\n";
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

void WorkerDatabaseInteract::addEmployees()
{
	int amount;
	std::cout << "The amount of employees to add: ";
	amount = getIntNumber();
	//std::cin >> amount;
	//std::cin.ignore(1);

	for (int i = 0; i < amount; i++)
	{
		emp* someEmp = new emp(1);
		data.push_back(*someEmp);
	}
}

void WorkerDatabaseInteract::saveData(std::string fileName)
{
	std::ofstream out;
	try
	{
		out.open(fileName);
		if (out.goodbit)
		{
			std::string str = "Couldn't save data. Unable to open " + fileName + "\n";
			throw(str);
		}
		for (int i = 0; i < data.size(); i++)
		{
			if (out.is_open())
			{
				out << i << '\n' << data[i].fio->getName() << '\n' << data[i].fio->getSecondName() << "\n" << data[i].fio->getPatronymic() << '\n' << data[i].getDepartment() << '\n' << std::setprecision(7) << data[i].getSalary() << '\n';
			}
		}
		out.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to save in file. " << str << ", maybe you forgot to add employees?\n";
	}
}

void WorkerDatabaseInteract::loadData(std::string fileName)
{
	std::string line;
	std::ifstream in;
	try
	{
		in.open(fileName);
		if (in.goodbit)
		{
			std::string str = "Check if a file exists. Unable to open " + fileName + ". Maybe you saved in the other format?\n";
			throw(str);
		}
		emp* someEmp = new emp(0);
		data.push_back(*someEmp);
		//(*data)[0].name = "A";
		if (in.is_open())
		{
			while (getline(in, line))
			{
				int j = line[0] - '0';
				if (j >= data.size())
				{
					for (int i = data.size(); i <= j; i++)
					{
						data.push_back(*someEmp);
					}
				}
				getline(in, line);
				data[j].fio->setName(line);
				getline(in, line);
				data[j].fio->setSecondName(line);
				getline(in, line); 
				data[j].fio->setPatronymic(line);
				getline(in, line);
				data[j].setDepartment(stringToInt(line));
				getline(in, line);
				data[j].setSalary(stringToDouble(line));
			}
		}
		//delete someEmp;
		in.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to load a file. " << str << "\n";
	}
}

void WorkerDatabaseInteract::saveDataBin(std::string fileName)
{
	std::ofstream out (fileName, std::ios::binary | std::ios::out);
	try
	{
		if (!out.is_open())
		{
			std::string str = "Couldn't save data. Unable to open " + fileName;
			throw(str);
		}
		for (int i = 0; i < data.size(); i++)
		{
			if (out.is_open())
			{
				std::string str1 = std::to_string(data[i].getDepartment());
				std::string str2 = std::to_string(data[i].getSalary());
				//out << i << data[i].fio->getSecondName() << " " << data[i].fio->getName() << " " << data[i].fio->getPatronymic() << " " << data[i].getDepartment() << std::setprecision(7) << data[i].getSalary();
				out << i << data[i].fio->getSecondName() << " " << data[i].fio->getName() << " " << data[i].fio->getPatronymic() << " " << str1 << " " << str2 << "\n";
			}
		}
		out.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to save in a binary file. " << str << ", maybe you forgot to add employees?\n";
	}
}

void WorkerDatabaseInteract::loadDataBin(std::string fileName)
{
	std::string line;
	std::ifstream in;
	try
	{
		in.open(fileName);
		if (!in.is_open())
		{
			std::string str = "File is not opened. Check if it exists. Unable to open " + fileName;
			throw(str);
		}
		emp* someEmp = new emp(0);
		if (in.is_open())
		{
			int i;
			std::string name, secondName, patronymic, department, salary;
			in >> i >> secondName >> name >> patronymic >> department >> salary;
			someEmp->fio->setSecondName(secondName);
			someEmp->fio->setName(name);
			someEmp->fio->setPatronymic(patronymic);
			someEmp->setDepartment(std::stoi(department));
			someEmp->setSalary(std::stod(salary));
		}
		data.push_back(*someEmp);
		in.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to load from a binary file. " << str;
	}
}

std::pair <emp, int> WorkerDatabaseInteract::searchEmp()
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

void WorkerDatabaseInteract::myRor(int min, int max)
{
	emp t = data[max];
	for (int i = max; i > min; i--)
		data[i] = data[i - 1];
	data[min] = t;
}

void WorkerDatabaseInteract::salarySort()
{
	int len = data.size();
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
			if (data[(max + min) / 2].getSalary() <= data[i].getSalary())
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
		if (data[i].getSalary() >= data[max].getSalary())
			myRor(max, i);
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

void WorkerDatabaseInteract::printWorkerList()
{
	if (data.size() == 0)
		std::cout << "No data stored";
	for (int i = 0; i < data.size(); i++)
	{
		data[i].printWorker(i);
	}
}