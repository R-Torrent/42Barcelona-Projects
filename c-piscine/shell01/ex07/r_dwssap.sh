#!/bin/bash

# Ejemplo:
# FT_LINE1=7
# FT_LINE2=15

cat /etc/passwd | sed /^#/d | awk '!(NR%2) {print $1}' FS=: | rev | sort -r | awk -v ft1=$FT_LINE1 -v ft2=$FT_LINE2 'NR >= ft1 && NR <= ft2' ORS=', ' | sed 's/, $/./' | tr -d '\n'
