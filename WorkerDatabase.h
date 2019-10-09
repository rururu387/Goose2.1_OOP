#pragma once

typedef class WorkerDatabase
{
	std::vector <emp> data;

public:
	friend void searchDepartment(WorkerDatabase _data);
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

int WorkerDatabase::size()
{
	return data.size();
}

void WorkerDatabase::pop_back()
{
	data.pop_back();
}

emp WorkerDatabase::operator [] (int i)
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

void searchDepartment(WorkerDatabase _data)
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

void WorkerDatabase::addEmployees()
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

void WorkerDatabase::saveData(std::string fileName)
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

void WorkerDatabase::loadData(std::string fileName)
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

std::string intToString(int a)
{
	std::string str = "";
	int upA = 1;
	while (upA < a)
	{
		upA *= 10;
	}
	upA = upA / 10;
	while (a > 0)
	{
		str += floor (a / upA) + '0';
		a -= floor(a / upA) * upA;
		upA /= 10;
	}
	return str;
}

std::string doubleToString(double a)
{
	std::string str = "";
	int whole = floor(a);
	double fractional = (a - floor(a));
	while (fractional - floor(fractional) > 0.001)
	{
		fractional *= 10;
	}
	str += intToString(whole) + "." + intToString(floor (fractional));
	return str;
}

void WorkerDatabase::saveDataBin(std::string fileName)
{
	std::ofstream out (fileName, std::ios::binary | std::ios::out);
	try
	{
		if (out.goodbit)
		{
			std::string str = "Couldn't save data. Unable to open " + fileName;
			throw(str);
		}
		for (int i = 0; i < data.size(); i++)
		{
			if (out.is_open())
			{
				//fwrite(&(data[i].fio->getSecondName()), sizeof(char), data[i].fio->getSecondName().size(), );
				std::string str1 = intToString(data[i].getDepartment());
				std::string str2 = doubleToString(data[i].getSalary());
				//out << i << data[i].fio->getSecondName() << " " << data[i].fio->getName() << " " << data[i].fio->getPatronymic() << " " << data[i].getDepartment() << std::setprecision(7) << data[i].getSalary();
				out << i << data[i].fio->getSecondName() << " " << data[i].fio->getName() << " " << data[i].fio->getPatronymic() << " " << str1 << " " << str2 << "\n";
				//data[i].fio->getName() << '\n' << data[i].fio->getSecondName() << "\n" << data[i].fio->getPatronymic() << '\n' << data[i].getDepartment() << '\n' << std::setprecision(7) << data[i].getSalary() << '\n';
			}
		}
		out.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to save in file. " << str << ", maybe you forgot to add employees?\n";
	}
}

void WorkerDatabase::loadDataBin(std::string fileName)
{
	std::string line;
	std::ifstream in;
	try
	{
		in.open(fileName);
		if (in.goodbit)
		{
			std::string str = "Check if a file exists. Unable to open " + fileName;
			throw(str);
		}
		emp* someEmp = new emp(0);
		data.push_back(*someEmp);
		//(*data)[0].name = "A";
		if (in.is_open())
		{
			int i;
			std::string name, secondName, patronymic, department, salary;
			//Department and salary are rubbish. Why?
			in >> i >> secondName >> name >> patronymic >> department >> salary;
			std::cout << secondName << name << patronymic << department << salary;
			someEmp->fio->setSecondName(secondName);
			someEmp->fio->setName(name);
			someEmp->fio->setPatronymic(patronymic);
			someEmp->setDepartment(std::stoi (department));
			someEmp->setSalary(std::stod (salary));
			/*while (getline(in, line))
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
			}*/
		}
		//delete someEmp;
		in.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to load a file. " << str;
	}
}

std::pair <emp, int> WorkerDatabase::searchEmp()
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

void WorkerDatabase::myRor(int min, int max)
{
	emp t = data[max];
	for (int i = max; i > min; i--)
		data[i] = data[i - 1];
	data[min] = t;
}

void WorkerDatabase::salarySort()
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

void WorkerDatabase::printWorkerList()
{
	if (data.size() == 0)
		std::cout << "No data stored";
	for (int i = 0; i < data.size(); i++)
	{
		data[i].printWorker(i);
	}
}