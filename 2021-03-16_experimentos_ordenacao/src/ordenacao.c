#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#define LINE_SIZE 80

unsigned long long microtime() {
  struct timeval time;
  gettimeofday(&time, NULL);
  return ((unsigned long long) time.tv_sec * 1000000) + time.tv_usec;
}

/*
 * Compara o tempo de execução da ordenação de n números com m dígitos cada
 * com os algoritmos de ordençaõ digital e quicksort.
 *
 * uso: ordenacao n m s
 *
 * onde:
 *   n = tamanho do vetor a ser ordenado
 *   m = número de dígitos de cada número (max. 19)
 *   s = semente do gerador de números aleatórios (opcional)
 */

// Rearranja em ordem lexicográfica um vetor v[0..n-1]
// de strings. Cada v[i] é uma string v[i][0..W-1]
// cujos elementos pertencem ao conjunto 0..9.
// Fonte: Prof. Paulo Feofiloff
//        https://www.ime.usp.br/~pf/algoritmos/aulas/radix.html
void ordenacaoDigital (char **v, int n, int W)
{
   int *fp;
   char **aux;
   fp = malloc ((11) * sizeof (int));
   aux = malloc (n * sizeof (char *));

   for (int d = W-1; d >= 0; --d) {
      int r;

      // ordenacao por contagem pelo dígito de ordem d
      for (r = 0; r <= 10; ++r)
         fp[r] = 0;
      for (int i = 0; i < n; ++i) {
         r = v[i][d]-'0';
         fp[r+1] += 1;
      }
      for (r = 1; r <= 10; ++r)
         fp[r] += fp[r-1];
      for (int i = 0; i < n; ++i) {
         r = v[i][d]-'0';
         aux[fp[r]] = v[i];
         fp[r]++;
      }
      for (int i = 0; i < n; ++i)
         v[i] = aux[i];
   }
   free (fp);
   free (aux);
}

// imprime o vetor de strings para testes
void print_v(char *mensagem, char **v, int n)
{
  printf("%s\n", mensagem);
  for (int i = 0; i < n; ++i)
    printf("%s\n", v[i]);
  printf("\n");
}

// imprime o vetor de inteiros para testes
void print_vi(char *mensagem, long long *vi, int n)
{
  printf("%s\n", mensagem);
  for (int i = 0; i < n; ++i)
    printf("%lld\n", vi[i]);
  printf("\n");
}

// A função randomInteger devolve um inteiro
// aleatório entre low e high inclusive,
// Vamos supor que low <= high e que
// high - low <= RAND_MAX. (O código foi copiado
// da biblioteca random de Eric Roberts.)
int randomInteger (int low, int high)
{
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    int k = d * (high - low + 1);
    return low + k;
}

// Gera n strings aleatórios
void strings_aleatorias(char **v, int n, int m)
{
  int i, j;

  for (i = 0; i<n; ++i) {
    for (j = 0; j<m; j++)
      v[i][j] = randomInteger(48,57); // dígito aleatório de 0 a 9 em ASCII
    v[i][j] = '\0';
  }
}

// compara dois inteiros para o qsort()
int comparador(const void * a, const void * b)
{
  long long d =  *(long long *)a - *(long long *)b;
  if (d > 0)
    return 1;
  else if (d < 0)
    return -1;
  else return 0;
}


// ordena o vetor v com ordenacaoDital() e
// imprime o tempo de execucao
unsigned long long ordena_por_digitos(char **v, int n, int m)
{
  unsigned long long t;
  double tempo;

  t = microtime();
  ordenacaoDigital (v, n, m);
  t = microtime() - t;

  return t;
}

// ordena o vetor v com o qsort() e
// imprime o tempo de execucao
unsigned long long quicksort(long long *v, int n, int m)
{
  unsigned long long t;
  double tempo;

  t = microtime();
  qsort(v, n, sizeof(long long), comparador);
  t = microtime() - t;

  return t;
}

void insertion_sort(long long *v, int n)
{
  int i = 0, j = 0;
  long long key = 0;

  for (i = 1; i < n; i++)
  {
    key = v[i];
    j = i - 1;
    while (j >= 0 && v[j] > key)
    {
      v[j + 1] = v[j];
      j = j - 1;
    }
    v[j + 1] = key;
  }
}

unsigned long long insertion_sort_test(long long *v, int n) {
  unsigned long long t;

  t = microtime();
  insertion_sort(v, n);
  t = microtime() - t;

  return t;
}

void run_test_for_n_m(int n, int m)
{
  // aloca um vetor de n strings de tamanho m cada para a ordenação digital
  // e um vetor de n inteiros para executar o quicksort
  char **v = malloc(n * sizeof(char *));
  long long *vi = malloc(n * sizeof(long long));
  long long *vi2 = malloc(n * sizeof(long long));

  for (int i = 0; i < n; ++i)
    v[i] = malloc((m + 1) * sizeof(char));

  // gera n strings aleatórias formadas por m dígitos cada
  strings_aleatorias(v, n, m);

  // copia as strings como números para vi, usado no quicksort
  for (int i = 0; i < n; ++i)
  {
    vi2[i] = vi[i] = atoll(v[i]);
  }

  printf(
    "%d\t%d\t%llu\t%llu\t%llu\n",
    n,
    m,
    // Testa o QuickSort
    quicksort(vi, n, m),
    // print_vi("qsort", vi, n);
    // Ordenação Digital
    ordena_por_digitos(v, n, m),
    // print_v("digital", v, n);
    // print_vi("before insertion sort", vi2, n);
    insertion_sort_test(vi2, n)
    // print_vi("after insertion sort", vi2, n);
  );
  fflush(stdout);

  for(int i = 0; i < n; i++) {
    free(v[i]);
  }

  free(v);
  free(vi);
  free(vi2);
}

int main(int argc, char *argv[])
{
  int n, m, times = 1;
  unsigned int seed;

  if (argc >=4) {
    times = atoi(argv[3]);
  }

  // recebe uma semente para o gerador aleatório
  // como primeiro parâmetro opcional
  if (argc == 5) {
    seed = atoi(argv[5]);
    printf("seed = %u\n", seed);
    srand(seed);
  }

  if (argc >= 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
  } else {
    printf("uso: ord-digital n m [times] [seed]\n");
    exit(1);
  }

  printf("n\tm\tquicksort\tordenacao digital\tinsertion sort\n");
  fflush(stdout);

  for (int j = 1; j <= n; j *= 10)
    for (int k = 1; k <= m; k++)
      for (int i = 0; i < times; i++)
        run_test_for_n_m(j, k);

  return 0;
}


