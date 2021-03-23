DROP DATABASE IF EXISTS ordenacao;
CREATE DATABASE ordenacao;

USE ordenacao;

DROP TABLE IF EXISTS experimentos;

CREATE TABLE experimentos (
    id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    n INT UNSIGNED NOT NULL,
    d INT UNSIGNED NOT NULL,
    t_quicksort INT UNSIGNED NOT NULL,
    t_radixsort INT UNSIGNED NOT NULL,
    t_mergesort INT UNSIGNED NOT NULL
) engine=innodb;

CREATE OR REPLACE VIEW vw_experimentos_quicksort AS
    SELECT
        n,
        d,
        AVG(t_quicksort) as media,
        STDDEV_POP(t_quicksort) as desvio_padrao,
        COUNT(id) as qtd
    FROM
        experimentos
    GROUP BY
        n, d;

CREATE OR REPLACE VIEW vw_experimentos_radixsort AS
    SELECT
        n,
        d,
        AVG(t_radixsort) as media,
        STDDEV_POP(t_radixsort) as desvio_padrao,
        COUNT(id) as qtd
    FROM
        experimentos
    GROUP BY
        n, d;

CREATE OR REPLACE VIEW vw_experimentos_mergesort AS
    SELECT
        n,
        d,
        AVG(t_mergesort) as media,
        STDDEV_POP(t_mergesort) as desvio_padrao,
        COUNT(id) as qtd
    FROM
        experimentos
    GROUP BY
        n, d;
