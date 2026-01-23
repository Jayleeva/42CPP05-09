#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
//# include <bits/stdc++.h>
//# include <ctime>
# include <algorithm>
# include <map>
# include <vector>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

void bitcoin(std::map<std::string, int> lines);

class	BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &original);
		BitcoinExchange &operator=(BitcoinExchange const &original);
		~BitcoinExchange();

		std::map<std::string, float>	getMap() const;
		void							setMap(std::string dataFile);
		void							printRes(char *inputFile);
 
	private:
		std::map<std::string, float>	dataLines;
};

float	find_closest(std::string key, std::map<std::string, float> data);
float	is_line_valid(std::string line, std::string key, std::string value, std::map<std::string, float> data);
int		is_value_valid(std::string value);
int		unexpectedchar(int sign, std::string value);
int		is_key_valid(std::string key);
int		is_day_valid(std::string day, int month, int year);
int		is_month_valid(std::string month, int year);
int		is_year_valid(std::string year);
int		is_year_bissextile(int year);
int		is_valid(int date, int min, int max);

#endif