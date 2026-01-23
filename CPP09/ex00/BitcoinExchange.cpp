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

	}
    std::cout << YELLOW << "[BTC] : Assignment operator overload called." << DEFAULT << std::endl;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << YELLOW << "[BTC] : Default destructor called." << DEFAULT << std::endl;
}

std::map<std::string, int>	BitcoinExchange::getMap() const
{
	return(this->dataLines);
}

void	BitcoinExchange::setMap(char *dataFile)
{
	std::ifstream				data;

	data.open(dataFile);
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
		int				value;

		key = line.substr(0, 11);
		if (key.empty())
			return;
		valuestr = line.substr(12, line.size());
		if (valuestr.empty())
			return ;
		value = std::stof(valuestr);
		this->dataLines.insert({key, value});
	}
	data.close();
}

std::vector<std::string> is_line_valid(std::string line)
{
	std::vector<std::string>	v[2];

	if (line.empty() || line[11] != '|')
		return ();
}


void	BitcoinExchange::printRes(char *inputFile)
{
	std::ifstream				file;
	std::vector<std::string>	v[2];

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
		v = is_line_valid(line);
	file.close();
}