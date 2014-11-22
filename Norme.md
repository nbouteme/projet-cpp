Style
=====

Convention de noms:

- Ne pas préfixer les noms de classes par C.
- Ne pas préfixer les noms des données membres par m_

Le style de code est le style Allman, c'est a dire que:
- Toute accolade délimitant un bloc d'instructions est seule sur sa ligne.
- Les lignes vides ne doivent pas contenir d'espaces.
- Une ligne vide doit suivre une ou plusieurs déclarations succesives.

Fonctionnalités du C++
======================

## Mot clé auto  ##

Le mot clé auto doit être utilisé pour simplifier une déclaration,
dont le type est long à taper, comme
`std::vector<string>::const_iterator`, pour améliorer la lisibilité.

## Header ##

Les fichiers headers doivent être dans le dossier include du projet,
vous pourrez donc les inclure dans vos fichiers source en utilisant
les <>
Lorsque vous incluez des headers dans un fichier cpp, faites les
inclusions dans cet ordre:
- Le header de la classe si applicable (A.hpp dans A.cpp par exemple)
- Les headers standard
- Les headers de bibliothèques tierces
- Les headers du projet
### Protection de multi-inclusion ###

Pour empêcher un fichier header d'être inclut plusieurs fois, on vous
a appris à définir des macros de compilation conditionnelles.

```
#ifndef __FILE_H__
#define __FILE_H__

#endif
```
Comme vous pouvez le voir, c'est long à taper, et force le
préprocesseur à lire tout le fichier pour savoir quelle partie du code
est affectée.  Un autre problème qui peut survenir lorsque un projet
grandit en taille, c'est la collision des noms, 2 headers avec le même
nom peuvent se trouver dans différents répertoires, et empêcher
l'inclusion de l'un. La méthode utilisé couramment pour contourner ce
problème est de faire des macros plus longues, ce qui devient plus
pénible. Aussi modifier le nom de fichier vous force aussi à modifier
son contenu.

`#ifndef __PATH_TO_FILE_H_`
...

Pour remédier à ces problèmes, utilisez `#pragma once` au début de vos
headers, c'est plus court, plus rapide à gérer pour le préprocesseur
et plus rapide à compiler.

Les puristes se plaindront que `#pragma once` n'est pas standard, et
n'est pas supporté par un certain compilateur d'IBM qui n'a pas eu de
mise à jour depuis presque 3 ans. Ces mêmes personnes déclarent des
tableau de type C de taille variable.

## Déclarations anticipées ##

Il peut arriver que des classes dépendent l'une sur l'autre pour leur
définitions.  La classe A utilise B comme argument a certaines de ses
méthodes, et B utilise A comme argument a certaines de ses méthodes, la
première initiative est d'inclure le header de B dans celui de A et le
header de A dans celui de B

Cela crée une dépendance circulaire, qui va faire que lorsque vous
compilerez A, B sera inclus, il essayera d'inclure A, mais échouera
car A ne pourra pas être inclus à cause de , faisant que B ne pourra
pas être défini, et fera échouer la compilation.

Pour éviter ce problème, vous devez utiliser des déclarations anticipées.
C'est à dire que vous déclarez que la classe B existe avant de définir
la classe A, et que vous inclurez le header B dans le .cpp de A.

`class B;`

Cela implique plusieurs choses. A ne doit pas hériter de B (Peu de
chance que sa arrive, une dépendance circulaire voudrait dire que vous
faite heriter A de B et B de A). Et A ne doit pas manipuler la classe
B et ses membres dans son header. Ce qui interdit la définitions de
méthodes dans la définition de classes.

Aussi, je vous invite (lire 'force') à utiliser les déclarations
anticipées même lorsque il n'y a pas de dépendances circulaires à
résoudre, car cela permet d'éviter d'inclure le header de B partout où
A est nécessaire, réduisant le temps de compilation du code.

Les déclarations anticipées ne sont pas utilisable dans un contexte où
vous avez besoin de connaître la définition d'une classe comme
l'héritage ou le passage de valeur par copie.
Vous ne pouvez donc que déclarer des pointeurs/références vers B dans
le header de A par exemple.

## Inline ##

La déclaration inline permet de remplacer un appel par le corps d'une
fonction.  En théorie.  En pratique, les fonction déclarer inline le
sont que si possible, une fonction virtuelle ne peut être inline, car
elle doit pouvoir être référencée dans la table virtuelle des classes
qui la manipule, ainsi que les fonction récursives, qui ont besoin de
manipuler la pile d'appels, un peu dur quand il y en a plus.  Lorsque
sa marche, le code est dupliqué partout ou un appel est
utilisé. Produisant de plus gros exécutables.  C'est pour sa qu'on ne
fera inline que des fonctions courtes. Les constructeurs et
destructeurs peuvent, mais ne doivent pas être rendu inline, car ils
appellent implicitement les constructeurs et destructeurs des membres.

Notez que lorsque vous définissez une méthode dans une définition de
classe dans un header, elle est implicitement inline.  Notez aussi que
lorsque vous déclarer des classes génériques, vous êtes obligés de
définir ses méthodes dans son header... Tirez en vos propres
conclusions.

## Explicit ##

Le mot clé `explicit` permet d'instancier une classe seulement si on a
utiliser son constructeur explicitement.  Prenons par exemple une
classe A qui a un constructeur prenant en paramètre une string.  Si ce
constructeur n'est pas explicit, une fonction prenant un A en
paramètre pourra aussi prendre une string en paramètre.  Ça peut être
pratique, mais c'est pas vraiment un comportement prévisible.  On
utilisera alors le mot clé explicit devant tout constructeur ne
prenant qu'un seul paramètre en argument.

## Délégation de constructeurs ##

Vous pouvez appeler des constructeurs dans des constructeurs d'une
même classe.  Prenons notre classe A, qui a un constructeur prenant un
int en paramètre et un autre prenant une string.

`A::A(string s) {...}`
`A::A(int i) : A("abc") {...}`

C'est légèrement diffèrent d'un argument par défaut vu que la routine
d'initialisation change aussi.

## Struct et Class ##

La différence entre struct et class en C++ est très fine. Elle ne
concerne que la visibilité des membre par défaut.  Ils sont private
dans une class et public dans une struct. C'est tout. Une struct peut
heriter d'une classe et une classe peut hériter d'une struct.

Mais par souci de sémantique, on utilisera struct pour définir des
objets qui ne contiennent soit que des données, soit qui servent
d'interface (purement abstraite), soit qui gardent des traits.
Et non pas une combinaison de 2 ou plus.

## Arguments par défauts ##

Les arguments par défaut ne doivent être utilisé que dans les constructeurs.

## Exceptions ##

Les exceptions simplifie le modèle de traitement d'erreur en propageant
des erreur d'exécutions vers le code appelant.  En théorie.  En
pratique, les exceptions produisent des exécutables plus gros, et a un
coût à l'exécution mémé si le code ne les mentionnent pas.  Dans un
langage qui gère automatiquement les ressources, dans un environnement
managé, lorsque vous faites une action interdite, comme accéder a un
index en dehors d'un tableau, une exception est levée, et vous pouvez
obtenir une pile d'appels et de contextes qui aide a trouver des bugs.

Le C++ n'offre rien de tout ça, un code C++ dit "exception-safe" ne
peut pas gérer les erreurs lors de la libération de ressources, et un
code exception-unsafe provoquera des fuites de mémoire. Vous perdez
aussi la pile d'appel et le contexte dans lequel l'exception c'est
faite levée.  Déréférencer un pointeur nul est littéralement plus
pratique que de lancer une exception, au moins vous avez un coredump.
Les exception du C++ sont incomparable a celles d'autre langages
véritablement orientés objet.  Lancer des exception dans un
destructeur est dangereux, un constructeur doit se contenter
d'initialiser les données, et doit faire le minimum de choses
possible.

Les exceptions sont désactivé, un appel à throw est donc remplacé par
un appel à std::terminate.  Ajoutez le mot clé `noexcept` au profil de
toute les methodes.

## Flux ##

N'utilisez pas cout/cerr, ou des flux en général.  Les flux sont plus
lent, et sont moins flexible que printf pour ce qui est de formatter
une sortie, ou de reordonner les arguments.

Par exemple, pour afficher un entier en héxadécimal, sous la forme
0xAABBCCDD, avec les 0 en tête:

`std::cout << std::hex << std::setfill('0') << std::setw(8) << x << std::dec << std::endl;`

contre

`printf("0x%08xn\n", x)`

Version 0.1

## Entiers ##

N'utilisez que int pour représenter un nombre entier quelconque.
Si vous avez besoin d'une taille spécifique, utilisez les types fournis par stdint.h
Le standard C++ ne spécifie pas exactement la taille des types entiers, seulement leurs capacités minimales.
En pratique, sur les 3 OS principaux, un char fait 8 bits, un short fait 16 bits et un int fait 32 bit.
Sur des systèmes type Unix, un long fait 64 bit, mais 32 bit sur Windows.
Utilisez seulement int pour des compteurs ou des nombres dont vous savez qu'ils ne pourrons pas atteindre la limite.
Sinon, utilisez int64_t.

### Entiers non-signés ###

N'utilisez pas d'entiers non signés pour indiquer qu'une valeur ne peut être négative. Utilisez des assert à la place.
Les entiers non-signés doivent être utilisé pour représenter des données brut ou des masques de bits.

Considérez cette boucle:

`for (unsigned int i = foo.Length()-1; i >= 0; --i)...`

Ce genre de bug est typiquement introduit par l'emploi d'entier non-signés.

