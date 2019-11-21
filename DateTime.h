#pragma once

class Date
{
protected:
	int year;
	int month;
	int day;
	static bool isCorrect(int _year, int _month, int _day);
public:
	bool isCorrect();
	Date(int _year, int _month, int _day);
	Date(Date& someDate);
	int getYear();
	int getMonth();
	int getDay();
	void setYear(int _year);
	void setMonth(int _month);
	void setDay(int _day);
	std::string toString();
};

std::string Date::toString()
{
	return std::to_string(year) + "." + std::to_string(month) + "." + std::to_string(day);
}

bool Date::isCorrect()
{
	return isCorrect(year, month, day);
}

bool Date::isCorrect(int _year, int _month, int _day)
{
	if (_year > 10000 || _year < -10000)
	{
		throw ("Date is unvalid: Year exceeds -10000...10000 interval.");
	}
	if (_month > 12 || _month < 1)
	{
		throw("Date is unvalid: Month is incorrect.");
	}
	if (_year == 0 && _month == 0 && _day == 0)
	{
		throw ("Date is unvalid: Year, month and date set to 0.");
	}
	switch (_month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (_day <= 31 && _day > 0)
				return 1;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (_day > 0 && _day <= 30)
				return 1;
			break;
		case 2:
			if (_day > 0)
			{
				if (_day <= 28)
					return 1;
				if (_day == 29)
				{
					if (_year % 4 == 0)
					{
						if (_year % 100 == 0 && _year % 400 != 0)
						{}
						return 1;
					}
				}
			}
			break;
	}
	throw ("Date is unvalid: Day is incorrect. There is no such day " + std::to_string(_month) + "." + std::to_string(_year));
	return 0;
}

void Date::setYear(int _year)
{
	if (isCorrect(_year, month, day))
		year = _year;
}

void Date::setMonth(int _month)
{
	if (isCorrect(year, _month, day))
		month = _month;
}

void Date::setDay(int _day)
{
	if (isCorrect(year, month, _day))
		day = _day;
}

int Date::getYear()
{
	return year;
}

int Date::getMonth()
{
	return month;
}

int Date::getDay()
{
	return day;
}

Date::Date(int _year, int _month, int _day)
{
	isCorrect(_year, _month, _day);
	year = _year;
	month = _month;
	day = _day;
}

Date::Date(Date& someDate)
{
	if (someDate.isCorrect())
	{
		year = someDate.getYear();
		month = someDate.getMonth();
		day = someDate.getDay();
	}
}

class DateTime : public Date
{
	int hour;
	int minute;
	int second;
	bool isCorrectTime(int _year, int _month, int _day, int _hour, int _minute, int _second);
public:
	bool isCorrect();
	DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second);
	DateTime(int _year, int _month, int _day);
	DateTime(DateTime& someDateTime);
	int getHour();
	int getMinute();
	int getSecond();
	void setHour(int _hour);
	void setMinute(int _hour);
	void setSecond(int _hour);
	std::string toString();
};

std::string DateTime::toString()
{
	return std::to_string(year) + "." + std::to_string(month) + "." + std::to_string(day) + " " + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}

bool DateTime::isCorrect()
{
	return isCorrectTime(year, month, day, hour, minute, second);
}

bool DateTime::isCorrectTime(int _year, int _month, int _day, int _hour, int _minute, int _second)
{
	if (Date::isCorrect(_year, _month, _day))
	{
		if (_hour < 25 && _hour > 0)
		{
			if (_minute < 60 && _minute > 0)
			{
				if (_second < 60 && _second > 0)
					return 1;
			}
		}
	}
	return 0;
}

void DateTime::setHour(int _hour)
{
	if (isCorrectTime(year, month, day, _hour, minute, second))
		hour = _hour;
}

void DateTime::setMinute(int _minute)
{
	if (isCorrectTime(year, month, day, hour, _minute, second))
		minute = _minute;
}

void DateTime::setSecond(int _second)
{
	if (isCorrectTime(year, month, day, hour, minute, _second))
		second = _second;
}

int DateTime::getHour()
{
	return hour;
}

int DateTime::getMinute()
{
	return minute;
}

int DateTime::getSecond()
{
	return second;
}

DateTime::DateTime(int _year, int _month, int _day) : Date(_year, _month, _day)
{
	hour = -1;
	minute = -1;
	second = -1;
}

DateTime::DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second) : Date(_year, _month, _day)
{
	if (isCorrectTime(year, month, day, _hour, _minute, _second))
	{
		hour = _hour;
		minute = _minute;
		second = _second;
	}
}

DateTime::DateTime(DateTime& someDateTime) : Date(someDateTime.getYear(), someDateTime.getMonth(), someDateTime.getDay())
{
	if (someDateTime.isCorrect())
	{
		year = someDateTime.getYear();
		month = someDateTime.getMonth();
		day = someDateTime.getDay();
		hour = someDateTime.getHour();
		minute = someDateTime.getMinute();
		second = someDateTime.getSecond();
	}
}