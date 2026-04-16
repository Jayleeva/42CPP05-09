#include "RPN.hpp"

RPN::RPN()
{
	//std::cout << YELLOW << "[RPN] : Default constructor called." << DEFAULT << std::endl;
}

RPN::RPN(RPN const &original)
{
	//std::cout << YELLOW << "[RPN] : Copy constructor called." << DEFAULT << std::endl;
	*this = original;
}

RPN &RPN::operator=(RPN const &original)
{
	if (this != &original)
	{
		this->expression = original.expression;
	}
	//std::cout << YELLOW << "[RPN] : Assignment operator overload called." << DEFAULT << std::endl;
	return (*this);
}

RPN::~RPN()
{
	//std::cout << YELLOW << "[RPN] : Default destructor called." << DEFAULT << std::endl;
}


std::string	trimSpaces(std::string arg)
{
	int	i = 0;
	while (arg[i] == ' ')
		i ++;
	arg = arg.substr(i, arg.size());

	int j = 0;
	while (arg[j])
	{
		int k = 0;
		while (arg[j + k] == ' ')
			k ++;
		if (k > 1)
		{
			k --;
			while (k)
			{
				arg.erase(j + k, 1);
				k --;
			}
		}
		j ++;
	}
	if (arg[j -1] != ' ')
		arg.push_back(' ');
	return (arg);
}
void	RPN::setQueue(std::string arg)
{
	arg = trimSpaces(arg);

	std::string			element;
    std::stringstream 	ss(arg);
	int					countdigit;
	int					n = 0;
	
	if (VERBIOSE)
		std::cout << YELLOW << "Cleaned expression : "<< DEFAULT << arg << std::endl;
	for (int i = 0; arg[i]; i++)
	{
		if (!isdigit(arg[i])
			&& arg[i] != '+' && arg[i] != '-'
			&& arg[i] != '/' && arg[i] != '*'
			&& arg[i] != ' ')
			throw InvalidArgumentException();
		n ++;
	}

	if (n < 2)
		return;

	if (n > 2 && n < 6)
		throw InvalidArgumentException();

	if (n > 2)
	{
		countdigit = 0;
		for (int i = 2; i < n; i+= 2)
		{
			if (arg[i] && !isdigit(arg[i]))
			{
				int countop = 0;
				int j = 0;
				while (arg[i + j] && (!isdigit(arg[i + j])))
				{
					countop ++;
					j += 2;
				}
				if (countdigit != countop)
				{
					throw InvalidArgumentException();
				}
				countdigit = 0;
				i += j - 2;
			}
			else
			{
				countdigit ++;
			}
		}
	}

	if (n > 2 && isdigit(arg[n -2]))
		throw InvalidArgumentException();

    while (getline(ss, element, ' '))
		this->expression.push(element);
}

std::queue<std::string>	RPN::getQueue() const
{
	return (this->expression);
}

void	fill_number(t_number *n, long value)
{
	n->value = value;
	n->full = true;
}


long	operate(t_data *data)
{
	long	res = data->operand.value;

	if (VERBIOSE)
		std::cout << data->operand.value << " " << data->op << " " << data->operated.value;

	if (data->op == '+')
		res += data->operated.value;
	else if (data->op == '-')
		res -= data->operated.value;
	else if (data->op == '/')
	{
		if (data->operated.value == 0)
			throw DivisionByZeroException();
		res /= data->operated.value;
	}
	else if (data->op == '*')
		res *= data->operated.value;

	if (VERBIOSE)
		std::cout << " = " << res << std::endl;
	return (res);
}

void	initialize_data(t_data *data)
{
	data->operand.value = 0;
	data->operated.value = 0;
	data->operand.full = false;
	data->operated.full = false;
	data->op = ' ';
}

void	RPN::printRes()
{
	t_data		data;
	std::string	str;
	long		res;
	long		tmpres;
	char		c;

	initialize_data(&data);

	if (this->expression.size() <= 1)
	{
		c = *this->expression.front().c_str();
		if (isdigit(c))
		{
			std::cout << c << std::endl;
			return ;
		}
		else
			throw InvalidArgumentException();
	}

	if (this->expression.size() < 3)
		throw InvalidArgumentException();

	int	i = 0;
	int countdigit = 0;
	//int countop = 0;
	while (this->expression.size())
	{
		c = *this->expression.front().c_str();

		if ((i == 0 || i == 1) && !isdigit(c))
			throw InvalidArgumentException();

		if (isdigit(c))
		{
			countdigit = 0;
			while (isdigit(c))
			{
				str.push_back(*this->expression.front().c_str());
				countdigit ++;
				i ++;
				this->expression.pop();
				c = *this->expression.front().c_str();
			}
			if (countdigit == 1)
			{
				if (i > 1)
				{
					fill_number(&data.operand, res);
					fill_number(&data.operated, static_cast<long>(*(str.end() -1) - '0'));
					str.erase(str.end() -1);
					data.op = c;
					this->expression.pop();
					res = operate(&data);
					fill_number(&data.operand, res);
					data.operated.full = false;
				}
				else
					throw InvalidArgumentException();
			}

			if (countdigit >= 2)
			{
				t_data	newdata;
				fill_number(&newdata.operated, static_cast<long>(*(str.end() -1) - '0'));
				str.erase(str.end() -1);
				fill_number(&newdata.operand, static_cast<long>(*(str.end() -1) - '0'));
				str.erase(str.end() -1);
				newdata.op = c;
				this->expression.pop();
				tmpres = operate(&newdata);
				initialize_data(&newdata);

				countdigit -= 2;

				std::string opstr;
				while (countdigit)
				{
					while (!isdigit(c) )
					{
						opstr.push_back(*this->expression.front().c_str());
						this->expression.pop();
						c = *this->expression.front().c_str();
					}
					fill_number(&newdata.operated, tmpres);
					fill_number(&newdata.operand, static_cast<long>(*(str.end() -1) - '0'));
					newdata.op = *(opstr.begin());
					str.erase(str.end() -1);
					opstr.erase(opstr.begin());
					//this->expression.pop();
					tmpres = operate(&newdata);
					initialize_data(&newdata);

					countdigit--;
				}
				if (!data.operand.full)
					fill_number(&data.operand, tmpres);
				else if (data.operand.full && !data.operated.full)
					fill_number(&data.operated, tmpres);

				std::cout << "data.operand = " << data.operand.value << " data.operated = " << data.operated.value << std::endl;
			}
		}
		else
		{			
			if (data.operand.full && data.operated.full)
			{
				data.op = c;
				this->expression.pop();
				res = operate(&data);
				initialize_data(&data);
				fill_number(&data.operated, res);
				i ++;
			}
			else
				throw InvalidArgumentException();
		}
	}
	if (data.operand.full && !data.operated.full)
		res = tmpres;
	if (VERBIOSE)
		std::cout << YELLOW << "Result : " << DEFAULT;
	std::cout << res << std::endl; 
}
