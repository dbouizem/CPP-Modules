# CPP Module 00

Ce module introduit les bases du C++98 : les flux d'entree/sortie, les classes,
les fonctions membres, les listes d'initialisation, ainsi que les membres
`static` et `const`.

## Compilation

Chaque exercice possede son propre `Makefile` :

```bash
make -C ex00
make -C ex01
make -C ex02
```

Les programmes peuvent ensuite etre executes avec :

```bash
./ex00/megaphone "hello world"
./ex01/phonebook
./ex02/account
```

Tous les exercices sont compiles avec :

```text
-Wall -Wextra -Werror -std=c++98
```

## Exercice 00 - Megaphone

### Objectif

Le programme affiche en majuscules tous les arguments recus. Sans argument, il
affiche le message demande par le sujet.

### Fonctions et constructions utilisees

| Element | Utilite |
| --- | --- |
| `main(int ac, char **av)` | Point d'entree. `ac` contient le nombre d'arguments et `av` leurs valeurs. |
| `std::cout` | Ecrit le resultat sur la sortie standard. |
| `std::toupper()` | Convertit un caractere en majuscule. |
| `static_cast<unsigned char>()` | Fournit a `toupper` une valeur de caractere valide, meme si `char` est signe. |
| `static_cast<char>()` | Reconvertit le resultat de `toupper` en caractere affichable. |
| `std::endl` | Termine la ligne et vide le tampon de sortie. |

### Deroulement

1. Le programme verifie si un argument a ete fourni.
2. Il parcourt chaque argument a partir de `av[1]`.
3. Il parcourt chaque caractere et l'affiche en majuscule.
4. Il termine l'affichage par une nouvelle ligne.

## Exercice 01 - My Awesome PhoneBook

### Objectif

Le programme gere jusqu'a huit contacts avec les commandes `ADD`, `SEARCH` et
`EXIT`. Lorsqu'un neuvieme contact est ajoute, il remplace le plus ancien.

### Fonctions de la bibliotheque standard

| Element | Utilite |
| --- | --- |
| `std::getline()` | Lit une ligne complete, espaces compris. |
| `std::cin` | Recupere les commandes, les champs et l'index saisis. |
| `std::cout` | Affiche les invites, le tableau et les informations. |
| `std::string::empty()` | Verifie qu'une saisie n'est pas vide. |
| `std::string::length()` | Obtient la longueur d'un champ. |
| `std::string::substr()` | Tronque un champ trop long a neuf caracteres avant d'ajouter `.`. |
| `std::setw(10)` | Fixe la largeur d'une colonne a dix caracteres et aligne a droite. |
| `std::istringstream` | Convertit et valide l'index saisi sous forme de texte. |
| `std::endl` | Termine une ligne et vide le tampon de sortie. |

### Fonctions creees dans le projet

| Fonction | Utilite |
| --- | --- |
| `Contact::Contact()` | Construit un contact vide. |
| `Contact::setContact()` | Copie les cinq informations dans un objet `Contact`. |
| `Contact::displayShort()` | Affiche un contact dans le tableau abrege de `SEARCH`. |
| `Contact::displayFull()` | Affiche tous les champs du contact selectionne. |
| `formatField()` | Tronque localement les champs depassant dix caracteres. |
| `PhoneBook::PhoneBook()` | Initialise le nombre de contacts et le prochain emplacement a zero. |
| `readField()` | Redemande un champ tant que la saisie est vide. |
| `PhoneBook::addContact()` | Lit les champs et enregistre le contact dans le prochain emplacement. |
| `PhoneBook::searchContact()` | Affiche la liste, valide l'index puis affiche le contact choisi. |

### Variables principales de `PhoneBook`

| Variable | Utilite |
| --- | --- |
| `contacts[8]` | Tableau fixe contenant les contacts. |
| `contactCount` | Nombre d'emplacements actuellement valides, de 0 a 8. |
| `nextIndex` | Emplacement du prochain ajout. Le modulo `% 8` le ramene a zero apres sept. |

## Exercice 02 - The Job Of Your Dreams

### Objectif

Cet exercice consiste a reconstruire l'implementation de la classe `Account` a
partir de son interface, du fichier de test et d'un journal de reference. Chaque
compte conserve son propre solde et ses compteurs, tandis que les membres
`static` conservent les totaux communs a tous les comptes.

### Fonctions de la bibliotheque standard

| Element | Utilite |
| --- | --- |
| `std::time()` | Recupere l'heure courante sous forme de timestamp. |
| `std::localtime()` | Convertit le timestamp en date et heure locales. |
| `std::strftime()` | Formate la date sous la forme `[YYYYMMDD_HHMMSS]`. |
| `std::cout` | Affiche les operations et l'etat des comptes. |
| `std::endl` | Termine une ligne et vide le tampon de sortie. |
| `std::vector` | Stocke les comptes, depots et retraits dans `tests.cpp`. |
| `std::pair` | Regroupe un iterateur de comptes et un iterateur de montants. |
| `std::for_each()` | Applique `displayStatus()` a chaque compte. |
| `std::mem_fun_ref()` | Adapte une methode membre pour son utilisation par `for_each`. |
| `begin()` / `end()` | Fournissent les iterateurs de debut et de fin des vecteurs. |
| `sizeof` | Calcule le nombre d'elements des tableaux de test. |

### Fonctions creees dans la classe `Account`

| Fonction | Utilite |
| --- | --- |
| `Account::Account(int)` | Cree un compte, initialise son solde et actualise les totaux. |
| `Account::~Account()` | Signale la fermeture du compte et retire son solde des totaux. |
| `Account::getNbAccounts()` | Retourne le nombre total de comptes ouverts. |
| `Account::getTotalAmount()` | Retourne la somme des soldes de tous les comptes. |
| `Account::getNbDeposits()` | Retourne le nombre total de depots effectues. |
| `Account::getNbWithdrawals()` | Retourne le nombre total de retraits acceptes. |
| `Account::_displayTimestamp()` | Affiche l'horodatage devant chaque message. |
| `Account::displayAccountsInfos()` | Affiche les informations globales de tous les comptes. |
| `Account::makeDeposit()` | Ajoute un montant et actualise les compteurs locaux et globaux. |
| `Account::makeWithdrawal()` | Refuse un retrait trop eleve ou soustrait le montant demande. |
| `Account::checkAmount()` | Retourne le solde du compte sans le modifier. |
| `Account::displayStatus()` | Affiche le solde et les compteurs propres a un compte. |

### Membres `static` et membres d'instance

- Les membres `static`, comme `_totalAmount`, sont partages par tous les comptes.
- Les membres d'instance, comme `_amount`, appartiennent a un compte precis.
- Une methode terminee par `const` garantit qu'elle ne modifie pas l'objet.

## Commandes des Makefiles

| Commande | Utilite |
| --- | --- |
| `make` ou `make all` | Compile l'exercice. |
| `make clean` | Supprime les fichiers objets `.o`. |
| `make fclean` | Supprime les objets et l'executable. |
| `make re` | Nettoie puis recompile entierement l'exercice. |
