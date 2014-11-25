Aide pour l'implementation
==========================

node_iterator et node sont des classes génériques interne à List (declarez les a l'interieur de celle ci)

## Classe node ##

La `struct node` contient simplement 2 pointeurs, vers les node suivant et precedant appelé next et prev.
Elle contient aussi un objet de type T appelé data.

## Classe node_iterator ##

Comme tout ses membre doivent etre public, on utilisera la mot cle struct pour la declarer

La classe node_iterator est une classe generique qui defini plusieurs types:
- difference_type
- iterator_category
- value_type
- pointer
- reference

Elle possede un constructeur par defaut, qui initialize un pointeur vers struct node qui contient 2 pointeurs (next et previous, les elements suivant et precedent de la liste),
Et un autre constructeur qui peut prendre en parametre un pointeur vers cette structure

Elle a pour seul membre un pointeur vers struct node, appelé node_ptr;

Ensuite, cette classe doit se comporter comme un iterateur normal, il faut donc surcharger les operateurs *, ->, ++ et -- (post et pre) et les operateur de comparaison == et <.
La classe const_node_iterator est une version const.
La STL fourni des templates pour les reverse_iterator, sa devrait pas poser de probleme.
Ces classes devrait etre implementer comme sous classes publique de List, ou bien comme classe a part entiere, a debattre.

Les iterateur se comporte a peu pres comme des pointeurs.
Il est donc necessaire de surcharger les operateurs ++ --, que vous avez vu en cours,
et l'operateur unaire * et ->.

L'iterateur itere sur des objets du type T (generique), et avance et recule en utilisant les pointeur de la structure node (next et prev), par exemple, it++ passe a l'objet suivant de la liste.

La surcharge de l'operateur * doit renvoyer une reference a l'objet du noeud iteré (le membre data du noeud), pour pouvoir le modifier.

Utilise alors le typedef reference pour ecrire le profil:

reference operator*() noexcept;

Il est aussi necessaire d'ecrire une version const de la surcharge:

const reference operator*() const noexcept;


## Constructeur de List ##

List possede un constructeur par defaut qui ne peut lever une exception que si le constructeur de la classe contenue dans la liste peut lever une exception.
Cela sera implementer plus tard, pour l'instant ecriver des constructeur lambdas.

