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
		std::cout << "Error: could not open file." << std::endl;
		return ;
	}
	std::string firstline;
	std::getline(data, firstline);
	if (firstline.empty())
		return;
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
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
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
		std::cout << "Error: could not open file." << std::endl;
		return ;
	}
	std::string firstline;
	std::getline(file, firstline);
	if (firstline.empty() || firstline != "date | value")
	{
		std::cout << "Error: wrong format." << std::endl;
		return ;
	}
    for (std::string line; std::getline(file, line);)
	{
		if (line.empty())
			continue;
		if (!line[11] || line[11] != '|' || !line[13])
		{
			std::cout << "Error: wrong format." << std::endl;
			continue;
		}
		key = getKey(line);
		if (!is_key_valid(key))
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