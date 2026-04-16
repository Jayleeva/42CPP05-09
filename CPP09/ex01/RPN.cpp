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

void	RPN::setQueue(std::string arg)
{

	std::string			element;
    std::stringstream 	ss(arg);
	int					n = 0;
	
	for (int i = 0; arg[i]; i++)
	{
		if (!isdigit(arg[i])
			&& arg[i] != '+' && arg[i] != '-'
			&& arg[i] != '/' && arg[i] != '*'
			&& arg[i] != ' ')
			throw InvalidArgumentException();
		n ++;
	}

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
		std::cout << data->operand.value << " " << data->op << " " << data->operated.value << " = " << res << std::endl;
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

	if (this->expression.empty())
		throw InvalidArgumentException();

	ssize_t	size = this->expression.size();
	if (size <= 1)
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

	if (size < 3)
		throw InvalidArgumentException();

	int	i = 0;
	int countdigit = 0;
	while (!this->expression.empty())
	{
		c = *this->expression.front().c_str();

		if (isdigit(c))
		{
			countdigit = 0;
			while (isdigit(c))
			{
				str.push_back(*this->expression.front().c_str());
				countdigit ++;
				i ++;
				this->expression.pop();
				if (this->expression.empty())
					throw InvalidArgumentException();
				c = *this->expression.front().c_str();
			}
			if (countdigit == 1)
			{
				if (i > 1)
				{
					if (data.operand.full && data.operated.full)
					{
						long tmp = data.operand.value;
						fill_number(&data.operand, data.operated.value);
						fill_number(&data.operated, static_cast<long>(*(str.end() -1) - '0'));
						str.erase(str.end() -1);
						data.op = c;
						this->expression.pop();
						res = operate(&data);
						initialize_data(&data);
						fill_number(&data.operand, tmp);
						fill_number(&data.operated, res);
					}
					else
					{
						fill_number(&data.operand, res);
						fill_number(&data.operated, static_cast<long>(*(str.end() -1) - '0'));
						str.erase(str.end() -1);
						data.op = c;
						this->expression.pop();
						res = operate(&data);
						if (!data.operand.full)
							fill_number(&data.operand, res);
						else if (data.operand.full && !data.operated.full)
							fill_number(&data.operated, res);
					}
				}
				else
					throw InvalidArgumentException();
			}

			if (countdigit >= 2)
			{
				t_data	newdata;
				initialize_data(&newdata);

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
					fill_number(&newdata.operated, tmpres);
					fill_number(&newdata.operand, static_cast<long>(*(str.end() -1) - '0'));
					if (this->expression.empty())
						throw InvalidArgumentException();
					newdata.op = *this->expression.front().c_str();
					this->expression.pop();
					str.erase(str.end() -1);
					tmpres = operate(&newdata);
					initialize_data(&newdata);

					countdigit--;
				}
				if (!data.operand.full)
					fill_number(&data.operand, tmpres);
				else if (data.operand.full && !data.operated.full)
					fill_number(&data.operated, tmpres);
				else
				{
					fill_number(&newdata.operand, data.operated.value);
					fill_number(&newdata.operated, tmpres);
					newdata.op = c;
					if (!this->expression.empty())
						this->expression.pop();
					tmpres = operate(&newdata);
					initialize_data(&newdata);
					fill_number(&data.operated, tmpres);
				}
				res = tmpres;
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
				//fill_number(&data.operated, res);
				i ++;
			}
			else
				throw InvalidArgumentException();
		}
	}
	if (data.operand.full && data.operated.full && data.op == ' ')
		throw InvalidArgumentException();
	if (VERBIOSE)
		std::cout << YELLOW << "Result : " << DEFAULT;
	std::cout << res << std::endl; 
}
