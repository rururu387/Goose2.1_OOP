#pragma once

typedef class baseWorker
{
public:
	FIO* getFIO();
	const FIO getConstFIO() const;
	virtual void printWorker(int i) {};
	const double getSalary() const { return salary; }
	void setSalary(double _salary) { salary = _salary; }
	bool operator == (FIO someFIO);
	virtual void empToFile(std::ofstream& out, int i);
	virtual void fileToEmp(std::istream& in);
protected:
	double salary;
	FIO* fio;
	static int count;
	int getCount() { return count; }
}base;
int baseWorker::count = 0;

void baseWorker::empToFile(std::ofstream& out, int i)
{
	std::string str = "You are trying to write in a file baseWorker of an invalid type.";
	throw (str);
}

void baseWorker::fileToEmp(std::istream& in)
{
	std::string str = "You are trying to a baseWorker of an invalid type from file. Data may be corrupted.";
	throw (str);
}

const FIO baseWorker::getConstFIO() const
{
	return *fio;
}

FIO* baseWorker::getFIO()
{
	return fio;
}

inline bool baseWorker::operator == (FIO someFIO)
{
	if (*(this->fio) == someFIO)
		return 1;
	return 0;
}