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

int	is_year_valid(std::string year, t_date min_date)
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
	if (date < min_date.year)
		return (0);
	return (1);
}

int	is_month_valid(std::string month, int year, t_date min_date)
{
	int	date;

	if (month.empty())
		return (0);
	for (int i = 0; month[i]; i ++)
	{
		if (!isdigit(month[i]))
			return (0);
	}
	date = atoi(month.c_str());
	if (!is_valid(date, 1, 12))
		return (0);
	if (year == min_date.year && date < min_date.month)
		return (0);
	return (1);
}

int	is_day_valid(std::string day, int month, int year, t_date min_date)
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
	if (year == min_date.year && month == min_date.month && date < min_date.day)
		return (0);
	return (1);
}

int	is_key_valid(std::string key, t_date min_date)
{
	std::string	year;
	std::string	month;
	std::string	day;

	if (key.empty())
		return (0);

	if (key[4] != '-' || key[7] != '-')
		return (0);

	year = key.substr(0, 4);
	if (!is_year_valid(year, min_date))
		return (0);
	month = key.substr(5, 2);
	if (!is_month_valid(month, atoi(year.c_str()), min_date))
		return (0);
	day = key.substr(8, 2);
	if (!is_day_valid(day, atoi(month.c_str()), atoi(year.c_str()), min_date))
		return (0);
	return (1);
}

int	has_dot(int sign, std::string value)
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

	if (sign == 1 && !value[1])
	{
		std::cout << "Error: unexpected char." << std::endl;
		return (0);
	}

	dot = has_dot(sign, value);
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

	if (line.size() < 13)
		return (NULL);
	value = line.substr(13, line.size());
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