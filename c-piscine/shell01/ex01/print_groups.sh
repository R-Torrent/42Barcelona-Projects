#!/bin/bash

# Ejemplo 1:
# FT_USER=nours

# Ejemplo 2:
# FT_USER=daemon

id -Gn $FT_USER | tr ' ' ',' | tr -d '\n'
