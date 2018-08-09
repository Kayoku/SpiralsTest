# SpiralsTest
Dépôt du test technique C - https://docs.google.com/document/d/1IlGUcNnYzX9uyYWiXiGbGTdFMsk7FYVTBEA2Nf0BjVM/edit

## Installer les dépendances

	sudo apt-get install cmake libcunit1 libcunit1-doc libcunit1-dev

## Compiler le projet

	./compile.sh

Les executables seront générés dans le sous dossier ./cmake/bin

## TODO

- Faire la fonction "decode" de geohash
- Rendre l'executable utilisable avec des arguments (getopt)
- Faire des tests basiques pour les fonctions geohash (pour être certain qu'elle fonctionne dans les cas principaux)
