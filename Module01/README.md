# C++ Module 01

Ce module introduit l'allocation memoire, les pointeurs, les references,
les pointeurs sur fonctions membres et l'instruction `switch` en C++98.

## Compilation

Chaque exercice possede son propre `Makefile` et doit compiler avec :

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

Pour compiler un exercice :

```bash
cd ex00
make
```

Commandes communes a tous les `Makefile` :

- `make` ou `make all` : compile l'exercice ;
- `make clean` : supprime les fichiers objets ;
- `make fclean` : supprime les objets et l'executable ;
- `make re` : recompile entierement l'exercice.

## ex00 - BraiiiiiiinnnzzzZ

**Etat : termine**

Creation d'une classe `Zombie` avec un nom et une methode `announce()`.

Classes et fonctions :

- `Zombie(std::string name)` initialise le nom du zombie ;
- `~Zombie()` annonce sa destruction ;
- `Zombie::announce()` affiche `<name>: BraiiiiiiinnnzzzZ...` ;
- `newZombie()` cree et retourne un zombie sur le tas avec `new` ;
- `randomChump()` cree un zombie sur la pile et appelle `announce()`.

Notions utilisees : allocation sur la pile et sur le tas, `new`, `delete`,
constructeur, destructeur et duree de vie des objets.

Utilisation :

```bash
cd ex00
make
./zombie
```

Le zombie local est detruit automatiquement a la fin de `randomChump()`. Le
zombie alloue avec `new` est libere explicitement avec `delete`.

Fichiers : `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`,
`newZombie.cpp`, `randomChump.cpp`.

## ex01 - Moar brainz!

**Etat : termine**

Creation d'une horde de `N` zombies en une seule allocation :

```cpp
Zombie* horde = new Zombie[N];
```

Classe et fonctions :

- `Zombie()` permet de creer un tableau de zombies ;
- `~Zombie()` annonce la destruction de chaque zombie ;
- `Zombie::setName()` attribue le meme nom a chaque element ;
- `Zombie::announce()` affiche le nom du zombie ;
- `zombieHorde(int N, std::string name)` alloue et initialise la horde ;
- la fonction retourne `NULL` lorsque `N` est inferieur ou egal a zero.

Notions utilisees : allocation d'un tableau avec `new[]`, initialisation de ses
elements, parcours par indice et liberation avec `delete[]`.

Utilisation :

```bash
cd ex01
make
./zombieHorde
```

Le programme de test cree cinq zombies, appelle `announce()` sur chacun, puis
libere toute la horde.

Fichiers : `Makefile`, `main.cpp`, `Zombie.hpp`, `Zombie.cpp`,
`zombieHorde.cpp`.

## ex02 - HI THIS IS BRAIN

**Etat : termine**

Comparaison entre une variable, un pointeur et une reference vers la meme chaine.

```cpp
std::string string = "HI THIS IS BRAIN";
std::string* stringPTR = &string;
std::string& stringREF = string;
```

Les trois adresses affichees sont identiques, ainsi que les trois valeurs.

Classes et fonctions : aucune classe personnelle. Tout le test se trouve dans
`main()` et utilise `std::string` ainsi que `std::cout`.

Notions utilisees : adresse avec `&`, pointeur avec `*`, dereferencement avec
`*stringPTR` et reference avec `std::string&`.

Utilisation :

```bash
cd ex02
make
./brain
```

Le programme affiche d'abord les trois adresses, puis les trois valeurs.

Fichiers : `Makefile`, `main.cpp`.

## ex03 - Unnecessary violence

**Etat : termine**

Creation des classes `Weapon`, `HumanA` et `HumanB`.

Classes et fonctions :

- `Weapon(std::string type)` initialise le type de l'arme ;
- `Weapon::getType()` retourne une reference constante vers son type ;
- `Weapon::setType()` modifie le type de l'arme ;
- `HumanA(std::string name, Weapon& weapon)` exige une arme des sa creation ;
- `HumanA::attack()` utilise la reference vers son arme ;
- `HumanB(std::string name)` peut etre cree sans arme ;
- `HumanB::setWeapon()` enregistre l'adresse d'une arme ;
- `HumanB::attack()` utilise l'arme si son pointeur n'est pas `NULL`.

Une reference :

- doit toujours etre initialisee ;
- ne peut pas etre `NULL` ;
- ne peut pas changer pour viser une autre arme ;
- `HumanA` a toujours une arme.

Un pointeur :

- peut etre `NULL` ;
- peut recevoir une arme plus tard ;
- peut changer pour pointer vers une autre arme ;
- `HumanB` peut exister sans arme au debut.

| `HumanA` | `HumanB` |
|---|---|
| Stocke `Weapon&` | Stocke `Weapon*` |
| Arme obligatoire | Arme facultative |
| Arme donnee au constructeur | Arme donnee plus tard |
| Utilise `weapon.getType()` | Utilise `weapon->getType()` |
| Ne peut pas etre `NULL` | Peut etre `NULL` |

```cpp
Weapon objet("club");
objet.getType();       // objet normal

Weapon& reference = objet;
reference.getType();   // reference

Weapon* pointer = &objet;
pointer->getType();    // pointeur
```

Notions utilisees : differences entre pointeur et reference, liste
d'initialisation du constructeur, pointeur nul, passage par reference et retour
par reference constante.

Utilisation :

```bash
cd ex03
make
./violence
```

Le changement effectue avec `Weapon::setType()` est visible par `HumanA` et
`HumanB`, car ils utilisent tous les deux le meme objet `Weapon`.

Fichiers : `Makefile`, `main.cpp`, `Weapon.hpp`, `Weapon.cpp`,
`HumanA.hpp`, `HumanA.cpp`, `HumanB.hpp`, `HumanB.cpp`.

## ex04 - Sed is for losers

**Etat : termine**

Le programme recoit un nom de fichier et deux chaines `s1` et `s2`. Il copie le
contenu dans `<filename>.replace` en remplacant chaque occurrence de `s1` par
`s2`, sans utiliser `std::string::replace` ni les fonctions de fichiers du C.

Classes et fonctions :

- aucune classe personnelle n'est necessaire ;
- `main()` valide les arguments, ouvre les fichiers et gere les erreurs ;
- `writeReplaced()` cherche les occurrences et ecrit le contenu transforme ;
- `std::ifstream` lit le fichier source ;
- `std::ofstream` cree le fichier de sortie ;
- `std::ostringstream` rassemble tout le contenu en memoire ;
- `std::string::find()`, `substr()` et `length()` effectuent le remplacement.

Notions utilisees : flux de fichiers C++, validation d'entrees, manipulation de
chaines et verification des erreurs de lecture et d'ecriture.

Fichiers : `Makefile`, `main.cpp`.

Utilisation :

```bash
cd ex04
make
./replace <filename> <s1> <s2>
```

Exemple :

```bash
echo "bonjour bonjour" > test.txt
./replace test.txt bonjour salut
cat test.txt.replace
```

Resultat :

```text
salut salut
```

Fonctionnement :

1. Verifier qu'il y a exactement trois arguments et que `s1` n'est pas vide.
2. Ouvrir le fichier source avec `std::ifstream`.
3. Lire son contenu avec un `std::ostringstream`.
4. Creer le fichier `<filename>.replace` avec `std::ofstream`.
5. Chercher chaque occurrence avec `std::string::find()`.
6. Ecrire les morceaux avec `substr()` et inserer `s2` entre eux.

Le programme gere les fichiers vides, les occurrences multiples ou absentes,
un `s2` vide et les erreurs d'ouverture, de lecture ou d'ecriture.

## ex05 - Harl 2.0

**Etat : termine**

Creation d'une classe `Harl` avec quatre niveaux : `DEBUG`, `INFO`, `WARNING`
et `ERROR`. Chaque niveau correspond a une methode privee qui affiche un message.

Classe et fonctions :

- `Harl::debug()` affiche le message de diagnostic ;
- `Harl::info()` affiche le message d'information ;
- `Harl::warning()` affiche le message d'avertissement ;
- `Harl::error()` affiche le message d'erreur ;
- `Harl::complain(std::string level)` selectionne et appelle la bonne methode ;
- `main()` teste tous les niveaux ou ceux passes en arguments.

La methode publique `complain(std::string level)` cherche le niveau dans un
tableau, puis appelle la methode correspondante grace a un pointeur sur fonction
membre :

```cpp
typedef void (Harl::*Complaint)(void);

Complaint complaints[4] = {
	&Harl::debug,
	&Harl::info,
	&Harl::warning,
	&Harl::error
};

(this->*complaints[i])();
```

Cette solution evite une longue suite de `if/else if`.

Notions utilisees : pointeur sur fonction membre, `typedef`, tableau de chaines,
tableau de methodes et operateur `->*`.

Utilisation :

```bash
cd ex05
make
./harl
./harl DEBUG WARNING ERROR
```

Sans argument, le programme teste les quatre niveaux. Avec des arguments, il
affiche uniquement les niveaux valides demandes. Un niveau inconnu est ignore.

Fichiers : `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.

## ex06 - Harl filter

**Etat : termine (bonus facultatif pour valider le module)**

Cet exercice reprend les quatre niveaux de la classe `Harl` de l'ex05 et ajoute
un filtre. Le programme recoit exactement un niveau en argument et affiche le
message de ce niveau ainsi que tous les niveaux superieurs :

Classe et fonctions :

- `Harl::debug()`, `info()`, `warning()` et `error()` affichent leur titre et
  leur message ;
- `Harl::complain()` convertit le niveau en indice, puis applique le filtre ;
- `main()` exige exactement un argument et appelle `complain()`.

- `DEBUG` affiche `DEBUG`, `INFO`, `WARNING` et `ERROR`.
- `INFO` affiche `INFO`, `WARNING` et `ERROR`.
- `WARNING` affiche `WARNING` et `ERROR`.
- `ERROR` affiche uniquement `ERROR`.

Utilisation :

```bash
cd ex06
make
./harlFilter WARNING
```

Pour un niveau inconnu, le programme affiche :

```text
[ Probably complaining about insignificant problems ]
```

Le filtrage doit obligatoirement utiliser une instruction `switch`. La cascade
entre les `case`, sans `break` intermediaire, permet d'afficher le niveau choisi
et tous les niveaux suivants.

Notions utilisees : `switch`, cascade volontaire entre les `case`, pointeurs sur
fonctions membres et validation des arguments.

L'executable doit s'appeler `harlFilter`.

Fichiers demandes : `Makefile`, `main.cpp`, `Harl.hpp`, `Harl.cpp`.

## Regles importantes

- Utiliser le standard C++98.
- Ne pas utiliser `printf`, `malloc`, `calloc`, `realloc` ou `free`.
- Ne pas utiliser `using namespace` ni `friend`.
- Ne pas utiliser les conteneurs STL ni `<algorithm>` dans ce module.
- Verifier les allocations et les fuites memoire.
- Les en-tetes doivent avoir des gardes contre la double inclusion.
- La Norminette ne s'applique pas aux modules C++, mais le code doit rester clair.
