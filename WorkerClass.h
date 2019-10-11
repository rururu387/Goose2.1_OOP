#pragma once

typedef class Worker
{
	//void initialize();
	int department;
	double salary;
	static int count;
	//std::pair <emp, int> searchEmp (std::vector <emp> data);
	//void salarySort(std::vector <emp>* data);
	//friend void searchDepartment(std::vector <emp> data);
public:
	FIO* fio;
	Worker(char* _name, char* _secondName, int _department, double _salary);
	Worker(int var = 0);
	Worker(const Worker &_someEmp);
	~Worker();
	int getDepartment() const { return department; }
	double getSalary() const { return salary; }
	void setDepartment(int _department) { department = _department; }
	void setSalary(double _salary) { salary = _salary; }
	int getCount() { return count; }
	void printWorker(int i);
	Worker operator = (const Worker &rightVal);
	friend std::istream &operator >> (std::istream &in, Worker&rightVal);
	bool operator == (Worker someEmp);
}emp;
int Worker::count = 0;

inline bool Worker::operator == (Worker someEmp)
{
	if (this->fio == someEmp.fio && this->getDepartment() == someEmp.getDepartment() && this->getSalary() == someEmp.getSalary())
		return 1;
	return 0;
}

inline Worker Worker::operator = (const Worker &rightVal)
{
	if (this == &rightVal)
		throw ("You've tryed to write one's data to himself");
	else
	{
		this->department = rightVal.department;
		this->fio = rightVal.fio->deepCopy(rightVal.fio);
	}
}

inline std::istream &operator >> (std::istream &in, Worker &rightVal)
{
	int department;
	double salary;
	in >> *(rightVal.fio) >> department >> salary;
	rightVal.setDepartment(department);
	rightVal.setSalary(salary);
}

Worker::Worker(const Worker &_someEmp)
{
	/*this->fio->setName(_someEmp.fio->getName());
	this->fio->setSecondName(_someEmp.fio->getSecondName());*/
	//FIO *fio = new FIO(_someEmp.fio);
	FIO* someFIO(_someEmp.fio);
	this->fio = someFIO;
	this->setDepartment(_someEmp.getDepartment());
	this->setSalary(_someEmp.getSalary());
	//count++;			Ёто как понимать? count сам измен€етс€ при вызове конструкторов и деструкторов
}

/*void Worker::initialize()
{
	name = "";
	fam = "";
	department = 0;
	salary = 0;
}*/

Worker::Worker(int var)
{
	//initialize();
	if (var == 0)
	{
		FIO* _fio = new FIO();
		fio = _fio;
		setDepartment(0);
		setSalary(0);
	}
	else if (var == 1)
	{
		std::cout << "Enter the following worker's data, please.\n";
		FIO* _fio = new FIO(1);
		fio = _fio;
		/*std::cout << "Enter name: ";
		//std::cin.clear();
		std::string _str;
		std::getline(std::cin, _str);
		fio->setName(_str);
		//setName(_str);
		std::cout << "Enter secondName: ";
		std::getline(std::cin, _str);
		fio->setSecondName(_str);*/
		//setFam(_str);
		std::cout << "Enter department: ";
		setDepartment(getIntNumber());
		std::cout << "Enter salary: ";
		setSalary(getDoubleNumber());
		//count++;
	}
}

Worker::Worker (char* _name, char* _secondName, int _department, double _salary)
{
	this->fio->setName(_name);
	this->fio->setSecondName(_secondName);
	department = _department;
	salary = _salary;
	//count++;
}

Worker::~Worker()
{
	delete this->fio;
}

void Worker::printWorker(int i)
{
	std::cout << i << ": ";
	std::cout << fio->getName() << '\t';
	std::cout << fio->getSecondName() << '\t';
	std::cout << fio->getPatronymic() << '\t';
	std::cout << getDepartment() << '\t';
	std::cout << std::setprecision(5) << getSalary() << "\n";
	//printf ("%s\t%s\t%d\t%lf", data[i]->name, data[i]->secondName, data[i]->department, data[i]->salary);
}

//¬се навороты - исключительно дл€ выпендрежа. Ќу, и дл€ того чтобы что-то доказать самому себе =)
//ƒа, это *0**0*0* (--* --- *-- -* --- -*- --- -**), все так и задумывалось