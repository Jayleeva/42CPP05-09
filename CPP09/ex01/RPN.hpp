#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <string>
# include <bits/stdc++.h>
# include <queue>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class RPN
{
	public:
		RPN();
		RPN(RPN const &original);
		RPN &operator=(RPN const &original);
		~RPN();

		void					setQueue(std::string arg);
		std::queue<std::string>	getQueue() const;
		void					printRes();
	private:
		std::queue<std::string>	expression;

};

double	operate_front(double res, std::string element);
#endif
