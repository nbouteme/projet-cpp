Aide pour l'implementation
==========================

## Classe node_iterator ##

Comme tout ses membre doivent etre public, on utilisera la mot cle struct pour la declarer

La classe node_iterator est une classe generique qui defini plusieurs types:
- difference_type
- iterator_category
- value_type
- pointer
- reference

Elle possede un constructeur par defaut, qui initialize une struct node qui contient 2 pointeurs (next et previous, les elements suivant et precedent de la liste), et un membre data qui contient les donnees
Et un autre constructeur qui peut prendre en parametre cette structure

Ensuite, cette classe doit se comporter comme un iterateur normal, il faut donc surcharger les operateurs *, ->, ++ et -- (post et pre) et les operateur de comparaison == et <.
La classe const_node_iterator est une version const.
La STL fourni des templates pour les reverse_iterator, sa devrait pas poser de probleme.
Ces classes devrait etre implementer comme sous classes publique de List, ou bien comme classe a part entiere, a debattre.


## Constructeur de List ##

List possede un constructeur par defaut qui ne peut lever une exception que si le constructeur de la classe contenue dans la liste peut lever une exception.
Cela sera implementer plus tard, pour l'instant ecriver des constructeur lambdas.

