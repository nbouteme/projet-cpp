#pragma once 
#include <cstddef> // ptrdiff_t
template<typename T>
class node_iterator
{
    public:
	

		
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
	

		node_iterator::operator+()(node_iterator a, node_iterator b)
		{
			// WIP
		}
		

		node_iterator::operator*() (node_iterator a, node_iterator b)
		{
		// WIP
		}

		node_iterator::operator->() (node_iterator a, node_iterator b)
		{
		// WIP
		}

		node_iterator::operator==() (node_iterator a, node_iterator b)
		{
		// WIP
		}
		

		node_iterator::operator<() (node_iterator a, node_iterator b)
		{
		// WIP
		}

};


