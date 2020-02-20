#!/usr/bin/env bash

name=$(date +%m_%y)
mkdir ./data/"$name"
mv *.don ./data/"$name"/
touch base.don
touch entree.don
touch sortie.don
cat *.don > "
"