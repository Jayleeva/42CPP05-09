#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << YELLOW << "[BTC] : Default constructor called." << DEFAULT << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &original)
{
	*this = original;
    std::cout << YELLOW << "[BTC] : Copy destructor called." << DEFAULT << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &original)
{
	if (this != &original)
	{
		this->dataLines = original.dataLines;
	}
    std::cout << YELLOW << "[BTC] : Assignment operator overload called." << DEFAULT << std::endl;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << YELLOW << "[BTC] : Default destructor called." << DEFAULT << std::endl;
}

std::map<std::string, float>	BitcoinExchange::getMap() const
{
	return(this->dataLines);
}

int	BitcoinExchange::setMap(std::string dataFile)
{
	std::ifstream				data;

	data.open(dataFile.c_str());
	if (data.fail())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (0);
	}
	std::string firstline;
	std::getline(data, firstline);
	if (firstline.empty())
	{
		data.close();
		return (0);
	}
	int i = 0;
    for (std::string line; std::getline(data, line);)
	{
		std::string		key;
		std::string		valuestr;
		float			value;

		try
		{
			key = (line.substr(0,10));
			valuestr = line.substr(11, line.size());
			value = std::atof(valuestr.c_str());
			std::pair<std::string, float> p = std::make_pair(key, value);
			this->dataLines.insert(p);
			if (i == 0)
			{
				this->min_date.year = atoi(key.substr(0,4).c_str());
				this->min_date.month = atoi(key.substr(5,6).c_str());
				this->min_date.day = atoi(key.substr(8,9).c_str());
			}
			i ++;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			data.close();
			return (0);
		}
	}
	data.close();

	return (1);
}

void	BitcoinExchange::printRes(char *inputFile)
{
	std::ifstream				file;
	std::string					key;
	std::string					value;
	float						rate;

	file.open(inputFile);
	if (file.fail())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}
	std::string firstline;
	std::getline(file, firstline);
	if (firstline.empty() || !firstline.compare("date | value\n"))
	{
		std::cerr << "Error: wrong format." << std::endl;
		file.close();
		return ;
	}
    for (std::string line; std::getline(file, line);)
	{
		if (line.empty())
			continue;
		if (!line[10] || !line[11] || line[11] != '|' || !line[13])
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		key = getKey(line);
		if (!is_key_valid(key, this->min_date))
		{
			std::cout << "Error: bad input => " << key << std::endl;
			continue ;
		}
		value = getValue(line);
		if (!is_value_valid(value))
			continue ;
		rate = getRate(key, this->dataLines);
		if (rate > -1)
			std::cout << key << " => " << value << " = " << std::atof(value.c_str()) * rate << std::endl;
	}
	file.close();
}