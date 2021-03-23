#!/bin/bash

MAX_N_SIZE=1000000
MAX_D_SIZE=18
MAX_RUN_TIMES=50

# Roda o experimento e salva no arquivo data.dat
./build/ordenacao $MAX_N_SIZE $MAX_D_SIZE $MAX_RUN_TIMES | tee ./data/data.dat

# importa os dados na base de dados
mysql --defaults-file=~/.mysql_connections/root.conf \
    -e "load data infile '$PWD/data/data.dat' into table experimentos fields terminated by '\t' ignore 1 lines"

# extrai os dados para cada dataset pro gnuplot exibir
echo '"Quicksort"' > data_quicksort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    -e 'select n, m as d, media, desvio_padrao from vw_experimentos_quicksort' >> data_quicksort.dat

echo '"Radixsort"' > data_radixsort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    -e 'select n, m as d, media, desvio_padrao from vw_experimentos_radixsort' >> data_radixsort.dat

echo '"Mergesort"' > data_mergesort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    -e 'select n, m as d, media, desvio_padrao from vw_experimentos_mergesort' >> data_mergesort.dat

cat data_quicksort.dat data_radixsort.dat data_mergesort.dat | \
    gnuplot