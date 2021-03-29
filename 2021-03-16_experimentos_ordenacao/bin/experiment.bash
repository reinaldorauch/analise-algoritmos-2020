#!/bin/bash

MAX_N_SIZE=1000000
MAX_D_SIZE=18
MAX_RUN_TIMES=100

echo "Executando o experimento com os argumentos N=$MAX_N_SIZE D=$MAX_D_SIZE repetições=$MAX_RUN_TIMES";
# Roda o experimento e salva no arquivo data.dat
./build/ordenacao $MAX_N_SIZE $MAX_D_SIZE $MAX_RUN_TIMES > ./data/data.dat

echo "Importando os resultados no banco de dados";
# importa os dados na base de dados
mysql --defaults-file=~/.mysql_connections/root.conf \
    ordenacao \
    -e "load data infile '$PWD/data/data.dat' into table experimentos fields terminated by '\t' ignore 1 lines (n, d, t_quicksort, t_radixsort, t_mergesort)"

echo "Extraindo as médias para o quicksort";
# extrai os dados para cada dataset pro gnuplot exibir
# echo '"Quicksort"' > data_quicksort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    ordenacao \
    --skip-column-names \
    -e 'select n, media, desvio_padrao from vw_experimentos_quicksort where d = 18' > data_quicksort.dat

echo "Extraindo as médias para o radixsort";
# echo '"Radixsort"' > data_radixsort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    ordenacao \
    --skip-column-names \
    -e 'select n, media, desvio_padrao from vw_experimentos_radixsort where d = 18' > data_radixsort.dat

echo "Extraindo as médias para o mergesort";
# echo '"Mergesort"' > data_mergesort.dat
mysql --defaults-file=~/.mysql_connections/root.conf \
    ordenacao \
    --skip-column-names \
    -e 'select n, media, desvio_padrao from vw_experimentos_mergesort where d = 18' > data_mergesort.dat

echo "Plotanto os gráficos";
gnuplot -c bin/plot-script.gplot -p
