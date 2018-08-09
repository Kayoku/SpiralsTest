# SpiralsTest
Dépôt du test technique C - https://docs.google.com/document/d/1IlGUcNnYzX9uyYWiXiGbGTdFMsk7FYVTBEA2Nf0BjVM/edit

## Installer les dépendances

	sudo apt-get install cmake libcunit1 libcunit1-doc libcunit1-dev

## Compiler le projet

	./compile.sh

Les exécutables seront générés dans le sous dossier ./cmake/bin

## Exécutable

### Geohash

Après avoir compiler le projet, on trouve deux exécutables dans le dossier ./cmake/bin.

Le premier permet de lancer les tests unitaires.

	./geohash_test

Le second permet de lancer l'algorithme geohash directement, en lui donnant soit des coordonnées pour encoder, soit un hash pour décoder. (exécutez le sans argument pour comprendre son fonctionnement :-))

	./geohash ...

## TODO

- Rendre l'executable utilisable avec des arguments (getopt)
- Commencer SimHash

## Doc

https://fr.slideshare.net/seb478/ecam-os2015c-unitslides (test)
