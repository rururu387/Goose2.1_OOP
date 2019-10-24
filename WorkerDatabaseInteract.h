#pragma once

typedef class WorkerDatabaseInteract
{
	std::vector <std::pair <void*, int>> data;
	int getMaxSizeType();
public:
	friend void searchDepartment(WorkerDatabaseInteract _data);
	void addEmployees();
	void saveData(std::string fileName, bool isBinary = 0);
	void loadData(std::string fileName);
	std::pair <void*, int> searchEmp();
	void myRor(int min, int max);
	void salarySort();
	std::pair <void*, int> operator [] (int i);
	void printWorkerList();
	void pop_back();
	int size();
	friend WorkerDatabaseInteract operator ++(WorkerDatabaseInteract &someDB);
	void operator += (Worker1 someWorker);
	void push_back(FIO fio, int department, double salary);
	void push_back(Worker1 someWorker);
	void DDB();
}wd;

void WorkerDatabaseInteract::DDB()
{
	for (int i = 0; i < this->size(); i++)
	{
		delete data[i].first;
	}
	data.clear();
}

void WorkerDatabaseInteract::push_back(Worker1 someWorker)
{
	this->data.push_back(std::pair <void*, int> ((void*) (&someWorker), 1));
}

void WorkerDatabaseInteract::push_back(FIO fio, int department, double salary)
{
	this->data.push_back(std::pair <void*, int> ((void*)((new Worker1 (fio.getSecondName(), fio.getName(), fio.getPatronymic(), department, salary))), 1));
}

void WorkerDatabaseInteract::operator +=(Worker1 someWorker)
{
	this->data.push_back(std::pair <void*, int>((void*)(&someWorker), 1));
}


WorkerDatabaseInteract operator ++(WorkerDatabaseInteract &someDB)
{
	someDB.data.push_back(std::pair <void*, int> ((void*)(new Worker1()), 1));
	return someDB;
}

int WorkerDatabaseInteract::size()
{
	return data.size();
}

void WorkerDatabaseInteract::pop_back()
{
	data.pop_back();
}

std::pair <void*, int> WorkerDatabaseInteract::operator [] (int i)
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
	std::cout << "Enter the needed department: ";
	int dep = getIntNumber();
	bool flag = 0;
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].second == 1 && ((Worker1*) (_data[i].first))->getDepartment() == dep)
		{
			((Worker1*) (_data[i].first))->printWorker(i);
			flag = 1;
		}
	}
	if (flag == 0)
		std::cout << "No workers from this department known\n";
}

void WorkerDatabaseInteract::addEmployees()
{
	int amount;
	std::cout << "The amount of employees to add: ";
	amount = getIntNumber();

	for (int i = 0; i < amount; i++)
	{
		int type;
		std::cout << "Enter worker's data, please.\n";
		std::cout << "Insert a type of employee storaged info (1 - department, 2 - profession): ";
		type = getIntNumber();
		void* someEmp;
		bool errorFlag = 0;
		try
		{
			switch (type)
			{
			case 1:
				someEmp = (void*) new emp(1);
				break;
			case 2:
				someEmp = (void*) new emp2(1);
				break;
			default:
				std::string str = "No description of such type here";
				throw (str);
			}
		}
		catch (std::string str)
		{
			errorFlag = 1;
			std::cout << str << "Did you fill in the type correctly? Retry now.\n";
			i--;
		}
		if (!errorFlag)
			data.push_back(std::pair <void*, int>(someEmp, type));
	}
}

void WorkerDatabaseInteract::saveData(std::string fileName, bool isBinary)
{
	std::ofstream out;
	try
	{
		if (isBinary)
			out.open(fileName, std::fstream::binary | std::fstream::out);
		else
			out.open(fileName, std::fstream::out);

		if (out.is_open())
		{
			for (int i = 0; i < data.size(); i++)
			{
				switch (data[i].second)
				{
				case 1:
					((Worker1*)data[i].first)->empToFile(out, i);
					break;
				case 2:
					((Worker2*)data[i].first)->empToFile(out, i);
					break;
				default:
					std::string str = "No description of such type here";
					throw (str);
					break;
				}
			}
		}
		else
		{
			std::string str = "Couldn't save data. Unable to open " + fileName + "\n";
			throw(str);
		}
		out.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to save in file. " << str << ", maybe you forgot to add employees?\n";
	}
}

int WorkerDatabaseInteract::getMaxSizeType()
{
	int sizeArray[] = {sizeof(Worker1), sizeof(Worker2)};
	int maxSize = 0;
	int maxSizeType = 0;
	for (int i = 0; i < 2; i++)
	{
		if (maxSize < sizeArray[i])
		{
			maxSize = sizeArray[i];
			maxSizeType = i;
		}
	}
	return maxSizeType;
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
		void* someWorker = someEmp;
		if (in.is_open())
		{
			while (getline(in, line))
			{
				int j = std::stoi(line);
				getline(in, line);
				int type = std::stoi(line);
				if (j >= data.size())
				{
					for (int i = data.size(); i <= j; i++)
					{
						data.push_back(std::pair <void*, int>(someEmp, 1));
					}
				}
				int maxSizeType = getMaxSizeType();
				switch (maxSizeType)
				{
				case 1:
					someWorker = (void*)new Worker1();
					break;
				case 2:
					someWorker = (void*)new Worker1();
					break;
				default:
					std::string str = "No description of such type here";
					throw (str);
					break;
				}
				switch (type)
				{
				case 1:
					((Worker1*)someWorker)->fileToEmp(in);
					break;
				case 2:
					((Worker2*)someWorker)->fileToEmp(in);
					break;		
				default:
						std::string str = "No description of such type here";
						throw (str);
						break;
				}
				data[j].first = someWorker;
				data[j].second = type;
			}
		}
		in.close();
	}
	catch (std::string str)
	{
		std::cout << "Failed to load a file. " << str << "\n";
	}
}

std::pair <void*, int> WorkerDatabaseInteract::searchEmp()
{
	std::string searchedSecondName;
	std::cout << "Print an employee's second name: ";
	std::getline(std::cin, searchedSecondName);
	int i = 0;
	for (std::vector <std::pair<void*, int>> ::iterator it = data.begin(); it < data.end(); it++)
	{
		if((it->second == 1 && ((Worker1*)it->first)->getFIO()->getSecondName().compare(searchedSecondName) == 0) || (it->second == 2 && ((Worker2*)it->first)->getFIO()->getSecondName().compare(searchedSecondName) == 0))
		{
			std::pair <void*, int> swaggyPair(it->first, it->second);
			return swaggyPair;
		}
		i++;
	}
	std::pair <void*, int> swaggyPair(data.begin()->first, -1);
	return swaggyPair;
}

void WorkerDatabaseInteract::myRor(int min, int max)
{
	std::pair <void*, int> t = data[max];
	for (int i = max; i > min; i--)
		data[i] = data[i - 1];
	data[min] = t;
}

void WorkerDatabaseInteract::salarySort()
{
	int len = data.size();

	for (int i = 1; i < len; i++)
	{
		int max = i - 1, min = 0;

		double salary1 = 0;
		double salary2 = 0;
		switch (data[(max + min) / 2].second == 1)
		{
		case 1:
			salary1 = ((Worker1*)data[(max + min) / 2].first)->getSalary();
			break;
		case 2:
			salary1 = ((Worker2*)data[(max + min) / 2].first)->getSalary();
			break;
		default:
			std::string str = "No description of such type here";
			throw (str);
			break;
		}
		switch (data[i].second == 1)
		{
		case 1:
			salary2 = ((Worker1*)data[i].first)->getSalary();
			break;
		case 2:
			salary2 = ((Worker2*)data[i].first)->getSalary();
			break;
		default:
			std::string str = "No description of such type here";
			throw (str);
			break;
		}

		while (max != min)
		{
			if (salary1 <= salary2)
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
		if (salary1 >= salary2)
			myRor(max, i);
	}
	std::cout << "Data was sorted\n";
}

void WorkerDatabaseInteract::printWorkerList()
{
	if (data.size() == 0)
		std::cout << "No data stored\n";
	for (int i = 0; i < data.size(); i++)
	{
		switch (data[i].second)
		{
		case 1:
			((Worker1*)data[i].first)->printWorker(i);
			break;
		case 2:
			((Worker2*)data[i].first)->printWorker(i);
			break;
		default:
			std::string str = "No description of such type here";
			throw (str);
			break;
		}
	}
}