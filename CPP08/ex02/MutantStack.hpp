#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

template<typename T>
class MutantStack: public std::stack<T>
{
	public:
		MutantStack();
		MutantStack(MutantStack const &original);
		MutantStack &operator=(MutantStack const &original);
		~MutantStack();

		// Create aliases for the iterator types
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		reverse_iterator rbegin();
		reverse_iterator rend();

		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
};

//std::stack = type d'adaptateur de container, fonctionnant dans un contexte LIFO (ce qui est ajoute l'est a la fin, ce qui est retire l'est au debut du container).
// - utilise un objet encapsule d'une classe de container specifique comme container sous-jacent:
//    amene un set specifique de fonctions membres pour acceder a ses elements.
// - les elements sont push et pop depuis "le back" / le "top".
// - par defaut, le sous-jacent est un dequeue, mais peut aussi etre un vecteur ou une liste.


		/*bool empty() const;
		size_t size() const;
		value_type &top();
		const value_type &top() const;
		void push(const value_type &val);
		template <class...Args> void emplace(Args&&...args);
		void pop();
		void swap(MutantStack &x);*/

#endif