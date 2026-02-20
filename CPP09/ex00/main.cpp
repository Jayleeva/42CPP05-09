#include "BitcoinExchange.hpp"



int	is_valid(int date, int min, int max)
{
	if (date < min || date > max)
		return (0);
	return (1);
}

int	is_year_bissextile(int year)
{
	if (year % 4 == 0 && year % 100 != 0)
		return (1);
	if (year % 400 == 0)
		return (1);
	return (0);
}

int	is_year_valid(std::string year)
{
	int	date;

	if (year.empty())
		return (0);
	for (int i = 0; year[i]; i ++)
	{
		if (!isdigit(year[i]))
			return (0);
	}
	date = atoi(year.c_str());
	if (!is_valid(date, 2009, 2026))
		return (0);
	return (1);
}

int	is_month_valid(std::string month, int year)
{
	int	date;

	if (month.empty())
	{
		//std::cout << "month empty" << std::endl;
		return (0);
	}
	for (int i = 0; month[i]; i ++)
	{
		if (!isdigit(month[i]))
		{
			//std::cout << month[i] << " is not a digit" << std::endl;
			return (0);
		}
	}
	date = atoi(month.c_str());
	if (!is_valid(date, 1, 12))
	{
		//std::cout << "not a month" << std::endl;
		return (0);
	}
	if (year == 2026 && date > 2)
	{
		//std::cout << "in the futuuure" << std::endl;
		return (0);
	}
	return (1);
}

int	is_day_valid(std::string day, int month, int year)
{
	int	date;
	int	min = 1;
	int	max;

	if (day.empty())
		return (0);
	for (int i = 0; day[i]; i ++)
	{
		if (!isdigit(day[i]))
			return (0);
	}
	if (month < 8)
	{
		if (month % 2 == 0)
		{
			if (month == 2)
			{
				if (is_year_bissextile(year))
					max = 29;
				else
					max = 28;
			}
			else
				max = 30;
		}
		else
			max = 31;
	}
	else
	{
		if (month % 2 == 0)
			max = 31;
		else
			max = 30;
	}
	date = atoi(day.c_str());
	if (!is_valid(date, min, max))
		return (0);
	if (year == 2009 && month == 1 && date < 2)
		return (0);
	if (year == 2026 && month == 2 && date > 26)
		return (0);
	return (1);
}

int	is_key_valid(std::string key)
{
	std::string	year;
	std::string	month;
	std::string	day;

	if (key.empty())
		return (0);

	if (key[4] != '-' || key[7] != '-')
		return (0);

	year = key.substr(0, 4);
	if (!is_year_valid(year))
		return (0);
	month = key.substr(5, 2);
	if (!is_month_valid(month, atoi(year.c_str())))
		return (0);
	day = key.substr(8, 2);
	if (!is_day_valid(day, atoi(month.c_str()), atoi(year.c_str())))
		return (0);
	return (1);
}

int	unexpectedchar(int sign, std::string value)
{
	int	dot = 0;

	for (int i = sign + 1; value[i]; i ++)
	{
		if (value[i] == '.')
		{
			dot ++;
			if (dot > 1)
				return (-1);
			if (!value[i + 1])
				return (-1);
		}
		if (!isdigit(value[i]) && value[i] != '.')
			return (-1);
	}
	return (dot);
}

int	is_value_valid(std::string value)
{
	int	sign = 0;
	int	dot = 0;

	if (value.empty())
		return (0);
	if (value[0] == '-')
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (0);
	}
	if (value[0] == '+')
		sign = 1;

	dot = unexpectedchar(sign, value);
	if (dot == -1)
	{
		std::cout << "Error: unexpected char." << std::endl;
		return (0);
	}
	if (dot == 0)
	{
		long    l;

		l = atol(value.c_str());
		if (l < 0 || l > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			return (0);
		}
	}
	if (dot == 1)
	{
		float   f;
		
		f = atof(value.c_str());
		if (f < 0.0f || f > 1000.0f)
		{
			std::cout << "Error: too large a number." << std::endl;
			return (0);
		}
	}
	return (1);
}

std::string	getKey(std::string line)
{
	std::string key;

	try
	{
		key = (line.substr(0,10));
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (NULL);
	}
	return (key);
}

std::string getValue(std::string line)
{
	std::string	value;

	try
	{
		value = line.substr(13, line.size());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (NULL);
	}
	return (value);
}

float	getRate(std::string key, std::map<std::string, float> data)
{
	float	rate = -2;

	std::map<std::string, float>::const_iterator it = data.find(key);
	if (it == data.end())
	{
		it = data.upper_bound(key);
		if (it != data.begin())
			it--;
	}
	rate = it->second;
	return (rate);
}

int	main(int argc, char **argv)
{
	BitcoinExchange	btc;

	if (argc != 2)
	{
		std::cout << "Error: no file submitted." << std::endl;
		return (1);
	}
	if (btc.setMap("data.csv"))
		btc.printRes(argv[1]);
	return (0);
}