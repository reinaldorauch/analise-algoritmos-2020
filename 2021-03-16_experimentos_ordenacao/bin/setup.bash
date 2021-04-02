#!/bin/bash

gcc -O3 -g -pthread -o build/ordenacao src/ordenacao.c
rm data/*
mysql --defaults-file=~/.mysql_connections/root.conf < \
  ./sql/database.sql

