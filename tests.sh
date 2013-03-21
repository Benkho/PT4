#!/bin/bash

##########################################
## Fichier de tests de la commande taar ##
##########################################

clear
echo "--------------------------------------"
echo "----- Tests sur la commande taar -----"
echo "--------------------------------------"

echo ""
echo "À chaque étape, lorsque le curseur clignote, appuyez sur Entrée pour continuer."

echo ""
echo "Pour réaliser les tests, nous nous servirons d'une archive TAR contenant quelques fichiers."
echo "\"test.tar\" contenant deux images, deux documents PDF et un executable."

echo ""
echo "--- Compilation : ---"
cd src
make

read -p ""

echo ""
echo "--- Affichage de l'aide ---------"
echo "--- Option -h -------------------"
echo "--- Commande : ./taar -h --------"
./taar -h

read -p ""

echo ""
echo "--- Listage des fichier de l'archive -----"
echo "--- Option -t ----------------------------"
echo "--- Commande : ./taar -t test.tar --------"
./taar -t ../test.tar

read -p ""

echo ""
echo "--- Extraction des fichier de l'archive ----------"
echo "--- Option -x ------------------------------------"
echo "--- Commande : ./taar -x test.tar sortie/ --------"
mkdir -p ../sortie
rm -f ../sortie/*
./taar -x ../test.tar ../sortie/

echo ""
echo "--- Vérification ---------------------------------"
echo "--- Commande : ls -Fl sortie/ --------------------"
ls -Fl ../sortie

read -p ""

echo ""
echo "--- Compression de l'archive -------------"
echo "--- Option -z ----------------------------"
echo "--- Commande : ./taar -z test.tar --------"
cp ../test.tar ../test_tmp.tar
rm -f ../test.tar.gz
./taar -z ../test.tar
mv ../test_tmp.tar ../test.tar

echo ""
echo "--- Vérification -------------------------"
echo "--- Commande : ls -Fl --------------------"
ls -Fl ../test.tar.gz

echo ""
echo "--------------------------------------"
echo "----- Fin du script de tests ! -------"
echo "--------------------------------------"
echo ""