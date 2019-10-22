#pragma once

typedef class Worker1 : public baseWorker
{
	int department;
public:
	Worker1(std::string _secondName, std::string _name, std::string _patronymic, int _department, double _salary);
	Worker1(int var = 0);
	Worker1(const Worker1 &_someEmp);
	int getDepartment()  const { return department; }
	void setDepartment(int _department) { department = _department; }
	void printWorker(int i);
	void empToFile(std::ofstream& out, int i);
	void fileToEmp(std::istream& in);
	Worker1& operator = (const Worker1& rightVal);
	friend std::istream& operator >> (std::istream& in, Worker1& rightVal);
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

void Worker1::fileToEmp(std::istream& in)
{
	std::string line;
	getline(in, line);
	getFIO()->setName(line);
	getline(in, line);
	getFIO()->setSecondName(line);
	getline(in, line);
	getFIO()->setPatronymic(line);
	getline(in, line);
	setSalary(stringToDouble(line));
	getline(in, line);
	setDepartment(stringToInt(line));
}

void Worker1::empToFile(std::ofstream& out, int i)
{
	out << i << "\n" << "1" << '\n' << getFIO()->getSecondName() << '\n' << getFIO()->getName() << "\n" << getFIO()->getPatronymic() << '\n' << std::setprecision(7) << getSalary() << '\n' << getDepartment() << '\n';
}

inline std::istream &operator >> (std::istream &in, Worker1 &rightVal)
{
	int department;
	double salary;
	in >> *(rightVal.fio) >> salary >> department;
	rightVal.setSalary(salary);
	rightVal.setDepartment(department);
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
}

Worker1::Worker1(int var)
{
	if (var == 0)
	{
		FIO* _fio = new FIO();
		fio = _fio;
		setDepartment(1);
		setSalary(0.1);
	}
	else if (var == 1)
	{
		std::cout << "Enter the following worker's data, please.\n";
		FIO* _fio = new FIO(1);
		fio = _fio;
		std::cout << "Enter salary: ";
		setSalary(getDoubleNumber());
		std::cout << "Enter department: ";
		setDepartment(getIntNumber());
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

//Все навороты - исключительно для выпендрежа. Ну, и для того чтобы что-то доказать самому себе =)
//Да, это *0**0*0* (--* --- *-- -* --- -*- --- -**), все так и задумывалось