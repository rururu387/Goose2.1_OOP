#pragma once

double myCeil(double num)
{
	double round = 1;
	for (int i = 0; floor(num) != 0; i++)
	{
		num /= 10;
		round *= 10;
	}
	return round;
}

double getDoubleNumber()
{
	int flag = 0;
	double whole, fractional;
	while (flag != 2)
	{
		whole = 0;
		fractional = 0;
		//std::cin.ignore();
		std::string digitStr;
		std::getline(std::cin, digitStr);
		if (digitStr.size() == 0)
		{
			std::cout << "You didn't enter a number. Retry: ";
			flag = 2;
		}
		for (int i = 0; i < digitStr.size(); i++)
		{
			if (isdigit(digitStr[i]))
			{
				if (flag == 0)
					whole = whole * 10 + digitStr[i] - '0';
				if (flag == 1)
				{
					fractional = fractional * 10 + digitStr[i] - '0';
				}
			}
			else
			{
				if (digitStr[i] == '.' && flag == 0)
					flag = 1;
				else
				{
					std::cout << "You have entered an unvalid number. Retry: ";
					flag = 0;
					break;
				}
			}
		}
		flag = 2;
	}

	/*double fractionalCpy = fractional;
	double round = 1;
	for (int i = 0; floor(fractionalCpy) != 0; i++)
	{
		fractionalCpy /= 10;
		round *= 10;
	}*/

	return whole + (fractional / myCeil(fractional));
}

int getIntNumber()
{
	int flag = 1;
	int num = 0;
	while (flag)
	{
		num = 0;
		flag = 0;
		std::string digitStr;
		std::getline(std::cin, digitStr);
		if (digitStr.size() == 0)
		{
			std::cout << "You didn't enter a number. Retry: ";
			flag = 2;
		}
		for (int i = 0; i < digitStr.size() && flag != 2; i++)
		{
			if (isdigit(digitStr[i]))
			{
				num = num * 10 + digitStr[i] - '0';
			}
			else
			{
				std::cout << "You have entered an unvalid number. Retry: ";
				flag = 2;
			}
		}
	}
	return num;
}

int stringToInt(std::string line)
{

	int num = 0;
	try
	{
		for (int i = 0; i != line.size(); i++)
		{
			if (isdigit(line[i]))
			{
				num = num * 10 + line[i] - '0';
			}
			else
			{
				std::string str = "Not a valid int stroed";
				throw (str);
			}
		}
	}
	catch (std::string str)
	{
		std::cout << "Exception: data corrupted: " << str;
	}
	return num;
}

double stringToDouble(std::string line)
{
	double whole = 0;
	double fractional = 0;
	bool flag = 1;
	try
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != '.')
			{
				if (isdigit(line[i]))
				{
					if (flag)
					{
						whole = whole * 10 + line[i] - '0';
					}
					else
					{
						fractional = fractional * 10 + line[i] - '0';
					}
				}
				else
				{
					std::string str = "Not a valid double stored";
					throw(str);
				}
			}
			else
				flag = 0;
		}
	}
	catch (std::string str)
	{
		std::cout << "Exception: data corrupted: " << str;
	}
	double res = whole + fractional / myCeil(fractional);
	return res;
}