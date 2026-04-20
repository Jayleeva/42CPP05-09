#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <map>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

typedef struct s_date
{
	int	year;
	int	month;
	int	day;
}		t_date;

class	BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &original);
		BitcoinExchange &operator=(BitcoinExchange const &original);
		~BitcoinExchange();

		std::map<std::string, float>	getMap() const;
		int								setMap(std::string dataFile);
		void							printRes(char *inputFile);

	private:
		std::map<std::string, float>	dataLines;
		t_date							min_date;
};


float		getRate(std::string key, std::map<std::string, float> data);
std::string	getKey(std::string line);
std::string	getValue(std::string line);
int			is_value_valid(std::string value);
int			has_dot(int sign, std::string value);
int			is_key_valid(std::string key, t_date min_date);
int			is_day_valid(std::string day, int month, int year, t_date min_date);
int			is_month_valid(std::string month, int year, t_date min_date);
int			is_year_valid(std::string year, t_date min_date);
int			is_year_bissextile(int year);
int			is_valid(int date, int min, int max);

#endif