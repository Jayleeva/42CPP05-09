#include "BitcoinExchange.hpp"

int	is_year_valid(std::string year)
{
	if (year.empty())
		return (0);
	
	return (1);
}

int	is_month_valid(std::string month)
{
	if (month.empty())
		return (0);
	
	return (1);
}

int	is_day_valid(std::string day, int month)
{

	if (day.empty())
		return (0);
	if (month < 8)
	{
		if (month % 2 == 0)
		{
			if (month == 2)
			{

			}
			else
			{

			}
		}

	}

	
	return (1);
}

int	is_line_valid(std::string line)
{
	std::string		key;
	std::string		value;

	if (line.empty() || line[11] != '|')
		return (0);
 	key = line.substr(0,11);
	if (key.empty() || key[4] != '-' || key[7] != '-')
		return (0);
	if (!is_year_valid(key.substr(0, 4)))
		return (0);
	if (!is_month_valid(key.substr(5, 7)))
		return (0);
	if (!is_day_valid(key.substr(8, 11), atoi(key.substr(5, 7).c_str())))
		return (0);
	value = line.substr(12, line.size());
	if (!is_value_valid(value))
		return (0);
	return (1);
}


int	main(int argc, char **argv)
{
	std::ifstream				infile;
	std::map<std::string, int>	lines;

	if (argc != 2)
	{
		std::cout << "Error: no file submitted." << std::endl;
		return (1);
	}

	infile.open(argv[1]);
	if (infile.fail())
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	std::string firstline;
	std::getline(infile, firstline);
	if (firstline != "date | value")
	{
		std::cout << "Error: wrong first line." << std::endl;
		return (0);
	}
    for (std::string line; std::getline(infile, line);)
	{
		std::string		key;
		int				value;

		if (!is_line_valid(line))
		{
			std::cout << "Error: wrong format." << std::endl;
			infile.close();
			return (1);
		}
		key = line.substr(0, 11);
		value = atoi(line.substr(12, line.size()).c_str());
		lines.insert({key, value});
	}
	//bitcoin(lines);
	infile.close();
	return (0);
}