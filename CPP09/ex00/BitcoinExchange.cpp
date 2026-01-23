#include "BitcoinExchange.hpp"

void	print_bitcoin(std::map<std::string, int> fileLines, std::map<std::string, int> dataLines)
{
	for (fileLines)
	{
		std::cout << filekey << " => " << lines[value] << " = " << () << std::endl; 
	}
}


void bitcoin(std::map<std::string, int> fileLines)
{
	std::ifstream				data;
	std::map<std::string, int>	dataLines;

	data.open("data.csv");
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
		value = atof(valuestr.c_str());
		dataLines.insert({key, value});
	}
	data.close();
	print_bitcoin(fileLines, dataLines);
}