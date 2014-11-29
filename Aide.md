Standard C++: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3242.pdf

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

## Classe list ##

Il est prevu a l'heure d'ecriture de ces ligne, d'implementer tout les membres present sur http://www.cplusplus.com/reference/list/list/ sauf ceux de la categorie Operation, et les midifier emplace* et assign,
qui seront implemente apres les smart pointer

La classe list a pour seule donnee membre un base_node qui est la sentinelle de la liste, elle est initialisee dans le constructeur telle que son suivant et son precendent pointent vers lui meme
La fonction size() recalcule a chaque appel la taille de la liste. Cela peut sembler lourd, mais quand il s'agit d'utiliser splice pour manipuler la liste, maintenir une variable de longueur est bien plus lourd,
et de plus, tout les algorithme fonctionnant sur les type de conteneur liste chainee le traite de maniere sequentielle.

### operateur -> ###

L'operateur -> renvoie l'adresse du membre sur lequel l'utilisateur veut recuperer un membre
Par exemple, une classe A ayant pour membre b, une instance de B ayant elle pour membre a c et -> surchargée dans A,
une instance a de A, alors l\operatuer permet d'acceder aux membre c de b en renvoyant un pointeur vers b

## swap ##

Swap prend une reference vers une list, et echange leur sentinelle.

## resize ##

Resize prend en parametre une taille de liste _n_, et une const value_type& qui a comme valeur par defaut T()
la fonction navigue jusqua n noeud et supprime les node de la jusque la fin de la liste.
Si on atteint la fin de la liste avant d'avoir traverser n noeud, alors on ajoute (n - nombre de noeud traversé) en recopiant le second parametre

## splice ##

splice sert a transferer des element d'une liste a l'autre, on va seulement implementer  3 de la surchage, autre surcharge, et certain constructeur
peuvent alors etre implementer avec cette methode

### transfer ###

pour implementer splice, on doit implementer transfer, qui prend en parametre 2 iterateur (first et last), indiquant une portion de liste, avec la borne inferieur incluse et la borne sup excluse.
et la deplace avant lui meme. donc concretement il y a 7 operation:
- Le noeud suivant du noeud precedent de last devient celui qui a appelé transfer (this) 
- Le noeud suivant du noeud precedent de first devient last (permet de refermer la portion de liste dans un sens)
- Le noeud suivant du noeud precedent du noeud qui a appeler transfer (this) devient first
- Sauvegarder le noeud precedant de l'appelant (this)
- Le noeud precedent de l'appelant devien le precedent de last
- Le noeud precedent de last devient le precedent de first (referme la portion de la liste dans l'autre sens)
- Le noeud precedent de first devient celui qui a ete sauvegardé plus haut, l'ancien noeud precedant de l'apelant

La fonction ne doit rien faire si last pointe le meme noeud que le noeud appelant, puisque l'action est deja faite

## reverse ##

la classe base node doit avoir une methode reverse qui sera appelee par la classe liste sur sa sentinelle
elle doit sauvegarder un pointeur sur le noeud, puis dans une boucle, echanger (swap) son pointeur precedent et son suivant.
vu que le noeud suivant devient le precedent, on itere dans la liste en l'assignant a son precedent

## unique ##

Supprime les element identique consécutif.
You should be able to solve that.

## sort ##

sort doit etre implémentée specialement pour cette classe, on ne peut utiliser
une fonction standard ou un tri basique qui requiert que la complexité soit
constante O(1) pour l'acces au elements

http://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
Implementez cet algo, remplacez dans votre tete null par "sentinelle"

## remove ##
## remove_if ##

J-Je peux vo-vous faire confiance la dessus, hein ?

## merge ##

merge prend en parametre une liste triée !!! et la liste qui apelle merge doit l'etre aussi !!!
Si l'une des deux n'est pas triée alors on a un comportement indefini
Mais bon, c'est a l'utilisateur de trier la liste, donc sa nous concerne pas :^)

L'algorithme de merge est lineaire, et plutot simple a mettre en place.

Soit 2 liste,
1 2 3
4 5 6

Leur merge donne 1 2 3 4 5 6

1 1 2 2 4 4 et
3 3 5 5

donne 1 1 2 2 3 3 4 4 5 5
Les maillons contenant des element identiques gardent le meme ordre

Aussi, la liste passée en parametre est vidée, puisque tout ses element seront transferer

## assign ##

Assign remplace le contenu d'une liste par celui d'une autre.
Pour economiser des allocation de memoire et dellocation, on ne supprime que ce qui a en trop, et
n'ajoute que ce qui manque.
