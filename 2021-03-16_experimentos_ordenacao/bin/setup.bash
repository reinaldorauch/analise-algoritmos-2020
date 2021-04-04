#!/bin/bash

echo "Compilando o programa do experimento"
gcc -O3 -g -pthread -o build/ordenacao src/ordenacao.c
echo "Reconstruindo a base de dados pra extração das médias de execução"
mysql --defaults-file=~/.mysql_connections/root.conf < \
  ./sql/database.sql

