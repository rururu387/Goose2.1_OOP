#pragma once

std::string getStringFromStream(std::istream& in, char flag)
{
	char a = in.get();
	std::string str = "";
	str = "";
	while (a != flag)
	{
		str += a;
		a = in.get();
	}
	return str;
}

int atod(char a)
{
	if (a >= 48 && a <= 57)
		return a - '0';
	return -1;
}

int getIntFromStream(std::istream& in, char flag)
{
	int num = 0;
	char a = in.get();
	bool flag2 = 0;
	if (a == '-')
	{
		a = in.get();
		flag2 = 1;
	}
	while (a != flag)
	{
		if (atod(a) == -1)
			throw ("Cannot convert char to digit");
		num *= 10;
		num += atod(a);
		a = in.get();
	}
	if (flag2)
		num = -num;
	return num;
}