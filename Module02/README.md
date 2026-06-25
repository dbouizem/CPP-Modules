# C++ Module 02

Ce module introduit les nombres a virgule fixe, la forme canonique orthodoxe,
la surcharge d'operateurs et le polymorphisme ad-hoc en C++98.

## Fiche de revision rapide

Notions principales du module :

- forme canonique orthodoxe ;
- representation d'un nombre a virgule fixe ;
- conversion `int` / `float` vers `Fixed` ;
- conversion `Fixed` vers `int` / `float` ;
- surcharge d'operateurs ;
- difference entre pre-increment et post-increment ;
- fonctions membres `static` ;
- surcharge de fonctions avec versions `const` et non-`const` ;
- classe immutable avec attributs `const` ;
- test BSP pour savoir si un point est strictement dans un triangle.

### A retenir sur `Fixed`

`Fixed` stocke une valeur dans un entier brut :

```cpp
int _fixedPointValue;
```

Avec 8 bits fractionnaires :

```cpp
static const int _fractionalBits = 8;
```

Cela veut dire :

```text
1.0 est stocke comme 256
0.5 est stocke comme 128
2.5 est stocke comme 640
```

La formule principale est :

```text
raw = value * 256
value = raw / 256
```

Dans le code :

```cpp
_fixedPointValue = value << _fractionalBits;          // int -> raw
_fixedPointValue = roundf(value * (1 << _fractionalBits)); // float -> raw
```

### A retenir sur la forme canonique

Chaque classe importante doit avoir :

```cpp
ClassName();
ClassName(const ClassName& other);
ClassName& operator=(const ClassName& other);
~ClassName();
```

Difference essentielle :

```cpp
Fixed b(a); // constructeur de copie
b = a;      // operateur d'affectation
```

### A retenir sur les operateurs

Les comparaisons retournent un `bool` :

```cpp
a < b
a >= b
a == b
```

Les operations arithmetiques retournent un nouvel objet :

```cpp
Fixed c = a + b;
Fixed d = a * b;
```

`operator<<` permet d'afficher un `Fixed` directement :

```cpp
std::cout << fixed << std::endl;
```

### A retenir sur `const`

Une fonction marquee `const` promet de ne pas modifier l'objet :

```cpp
float toFloat(void) const;
```

Une reference `const` evite une copie et interdit la modification :

```cpp
Fixed(const Fixed& other);
```

Dans `Point`, les coordonnees sont constantes :

```cpp
Fixed const _x;
Fixed const _y;
```

Donc apres construction, un `Point` ne change plus. C'est pour cela que
`operator=` ne copie rien dans `Point` : on ne peut pas reassigner des attributs
`const` apres leur initialisation.

### A retenir sur `bsp`

`bsp(a, b, c, point)` retourne :

```text
true  si point est strictement dans le triangle
false si point est dehors
false si point est sur un bord
false si point est sur un sommet
```

Le test utilise les signes d'aires. Si les signes sont tous du meme cote, le
point est dedans. Si les signes sont melanges, le point est dehors. Si un signe
vaut zero, le point est sur un bord, donc le sujet demande `false`.

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

Commandes communes :

- `make` ou `make all` : compile l'exercice ;
- `make clean` : supprime les fichiers objets ;
- `make fclean` : supprime les objets et l'executable ;
- `make re` : recompile entierement l'exercice.

## ex00 - My First Class in Orthodox Canonical Form

**Etat : termine**

Creation d'une classe `Fixed` qui represente un nombre a virgule fixe.
Dans cet exercice, la classe ne fait pas encore de calculs : elle stocke
seulement une valeur brute dans un entier.

### Classe `Fixed`

Attributs prives :

- `_fixedPointValue` : un `int` qui stocke la valeur brute du nombre ;
- `_fractionalBits` : un `static const int` qui vaut toujours `8`.

Le `_` au debut de `_fixedPointValue` n'a rien a voir avec la forme canonique
orthodoxe. C'est seulement une convention de nommage pour montrer que la
variable est un attribut prive de la classe.

Comme `_fractionalBits` est `static const`, il appartient a la classe et sa
valeur ne change pas. On ne le copie donc pas dans le constructeur de copie ou
dans l'operateur d'affectation.

### Forme canonique orthodoxe

La classe doit contenir les quatre fonctions suivantes :

```cpp
Fixed();                              // constructeur par defaut
Fixed(const Fixed& other);            // constructeur de copie
Fixed& operator=(const Fixed& other); // operateur d'affectation
~Fixed();                             // destructeur
```

La forme canonique orthodoxe veut dire qu'une classe possede les quatre
fonctions principales pour gerer la vie d'un objet :

1. creer un objet vide/default avec `Fixed()` ;
2. creer un objet a partir d'un autre avec `Fixed(const Fixed& other)` ;
3. copier dans un objet qui existe deja avec `operator=` ;
4. detruire l'objet avec `~Fixed()`.

Elle sert donc a donner a la classe une gestion complete de la creation, de la
copie, de l'affectation et de la destruction.

Difference importante :

```cpp
Fixed b(a);
```

cree un nouvel objet `b` a partir de `a`, donc cela appelle le constructeur de
copie.

```cpp
c = b;
```

copie `b` dans un objet `c` qui existe deja, donc cela appelle l'operateur
d'affectation.

### `getRawBits()` et `setRawBits()`

```cpp
int getRawBits(void) const;
void setRawBits(int const raw);
```

`getRawBits()` retourne la valeur brute stockee dans `_fixedPointValue`.

`setRawBits()` modifie la valeur brute de `_fixedPointValue`.

Exemple :

```cpp
Fixed a;

a.setRawBits(42);
std::cout << a.getRawBits() << std::endl;
```

Ce code affiche la valeur brute `42`.

### Utilisation

```bash
cd Module02/ex00
make
./fixed
```

Le programme de test cree trois objets `Fixed`, copie les valeurs entre eux,
puis affiche leurs valeurs brutes. Comme les objets sont initialises a `0`, les
trois valeurs affichees sont `0`.

Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.

## ex01 - Towards a more useful fixed-point number class

**Etat : termine**

Cet exercice reprend la classe `Fixed` de l'ex00 et la rend plus utile. Elle
peut maintenant etre construite a partir d'un `int` ou d'un `float`, puis etre
reconvertie en `int` ou en `float`.

### Comprendre le fixed-point depuis zero

#### 1. Un `int` normal

```txt
int = 4 octets = 32 bits

┌────────┬────────┬────────┬────────┐
│ octet1 │ octet2 │ octet3 │ octet4 │
└────────┴────────┴────────┴────────┘
```

Chaque octet contient 8 bits :

```txt
octet4
┌─┬─┬─┬─┬─┬─┬─┬─┐
│0│0│0│0│0│0│0│0│
└─┴─┴─┴─┴─┴─┴─┴─┘
```

#### 2. Dans fixed-point, on ne decoupe pas physiquement l'octet

On fait juste une **regle de lecture**.

On dit :

```txt
Les 8 derniers bits seront lus comme la partie apres la virgule.
```

Donc mentalement :

```txt
┌────────────────────────┬──────────────┐
│ 24 bits avant virgule  │ 8 bits apres │
└────────────────────────┴──────────────┘
```

#### 3. Pourquoi 256 ?

Parce que les 8 derniers bits peuvent contenir :

```txt
00000000 = 0
00000001 = 1
00000010 = 2
...
11111111 = 255
```

Donc ils peuvent representer **256 positions** :

```txt
0 a 255
```

#### 4. Le "metre" veut dire quoi ici ?

Quand on dit :

```txt
1 unite = 256 morceaux
```

on parle de l'espace entre :

```txt
0.0 et 1.0
```

Pas de memoire.

C'est comme une regle graduee :

```txt
0.0                                      1.0
|----------------------------------------|
0                                       256
```

Pour arriver a `1.0`, il faut 256 pas.

Donc :

```txt
1 pas = 1 / 256
```

#### 5. Exemple avec 0.5

`0.5`, c'est la moitie entre `0` et `1`.

La moitie de 256 :

```txt
256 / 2 = 128
```

Donc :

```txt
0.5 est stocke comme 128
```

```txt
0.0                  0.5                 1.0
|--------------------|--------------------|
0                   128                  256
```

#### 6. Exemple avec 2.5

```txt
2.5 = 2 + 0.5
```

En raw :

```txt
2 unites = 2 x 256 = 512
0.5 unite = 128

512 + 128 = 640
```

Donc :

```txt
2.5 est stocke comme 640
```

Et quand on relit :

```txt
640 / 256 = 2.5
```

Le plus important :

```txt
Les bits ne sont pas divises.
La memoire stocke juste un entier.
C'est nous qui decidons de lire cet entier avec /256.
```

Donc fixed-point = **un int normal**, mais avec une regle :

```txt
valeur reelle = raw / 256
raw = valeur reelle x 256
```

Pour `2.5` en fixed-point avec 8 bits fractionnaires :

```txt
2.5 x 256 = 640
```

Donc on stocke l'entier :

```txt
raw = 640
```

Et `640` en binaire :

```txt
640 = 1010000000
```

Donc :

```txt
2.5 est stocke comme :

1010000000
```

Mais comme un `int` fait 32 bits, en memoire complete ce serait :

```txt
00000000 00000000 00000010 10000000
```

On peut le lire comme ca :

```txt
00000000 00000000 00000010 10000000
│________________________│ │______│
      partie entiere       fraction
           2                128
```

Donc :

```txt
2 + 128/256
= 2 + 0.5
= 2.5
```

`1010000000` est donc correct, c'est juste la version sans les zeros devant.

### Nouveaux constructeurs

```cpp
Fixed(const int value);
Fixed(const float value);
```

Le constructeur avec un `int` convertit l'entier en valeur fixe :

```cpp
_fixedPointValue = value << _fractionalBits;
```

Comme `_fractionalBits` vaut `8`, cela revient a multiplier par `256`.

Le constructeur avec un `float` convertit le nombre decimal en valeur fixe :

```cpp
_fixedPointValue = roundf(value * (1 << _fractionalBits));
```

`roundf` sert a arrondir correctement le resultat.

### Conversions

```cpp
float toFloat(void) const;
int toInt(void) const;
```

`toFloat()` reconvertit la valeur brute en nombre decimal :

```cpp
return ((float)_fixedPointValue / (1 << _fractionalBits));
```

`toInt()` reconvertit la valeur brute en entier :

```cpp
return (_fixedPointValue >> _fractionalBits);
```

Avec 8 bits fractionnaires, on peut retenir :

```txt
<< 8  = convertir int -> fixed-point
>> 8  = convertir fixed-point -> int
```

Exemple avec `10` :

```cpp
_fixedPointValue = 10 << 8;
```

Cela fait :

```txt
10 x 256 = 2560
```

Donc on stocke `2560`.

Pour revenir a un `int` :

```cpp
return (_fixedPointValue >> 8);
```

Cela fait :

```txt
2560 / 256 = 10
```

Attention : `>> 8` donne un `int`, donc il enleve la partie apres la virgule.

Exemple avec `2.5` :

```txt
2.5 stocke = 640
640 >> 8 = 2
```

Donc :

```txt
toInt() perd le .5
toFloat() garde le .5
```

Resume :

```txt
int -> fixed-point :
value << 8

fixed-point -> int :
raw >> 8

fixed-point -> float :
raw / 256.0
```

### Operateur d'affichage

L'exercice demande aussi de surcharger l'operateur `<<` :

```cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
```

Cela permet d'ecrire :

```cpp
std::cout << fixed << std::endl;
```

Au lieu d'afficher l'objet directement, l'operateur affiche sa valeur en
`float` avec `toFloat()`.

### Utilisation

```bash
cd Module02/ex01
make
./fixed
```

Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.

resource Fixed Point Numbers[https://youtu.be/ZMsrZvBmQnU?si=_o3EQs5Ys7oXhv96]

## ex02 - Now we're talking

**Etat : termine**

Cet exercice reprend la classe `Fixed` de l'ex01 et ajoute les operateurs pour
que les objets `Fixed` puissent se comporter comme des nombres.

### Regle generale

```cpp
Fixed&   // reference vers un objet existant
Fixed    // nouvel objet ou copie
Fixed*   // pointeur, ici on ne l'utilise pas
```

### `operator=`

```cpp
Fixed& operator=(const Fixed& other);
```

Sert a faire :

```cpp
b = a;
```

- `other` est l'objet a copier ;
- `const Fixed&` evite une copie et protege `other` ;
- `Fixed&` retourne l'objet actuel avec `*this`.

Exemple :

```cpp
Fixed& Fixed::operator=(const Fixed& other)
{
	this->_fixedPointValue = other._fixedPointValue;
	return (*this);
}
```

Note importante : `return (*this);` permet de faire :

```cpp
c = b = a;
```

### Operateurs de comparaison

```cpp
bool operator>(const Fixed& other) const;
bool operator<(const Fixed& other) const;
bool operator>=(const Fixed& other) const;
bool operator<=(const Fixed& other) const;
bool operator==(const Fixed& other) const;
bool operator!=(const Fixed& other) const;
```

Ces fonctions comparent directement les valeurs brutes `_fixedPointValue`.

Exemple :

```cpp
bool Fixed::operator>(const Fixed& other) const
{
	return (this->_fixedPointValue > other._fixedPointValue);
}
```

Dans :

```cpp
a > b;
```

le resultat est :

```cpp
true  // 1
false // 0
```

Note importante :

- `const Fixed& other` protege `b` ;
- `const` a la fin protege `a`.

Dans `a > b`, `a` et `b` ne changent pas.

### Operateurs arithmetiques

```cpp
Fixed operator+(const Fixed& other) const;
Fixed operator-(const Fixed& other) const;
Fixed operator*(const Fixed& other) const;
Fixed operator/(const Fixed& other) const;
```

`+` et `-` additionnent ou soustraient les valeurs brutes.

`*` et `/` passent par `toFloat()` pour faire le calcul simplement, puis
reconstruisent un nouveau `Fixed` avec le resultat.

Note importante : ces operateurs retournent `Fixed`, pas `Fixed&`, parce que
`a + b` cree un nouvel objet resultat. Il ne modifie pas `a` et ne modifie pas
`b`.

### Increments et decrements

```cpp
Fixed& operator++();    // ++a
Fixed operator++(int);  // a++
Fixed& operator--();    // --a
Fixed operator--(int);  // a--
```

Le plus petit pas possible vaut :

```txt
1 / 256 = 0.00390625
```

Donc incrementer un `Fixed`, ce n'est pas ajouter `1.0`. C'est ajouter `1` a la
valeur brute :

```cpp
_fixedPointValue++;
```

Comme la valeur visible est :

```txt
_fixedPointValue / 256
```

ajouter `1` au raw revient a ajouter :

```txt
1 / 256 = 0.00390625
```

Exemple :

```txt
a raw = 0
a visible = 0 / 256 = 0
```

Apres :

```cpp
++a;
```

```txt
a raw = 1
a visible = 1 / 256 = 0.00390625
```

Encore apres :

```cpp
++a;
```

```txt
a raw = 2
a visible = 2 / 256 = 0.0078125
```

Donc :

```txt
++ sur Fixed = +1 raw = +1/256 visible
-- sur Fixed = -1 raw = -1/256 visible
```

C'est ce que le sujet veut dire avec "increase or decrease by the smallest
representable epsilon". Avec 8 bits fractionnaires, le plus petit pas
representable est `1 / 256`.

Pre-incrementation :

```cpp
Fixed& Fixed::operator++()
{
	this->_fixedPointValue++;
	return (*this);
}
```

`++a` modifie `a`, puis retourne `a`. On retourne `Fixed&` parce qu'on retourne
l'objet actuel, pas une copie.

Post-incrementation :

```cpp
Fixed Fixed::operator++(int)
{
	Fixed old(*this);

	this->_fixedPointValue++;
	return (old);
}
```

`a++` garde une copie de l'ancienne valeur, modifie `a`, puis retourne cette
ancienne copie. On retourne `Fixed` parce que `old` est une copie.

Le `int` dans `operator++(int)` est un parametre fictif. On ne l'utilise pas.
Il sert seulement a dire au compilateur que cette version correspond au
post-increment `a++`.

Meme logique pour la decrementation :

```cpp
Fixed& operator--();    // --a
Fixed operator--(int);  // a--
```

Ainsi, si `a` vaut `0`, alors `++a` donne :

```txt
0.00390625
```

Difference importante :

```cpp
++a
```

modifie `a`, puis retourne la nouvelle valeur.

```cpp
a++
```

garde une copie de l'ancienne valeur, modifie `a`, puis retourne l'ancienne
valeur.

Resume final :

```txt
++a  modifie puis retourne a lui-meme   -> Fixed&
a++  retourne l'ancienne copie puis modifie a -> Fixed
a+b  cree un nouveau resultat           -> Fixed
a>b  compare seulement                  -> bool
```

### `min` et `max`

```cpp
static Fixed& min(Fixed& a, Fixed& b);
static const Fixed& min(const Fixed& a, const Fixed& b);
static Fixed& max(Fixed& a, Fixed& b);
static const Fixed& max(const Fixed& a, const Fixed& b);
```

Elles servent a retourner :

```cpp
min(a, b); // le plus petit
max(a, b); // le plus grand
```

#### Pourquoi `static` ?

```cpp
static Fixed& min(Fixed& a, Fixed& b);
```

Le mot `static` veut dire que la fonction appartient a la classe `Fixed`, pas a
un objet particulier.

Donc on l'appelle ainsi :

```cpp
Fixed::min(a, b);
```

et non :

```cpp
a.min(b);
```

Difference avec une fonction normale :

```cpp
float toFloat(void) const;
```

Une fonction normale s'utilise avec un objet :

```cpp
a.toFloat();
```

Le compilateur passe automatiquement :

```txt
this = a
```

Une fonction `static` s'utilise avec la classe :

```cpp
Fixed::min(a, b);
```

Ici, `this` n'existe pas. La fonction recoit uniquement les parametres `a` et
`b`.

#### Pourquoi `min` et `max` sont static ?

Parce que `min(a, b)` compare deux objets. Elle n'a pas besoin d'un objet
principal. On veut simplement dire :

```txt
compare a et b
```

Pas :

```txt
a, compare-toi avec b
```

#### Pourquoi retourner `Fixed&` ?

```cpp
static Fixed& min(Fixed& a, Fixed& b);
```

Cette fonction retourne directement `a` ou `b`.

Exemple :

```cpp
Fixed a(5);
Fixed b(10);

Fixed& small = Fixed::min(a, b);
```

Ici, `small` est une reference vers `a`, car `5 < 10`.

Si on retournait `Fixed` :

```cpp
static Fixed min(Fixed& a, Fixed& b);
```

alors `return a;` creerait une copie. Avec `Fixed&`, on retourne directement
l'objet existant sans copie inutile.

Implementation :

```cpp
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return (a);
	return (b);
}
```

#### Pourquoi une deuxieme version `const` ?

```cpp
static const Fixed& min(const Fixed& a, const Fixed& b);
```

Elle sert pour des objets constants :

```cpp
const Fixed a(5);
const Fixed b(10);

const Fixed& r = Fixed::min(a, b);
```

Sans cette version, `Fixed::min(a, b)` ne compilerait pas, car un `const Fixed`
ne peut pas etre passe dans un `Fixed&` non-const.

`const Fixed&` veut dire :

- pas de copie ;
- impossible de modifier l'objet.

Donc :

```cpp
const Fixed& r = Fixed::min(a, b);
```

protege aussi le resultat.

#### Meme logique pour `max`

```cpp
static Fixed& max(Fixed& a, Fixed& b);
static const Fixed& max(const Fixed& a, const Fixed& b);
```

Implementation :

```cpp
Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return (a);
	return (b);
}
```

#### A retenir pour CPP02 ex02

Fonction normale :

```cpp
a.toFloat();
```

- appartient a un objet ;
- possede `this`.

Fonction `static` :

```cpp
Fixed::min(a, b);
```

- appartient a la classe ;
- ne possede pas `this`.

Retour `Fixed&` :

```cpp
return (a);
```

ou :

```cpp
return (b);
```

- pas de copie ;
- reference directe vers l'objet.

Retour `Fixed` :

```cpp
return (result);
```

- cree ou retourne un nouvel objet resultat.

Les quatre versions existent pour gerer :

- une version pour des objets modifiables ;
- une version pour des objets `const` ;
- sans faire de copies inutiles.

### Utilisation

```bash
cd Module02/ex02
make
./fixed
```

Le programme de test du sujet affiche notamment :

```txt
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```

Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`.

## ex03 - BSP

**Etat : termine**

Cet exercice utilise la classe `Fixed` pour faire de la geometrie. Le but est de
tester si un point est strictement a l'interieur d'un triangle.

Fichiers demandes :

```txt
Makefile
main.cpp
Fixed.hpp
Fixed.cpp
Point.hpp
Point.cpp
bsp.cpp
```

### Classe `Point`

La classe `Point` represente un point en 2D avec deux coordonnees constantes :

```cpp
Fixed const _x;
Fixed const _y;
```

Elle est aussi en forme canonique orthodoxe :

```cpp
Point();
Point(const float x, const float y);
Point(const Point& other);
Point& operator=(const Point& other);
~Point();
```

Exemple :

```cpp
Point p(2.5f, 3.0f);
```

veut dire :

```txt
x = 2.5
y = 3.0
```

Comme `_x` et `_y` sont `const`, ils ne peuvent plus etre modifies apres la
construction du point. Pour cette raison, l'operateur `operator=` existe pour la
forme canonique, mais il ne peut pas vraiment remplacer les coordonnees.

Les getters retournent des references constantes :

```cpp
const Fixed& getX(void) const;
const Fixed& getY(void) const;
```

Cela evite de copier les objets `Fixed` inutilement.

### Fonction `bsp`

Prototype demande :

```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```

- `a`, `b`, `c` sont les sommets du triangle ;
- `point` est le point a tester ;
- retourne `true` si `point` est strictement dans le triangle ;
- retourne `false` si `point` est dehors ;
- retourne aussi `false` si `point` est sur un bord ou sur un sommet.

`bsp` veut dire **Binary Space Partitioning**. Dans cet exercice, le nom est
utilise pour une idee simple : separer le plan en zones et verifier si le point
est du bon cote des trois cotes du triangle.

L'implementation utilise le signe d'une aire orientee, aussi appelee produit
vectoriel 2D. On regarde de quel cote de chaque cote du triangle se trouve le
point.

```cpp
static Fixed areaSign(Point const p1, Point const p2, Point const p3)
{
	return ((p1.getX() - p3.getX()) * (p2.getY() - p3.getY())
		- (p2.getX() - p3.getX()) * (p1.getY() - p3.getY()));
}
```

Cette formule donne un signe :

- positif : `p1` est d'un cote de la ligne `p2 -> p3` ;
- negatif : `p1` est de l'autre cote ;
- zero : `p1` est exactement sur la ligne.

Dans `bsp`, on calcule trois signes :

```cpp
sign1 = areaSign(point, a, b);
sign2 = areaSign(point, b, c);
sign3 = areaSign(point, c, a);
```

Chaque signe teste `point` par rapport a un cote du triangle :

```txt
             C
            / \
           /   \
          /  P  \
         /       \
        A---------B

sign1 : P par rapport au cote A -> B
sign2 : P par rapport au cote B -> C
sign3 : P par rapport au cote C -> A
```

#### Pourquoi `Fixed(0)` ?

`sign1`, `sign2` et `sign3` sont des objets de type `Fixed`.

Donc quand on ecrit :

```cpp
sign1 == Fixed(0)
```

on construit une valeur `Fixed` qui represente `0`, puis on compare deux
valeurs du meme type :

```txt
sign1     -> Fixed
Fixed(0)  -> Fixed qui contient la valeur 0
```

Cela appelle le constructeur `Fixed` avec l'entier `0`. C'est utile parce que
les operateurs de comparaison de la classe `Fixed` comparent normalement un
`Fixed` avec un autre `Fixed`.

#### Pourquoi un signe a zero retourne `false` ?

```txt
             C
            / \
           /   \
          /     \
         /       \
        A----P----B
```

Ici, `P` est sur le cote `A -> B`.

Dans ce cas :

```cpp
if (sign1 == Fixed(0) || sign2 == Fixed(0) || sign3 == Fixed(0))
	return (false);
```

Si au moins un signe vaut `0`, le point est sur un bord ou sur un sommet. Le
sujet demande un point strictement a l'interieur, donc un point sur le bord ne
compte pas comme dedans.

#### Logique de `hasNegative` et `hasPositive`

Apres avoir elimine le cas du bord, on verifie si les signes sont melanges :

```cpp
hasNegative = (sign1 < Fixed(0)) || (sign2 < Fixed(0)) || (sign3 < Fixed(0));
hasPositive = (sign1 > Fixed(0)) || (sign2 > Fixed(0)) || (sign3 > Fixed(0));
```

`||` veut dire "ou". Donc :

- `hasNegative` vaut `true` s'il y a au moins un signe negatif ;
- `hasPositive` vaut `true` s'il y a au moins un signe positif.

Le point est dans le triangle seulement si les trois signes vont dans le meme
sens.

Cas 1 : les trois signes sont positifs.

```txt
sign1 = +
sign2 = +
sign3 = +

hasNegative = false
hasPositive = true
```

```cpp
return (!(hasNegative && hasPositive));
return (!(false && true));
return (!(false));
return (true);
```

Le point est dedans.

Cas 2 : les trois signes sont negatifs.

```txt
sign1 = -
sign2 = -
sign3 = -

hasNegative = true
hasPositive = false
```

```cpp
return (!(hasNegative && hasPositive));
return (!(true && false));
return (!(false));
return (true);
```

Le point est aussi dedans. Le sens depend seulement de l'ordre des sommets du
triangle.

Cas 3 : les signes sont melanges.

```txt
             C
            / \
           /   \
          /     \
         /       \
        A---------B
             P
```

Exemple :

```txt
sign1 = -
sign2 = +
sign3 = +

hasNegative = true
hasPositive = true
```

```cpp
return (!(hasNegative && hasPositive));
return (!(true && true));
return (!(true));
return (false);
```

Le point est dehors.

#### Resume de la logique finale

```txt
tous positifs             -> dedans
tous negatifs             -> dedans
melange de + et de -      -> dehors
au moins un signe a zero  -> sur le bord, donc false
```

La ligne :

```cpp
return (!(hasNegative && hasPositive));
```

veut donc dire :

```txt
retourne true si on n'a pas a la fois du negatif et du positif
```

Autrement dit, les signes ne doivent pas etre melanges.

Avec la loi de De Morgan, cette ligne est equivalente a :

```cpp
return (!hasNegative || !hasPositive);
```

### Utilisation

```bash
cd Module02/ex03
make
./bsp
```

Le `main.cpp` teste :

- un point dedans ;
- un point dehors ;
- un point sur un bord ;
- un point sur un sommet.

Fichiers : `Makefile`, `main.cpp`, `Fixed.hpp`, `Fixed.cpp`, `Point.hpp`,
`Point.cpp`, `bsp.cpp`.
