#pragma once

typedef class Worker2:public baseWorker
{
private:
	std::string profession;
	void printWorker(int i);
	const int getDepartment() { return -1; };
	void setDepartment(int dep) { throw ("Tryed to set department to Worker2"); };
	~Worker2();
}emp2;

Worker2::~Worker2()
{
	delete fio;
}

void Worker2::printWorker(int i)
{
	std::cout << i << ": " << fio->getSecondName() << fio->getName() << fio->getPatronymic() << profession << salary;
}