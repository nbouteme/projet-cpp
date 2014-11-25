#pragma once 
#include <cstddef> // ptrdiff_t
template<typename T> class node_iterator;
class node_iterator
{
    public:
	
		struct Node_Structure //Comme tout ses membre doivent etre public, on utilisera la mot cle struct pour la declarer
		{
			ptrdiff_t difference_type;
			//iterator_category?
			template<typename T>
			T value_type;
			T* pointer;// I Dunno
			T& reference;// I Dunno
			template<typename T>
			T Data; //The Data of the node
		};
		
		node_iterator::node_iterator() //Constructeur multiparametre
		{
			/*
			Elle possede un constructeur par defaut, qui initialize un pointeur vers struct node qui contient 2 pointeurs 
			(next et previous, les elements suivant et precedent de la liste), Et un autre constructeur qui peut prendre 
			en parametre un pointeur vers cette structure
			*/
		}
		
		node_iterator::node_iterator(struct Node_Structure) //Constructeur pointeur de structure
		{
			this->Node_Structure = Node_Structure;
		}
		
		

		node_iterator::~node_iterator() //Destructeur
		{
			//dtor
				
		}
	
		template <class node_iterator>
		node_iterator::operator+()(node_iterator a, node_iterator b)
		{
			// WIP
		}
		
		template <class node_iterator>
		node_iterator::operator*() (node_iterator a, node_iterator b)
		{
		// WIP
		}
		template <class node_iterator>
		node_iterator::operator->() (node_iterator a, node_iterator b)
		{
		// WIP
		}
		template <class node_iterator>
		node_iterator::operator==() (node_iterator a, node_iterator b)
		{
		// WIP
		}
		
		template <class node_iterator>
		node_iterator::operator<() (node_iterator a, node_iterator b)
		{
		// WIP
		}
		
		/*
			http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
			Increment and decrement have two forms, prefix (++i) and postfix (i++). 
			To differentiate, the postfix version takes a dummy integer. Increment and decrement operators are most often member functions, as they generally need access to the private member data in the class. 
			The prefix version in general should return a reference to the changed object. 
			The postfix version should just return a copy of the original value. In a perfect world, A += 1, A = A + 1, A++, ++A should all leave A with the same value.	
		*/
		
		SomeValue& SomeValue::operator++() // prefix
		{
			
			//la preincrementation passe au noeud suivant et renvoie une reference
			
			
		
			++data;
			return *this;
		}
 
		SomeValue SomeValue::operator++(int unused) // postfix
		{
			//la post incrementation renvoie une copie de l'iterateur, puis passe l'iterateur au noeud suivant.

			SomeValue result = *this;
			++data;
			return result;
		}
		
		
		SomeValue& SomeValue::operator--() // prefix
		{
			//la preincrementation passe au noeud suivant et renvoie une reference
			--data;
			return *this;
		}
 
		SomeValue SomeValue::operator--(int unused) // postfix
		{
			//la post incrementation renvoie une copie de l'iterateur, puis passe l'iterateur au noeud suivant.
			SomeValue result = *this;
			--data;
			return result;
		}
		
		
		
		
		
		template <class node_iterator>
		bool are_equal (node_iterator node1, node_iterator node2)
		{
			//WIP
		}
		
		template <class node_iterator>
		bool is_lower (node_iterator node1, node_iterator node2)
		{
			//WIP
		}

		template <class node_iterator>
		bool is_bigger (node_iterator node1, node_iterator node2)
		{
			//WIP
		}   

    protected:
    private:
};


