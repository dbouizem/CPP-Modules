# CPP Module 03 - Inheritance

Ce module introduit l'heritage en C++ avec une famille de classes :

```text
ClapTrap
  |
  +-- ScavTrap
  |
  +-- FragTrap

ScavTrap + FragTrap
        |
        +-- DiamondTrap
```

Le but est de comprendre comment une classe peut reutiliser le code d'une autre classe,
comment les constructeurs/destructeurs s'enchainent, et pourquoi l'heritage multiple
peut creer des problemes si on ne le gere pas correctement.

## 1. Heritage simple

L'heritage permet de creer une classe a partir d'une autre.

Exemple :

```cpp
class ScavTrap : public ClapTrap
{
};
```

Cela veut dire :

```text
ScavTrap est un ClapTrap specialise.
```

`ScavTrap` recupere les attributs et fonctions de `ClapTrap`, selon leur visibilite.

Dans ce module :

```text
ex00 : ClapTrap seul
ex01 : ScavTrap herite de ClapTrap
ex02 : FragTrap herite de ClapTrap
ex03 : DiamondTrap herite de ScavTrap et FragTrap
```

## 2. Classe parent et classe enfant

La classe parent est la classe de base.

Dans ce module :

```text
ClapTrap = classe parent
ScavTrap = classe enfant de ClapTrap
FragTrap = classe enfant de ClapTrap
DiamondTrap = classe enfant de ScavTrap et FragTrap
```

Quand on cree un objet enfant, C++ construit d'abord la partie parent.

Exemple :

```cpp
ScavTrap scav("Serena");
```

Ordre de construction :

```text
ClapTrap constructor
ScavTrap constructor
```

Ordre de destruction :

```text
ScavTrap destructor
ClapTrap destructor
```

La destruction se fait dans l'ordre inverse de la construction.

## 3. public, protected, private

Ces mots controlent l'acces aux attributs et fonctions.

### private

Accessible seulement dans la classe elle-meme.

```cpp
class ClapTrap
{
private:
	std::string _name;
};
```

Si `_name` est `private`, `ScavTrap` ne peut pas y acceder directement.

### protected

Accessible dans la classe elle-meme et dans les classes enfants.

```cpp
class ClapTrap
{
protected:
	std::string _name;
	unsigned int _hitPoints;
	unsigned int _energyPoints;
	unsigned int _attackDamage;
};
```

Dans ce module, `protected` est utile parce que `ScavTrap`, `FragTrap` et
`DiamondTrap` doivent modifier les valeurs heritees de `ClapTrap`.

Exemple :

```cpp
ScavTrap::ScavTrap(const std::string& name)
	: ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}
```

### public

Accessible depuis l'exterieur.

```cpp
scav.attack("target");
scav.guardGate();
```

Les fonctions que le `main.cpp` doit appeler doivent etre `public`.

## 4. Heritage public

Dans ce module, on utilise :

```cpp
class ScavTrap : public ClapTrap
```

Le `public` apres les deux-points veut dire que l'interface publique de `ClapTrap`
reste publique dans `ScavTrap`.

Donc si `ClapTrap` a :

```cpp
void takeDamage(unsigned int amount);
void beRepaired(unsigned int amount);
```

Alors un `ScavTrap` peut aussi les utiliser :

```cpp
ScavTrap scav("Serena");
scav.takeDamage(10);
scav.beRepaired(5);
```

## 5. Redefinition d'une fonction

Une classe enfant peut redefinir une fonction du parent.

Dans `ClapTrap` :

```cpp
void attack(const std::string& target);
```

Dans `ScavTrap` :

```cpp
void attack(const std::string& target);
```

Les deux fonctions ont le meme nom et les memes parametres, mais elles affichent un
message different.

Exemple :

```cpp
ClapTrap clap("Basic");
ScavTrap scav("Serena");

clap.attack("target"); // appelle ClapTrap::attack
scav.attack("target"); // appelle ScavTrap::attack
```

Le sujet demande explicitement que `ScavTrap::attack()` affiche un message different.

## 6. Forme canonique orthodoxe

Depuis le Module 02, les classes doivent suivre la forme canonique orthodoxe.

Chaque classe doit avoir :

```cpp
ClassName();
ClassName(const ClassName& other);
ClassName& operator=(const ClassName& other);
~ClassName();
```

Cela correspond a :

```text
constructeur par defaut
constructeur de copie
operateur d'affectation
destructeur
```

Exemple :

```cpp
FragTrap a("Fraggy");
FragTrap b(a);    // constructeur de copie

FragTrap c;
c = a;            // operateur d'affectation
```

Dans ce module il n'y a pas de `new`, donc la copie est simple, mais il faut quand meme
respecter cette forme.

## 7. Heritage multiple

L'heritage multiple signifie qu'une classe herite de plusieurs classes.

Dans `ex03` :

```cpp
class DiamondTrap : public ScavTrap, public FragTrap
{
};
```

Donc `DiamondTrap` herite de :

```text
ScavTrap
FragTrap
```

Mais `ScavTrap` et `FragTrap` heritent eux-memes de `ClapTrap`.

Sans precaution, on obtient :

```text
DiamondTrap
  |
  +-- ScavTrap
  |     |
  |     +-- ClapTrap
  |
  +-- FragTrap
        |
        +-- ClapTrap
```

Le probleme : `DiamondTrap` aurait deux parties `ClapTrap`.

Cela peut creer des ambiguities :

```cpp
_name
_hitPoints
attack()
```

C++ ne saurait pas toujours s'il faut utiliser le `ClapTrap` venant de `ScavTrap` ou
celui venant de `FragTrap`.

Ce probleme s'appelle souvent le probleme du diamant.

## 8. Heritage virtuel

Pour eviter d'avoir deux `ClapTrap` dans `DiamondTrap`, on utilise l'heritage virtuel.

Dans `ScavTrap.hpp` :

```cpp
class ScavTrap : virtual public ClapTrap
```

Dans `FragTrap.hpp` :

```cpp
class FragTrap : virtual public ClapTrap
```

Avec ca, `DiamondTrap` partage une seule et unique partie `ClapTrap`.

Schema :

```text
      ClapTrap
      /      \
 ScavTrap  FragTrap
      \      /
    DiamondTrap
```

Le sujet dit :

```text
The ClapTrap instance of DiamondTrap will be created once, and only once.
```

Le "trick", c'est donc :

```cpp
virtual public ClapTrap
```

## 9. Constructeur avec heritage virtuel

Avec un heritage virtuel, la classe la plus derivee construit la base virtuelle.

Dans `DiamondTrap`, c'est donc `DiamondTrap` qui doit construire `ClapTrap`.

Exemple :

```cpp
DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;
}
```

Important :

```text
ClapTrap est construit une seule fois.
ScavTrap et FragTrap ne reconstruisent pas chacun leur propre ClapTrap.
```

## 10. Pourquoi DiamondTrap a deux noms

Le sujet demande que `DiamondTrap` ait son propre attribut `name`, avec le meme nom de
variable que dans `ClapTrap`.

Dans notre code, `ClapTrap` a :

```cpp
std::string _name;
```

Donc `DiamondTrap` doit aussi avoir :

```cpp
private:
	std::string _name;
```

Il y a donc deux noms differents :

```text
DiamondTrap::_name = nom du DiamondTrap
ClapTrap::_name    = nom de la partie ClapTrap
```

Exemple :

```cpp
DiamondTrap diamond("Diamond");
```

Valeurs attendues :

```text
DiamondTrap::_name = "Diamond"
ClapTrap::_name = "Diamond_clap_name"
```

Dans `whoAmI()` :

```cpp
std::cout << "DiamondTrap name: " << _name << std::endl;
std::cout << "ClapTrap name: " << ClapTrap::_name << std::endl;
```

`ClapTrap::_name` permet de dire explicitement qu'on veut le `_name` de `ClapTrap`.

## 11. Resolution d'ambiguite

Avec l'heritage multiple, plusieurs classes peuvent avoir une fonction du meme nom.

Le sujet demande que `DiamondTrap` utilise l'attaque de `ScavTrap`.

On peut donc ecrire :

```cpp
void DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}
```

`ScavTrap::attack(target)` dit explicitement :

```text
utilise la version attack de ScavTrap
```

Cela evite l'ambiguite.

## 12. Valeurs des classes

### ClapTrap

```text
Hit points    = 10
Energy points = 10
Attack damage = 0
```

Fonctions :

```text
attack()
takeDamage()
beRepaired()
```

### ScavTrap

```text
Hit points    = 100
Energy points = 50
Attack damage = 20
```

Fonction speciale :

```text
guardGate()
```

### FragTrap

```text
Hit points    = 100
Energy points = 100
Attack damage = 30
```

Fonction speciale :

```text
highFivesGuys()
```

### DiamondTrap

```text
Hit points    = FragTrap = 100
Energy points = ScavTrap = 50
Attack damage = FragTrap = 30
attack()      = ScavTrap::attack()
```

Fonction speciale :

```text
whoAmI()
```

## 13. Points importants pour l'evaluation

Verifier que :

```text
make compile avec -Wall -Wextra -Werror -std=c++98
les headers ont des include guards
les constructeurs affichent des messages
les destructeurs affichent des messages
les classes respectent la forme canonique orthodoxe
ScavTrap herite de ClapTrap
FragTrap herite de ClapTrap
DiamondTrap herite de ScavTrap et FragTrap
ScavTrap et FragTrap utilisent virtual public ClapTrap dans ex03
DiamondTrap construit ClapTrap une seule fois
whoAmI() affiche les deux noms
DiamondTrap utilise ScavTrap::attack()
```

## 14. Commandes utiles

Compiler un exercice :

```sh
cd ex00
make
```

Nettoyer :

```sh
make fclean
```

Recompiler :

```sh
make re
```

Tester :

```sh
./claptrap
./scavtrap
./fragtrap
./diamondtrap
```

