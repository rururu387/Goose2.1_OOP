#pragma once

typedef class Worker1 : public baseWorker
{
	int department;
public:
	Worker1(std::string _secondName, std::string _name, std::string _patronymic, int _department, double _salary);
	Worker1(int var = 0);
	Worker1(const Worker1 &_someEmp);
	const int getDepartment() { return department; }
	void setDepartment(int _department) { department = _department; }
	void printWorker(int i);
private:
	Worker1& operator = (const Worker1 &rightVal);
	friend std::istream &operator >> (std::istream &in, Worker1 &rightVal);
	~Worker1();
}emp;

Worker1::~Worker1()
{
	delete fio;
}

Worker1& Worker1::operator = (const Worker1 &rightVal)
{
	if (this == &rightVal)
		throw ("You've tryed to write one's data to himself");
	else
	{
		this->department = rightVal.getDepartment();
		this->salary = rightVal.getSalary();
		delete this->fio;
		this->fio->deepCopy(&(rightVal.getConstFIO()));
	}
	return *this;
}

inline std::istream &operator >> (std::istream &in, Worker1 &rightVal)
{
	int department;
	double salary;
	in >> *(rightVal.fio) >> department >> salary;
	rightVal.setDepartment(department);
	rightVal.setSalary(salary);
}

Worker1::Worker1(const Worker1 &_someEmp)
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

Worker1::Worker1(int var)
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

Worker1::Worker1 (std::string _secondName, std::string _name, std::string _patronymic, int _department, double _salary)
{
	FIO* _fio = new FIO(_secondName, _name, _patronymic);
	fio = _fio;
	department = _department;
	salary = _salary;
	//count++;
}

/*Worker::~Worker()
{
	delete this->fio;
}*/

void Worker1::printWorker(int i)
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