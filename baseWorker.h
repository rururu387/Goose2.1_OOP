#pragma once

typedef class baseWorker
{
public:
	FIO* getFIO();
	const FIO getConstFIO();
	virtual void printWorker(int i) {};
	virtual const int getDepartment() {};
	virtual void setDepartment(int dep) {};
	const double getSalary() const { return salary; }
	void setSalary(double _salary) { salary = _salary; }
	bool operator == (FIO someFIO);
protected:
	double salary;
	FIO* fio;
	static int count;
	int getCount() { return count; }
}base;
int baseWorker::count = 0;

const FIO baseWorker::getConstFIO()
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