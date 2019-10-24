#pragma once

typedef class Worker2:public baseWorker
{
public:
	void printWorker(int i);
	void setProfession(const std::string str) { profession = str; };
	std::string getProfession() const { return profession; };
	void empToFile(std::ofstream& out, int i);
	void fileToEmp(std::istream& in);
	~Worker2();
	Worker2(int var);
private:
	std::string profession;
}emp2;

Worker2::Worker2(int var = 0)
{
	if (var == 0)
	{
		FIO* _fio = new FIO();
		fio = _fio;
		salary = 0.2;
		profession = "Programmer";
	}
	if (var == 1)
	{
		FIO* _fio = new FIO(1);
		fio = _fio;
		std::cout << "Enter salary: ";
		salary = getDoubleNumber();
		std::cout << "Enter profession: ";
		std::cin >> profession;
		std::cin.ignore();
	}
}

void Worker2::fileToEmp(std::istream& in)
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
	setProfession(line);
}

void Worker2::empToFile(std::ofstream& out, int i)
{
	out << i << '\n' << "2" << "\n" << getFIO()->getSecondName() << '\n' << getFIO()->getName() << "\n" << getFIO()->getPatronymic() << '\n' << std::setprecision(7) << getSalary() << '\n' << getProfession();
}

Worker2::~Worker2()
{
	delete fio;
}

void Worker2::printWorker(int i)
{
	std::cout << i << ": ";
	std::cout << fio->getName() << '\t';
	std::cout << fio->getSecondName() << '\t';
	std::cout << fio->getPatronymic() << '\t';
	std::cout << std::setprecision(5) << getSalary() << "\t";
	std::cout << getProfession() << "\n";
}