#!/bin/bash

base1="'\\\\\"?\!"
base2=mrdoc

# Ejemplo 1:
# FT_NBR1="\\'?\"\\\"'\\"
# FT_NBR2=rcrdmddd

# Ejemplo 2:
# FT_NBR1="\\\"\\\"\!\\\"\\\"\!\\\"\\\"\!\\\"\\\"\!\\\"\\\"\!\\\"\\\""
# FT_NBR2=dcrcmcmooododmrrrmorcmcrmomo

echo $FT_NBR1 + $FT_NBR2 | tr $base1 01234 | tr $base2 01234 | sed 's/^/obase=13; ibase=5;/' | bc | tr 0123456789ABC gtaio' 'luSnemf
