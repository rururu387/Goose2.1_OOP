class Order
{
	Development* task;
	Schedule* sched;
public:
	Development getDevelopment() { return *task; };
	Schedule getSch() { return *sched; };
	void setDevelopment(Development _task);
	//void setSchedule(Schedule _sched);
	Order(Development* _task, Schedule* _sched);
	Order();
	~Order();
	void getConsole();
	std::string toString();
	void toStream(std::ofstream& out);
	void fromStream(std::ifstream& in);
};

void Order::fromStream(std::ifstream& in)
{
	sched->fromStream(in);
	task->fromStream(in);
}

void Order::toStream(std::ofstream& out)
{
	/*std::string str = "";
	str += sched->toFile();
	str += task->toFile();*/
	sched->toStream(out);
	task->toStream(out);
	//return str;
}

std::string Order::toString()
{
	return "\tCompany's orders: " + sched->toString() + "\tTask: " + task->toString();
}

/*void Order::setSchedule(Schedule _sched)
{
	sched->setDateSch(_sched.getDateSch());
	sched->setDateFact(_sched.getDateFact());
}*/

void Order::setDevelopment(Development _task)
{
	task->setName(_task.getName());
	task->setStageAm(_task.getStageAm());
	task->getStageSch().clear();
	for (int i = 0; i < _task.getStageAm(); i++)
	{
		task->getStageSch().push_back(_task.getStageSch()[i]);
	}
}

void Order::getConsole()
{
	//std::cout << "\t\tSet order's parameters\n";
	sched->getConsole(2);
	std::cout << "\n\t\tSet order's development information\n\t\t";
	task->getConsole();
}

Order::Order(Development* _task, Schedule* _sched)
{
	task = _task;
	sched = _sched;
}

Order::Order()
{
	task = new Development();
	sched = new Schedule();
}

Order::~Order()
{
	delete task;
	delete sched;
}