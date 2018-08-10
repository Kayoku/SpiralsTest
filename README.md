# SpiralsTest
Dépôt du test technique C - https://docs.google.com/document/d/1IlGUcNnYzX9uyYWiXiGbGTdFMsk7FYVTBEA2Nf0BjVM/edit

## Installer les dépendances

	sudo apt-get install cmake libcunit1 libcunit1-doc libcunit1-dev ninja-build

## Compiler le projet

	./compile.sh

Les exécutables seront générés dans le sous dossier "build" avec l'aide de CMake & Ninja. Une fois le script compile.sh exécuté une fois, vous pouvez recompiler simplement les exécutables juste avec la commande "ninja" directement dans le dossier "build".

## Exécutable

### Geohash

Après avoir compilé le projet, on trouve deux exécutables dans le dossier "build".

Le premier permet de lancer les tests unitaires.

	./geohash_test

Le second permet de lancer l'algorithme geohash directement, en lui donnant soit des coordonnées pour encoder, soit un hash pour décoder. (exécutez le sans argument pour comprendre son fonctionnement :-))

	./geohash ...

## TODO

- Commencer SimHash
