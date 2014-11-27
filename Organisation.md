Chef de groupe
==============

- Nabil Boutemeur

Codeurs
=======

- Adrien Bono
- Imade Benrouijal
- Simon Berda

Testeur
=======

- Nabil Boutemeur

Implémentation
==============

On commence par la classe v2 jusque ce qu'on ai des details sur GetSuivant(), et on utilisera des smart pointer quand les methodes seront fonctionnels.

## Types ##

Simon doit implémenter les types suivants:

- [ ] value_type
- [ ] allocator_type
- [ ] reference
- [ ] const_reference
- [ ] pointer	
- [ ] const_pointer

Pour implementer les type iterator, tu dois implementer la classe node_iterator (voir Aide.md)
- [ ] iterator
- [ ] const_iterator
- [ ] reverse_iterator
- [ ] const_reverse_iterator
- [ ] difference_type
- [ ] iterator_traits
- [ ] size_type

Simon, et Simon seulement et *seulement ca*, _ni plus ni moins_!


## Méthodes ##

Adrien doit implementer:

- [ ] constructeur
Le constructeur cree une seule sentinelle, dont le base_node suivant est lui-meme et son precedent pointe aussi sur lui meme
- [ ] destructeur
le destructeur appelle clear
- [ ] Implementer les smart pointers
- [ ] Implementer une allocation custom

Imade:

- [ ] begin
- [ ] end
- [ ] empty
doit renvoyer vrai si le suivant de la sentinelle est lui meme
- [ ] size
doit mesurer la taille a chaque execution, necessaire pour reduire la complexitee de splice
- [ ] max_size
renvoie std::numeric_limits<size_type>::max()
- [ ] clear
execute erase sur begin() tant que begin ne vaut pas end
- [ ] erase
demande au neoeud de se detacher de la liste et libere le noeud

## Classes ##

Simon:
- [ ] node_iterator
Doit definir tout les type de iterator:
http://www.cplusplus.com/reference/iterator/iterator/
- [ ] const_node_iterator

Imade:
- [x] node

*Changement !* : la struct node doit etre separee en 2 classes, une
 node_base qui contient seulement les pointeurs next et prev et une classe node qui
 herite publiquement de node base, pour ne pas avoir a stocker de valeur pour les
 sentinelles
Les methode de node migrent vers base_node, et y ajouter unhook, qui decroche un maillon de la chaine