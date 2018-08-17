# SpiralsTest
Dépôt du test technique C - https://docs.google.com/document/d/1IlGUcNnYzX9uyYWiXiGbGTdFMsk7FYVTBEA2Nf0BjVM/edit

## Installer les dépendances

	sudo apt-get install cmake ninja-build openssl

## Compiler le projet

	./compile.sh

Les exécutables seront générés dans le sous dossier "build" avec l'aide de CMake & Ninja. Une fois le script compile.sh exécuté une fois, vous pouvez recompiler simplement les exécutables juste avec la commande "ninja" directement dans le dossier "build". Le script va également se charger de télécharger la bibliotèque GoogleTest utilisé pour faire les tests unitaires, puis la compiler et faire ce qu'il faut pour l'installer correctement.

## Tester le projet

Pour lancer tous les tests et s'assurer que tout est correct, vous pouvez lancer la commande suivante

	ninja test

## Exécutable

### Geohash

Après avoir compilé le projet, on trouve deux exécutables dans le dossier "build".

Le premier permet de lancer les tests unitaires.

	./geohash_test

Le second permet de lancer l'algorithme geohash directement, en lui donnant soit des coordonnées pour encoder, soit un hash pour décoder. (exécutez le sans argument pour comprendre son fonctionnement :-))

	./geohash ...

### SimHash

Après compilation du projet, on trouve deux exécutables dans le dossier "build".

Le premier permet de lancer les tests unitaires.

	./simhash_test

Le second permet de tester l'algorithme simhash. (exécutez le sans argument pour comprendre également son fonctionnement)

	./simhash

## TODO

#### SimHash
- Tester SimHash plus en profondeur
- SimHash avec poids

#### Acteurs

- $TERM n'arrête pas tous les processus. Faire des tests.
- Mieux modéliser l'architecture (pipe des zactors inutilisé... problème de conception)
- Mettre au propre les variables dans chaque acteurs
