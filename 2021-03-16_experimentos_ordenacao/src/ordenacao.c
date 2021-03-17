#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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

// função para testar os algoritmos de ordenação
void teste()
{
  char *v1[10] = { "3847121", "9585345", "0498413", "1134995", "2222222",
		   "2222432", "3244232", "1123231", "6233213", "1923342"};
  int v2[10];

  print_v("Não Ordenado:", v1, 10);
  ordenacaoDigital (v1, 10, 7);
  print_v("Ordenado por ordenacaoDigital():", v1, 10);

  for(int i=0; i<10; ++i)
    v2[i] = atoi(v1[i]);

  qsort(v2, 10, sizeof(int), comparador);
  printf("Ordenado pelo qsort():\n");
  for (int i=0; i<10; ++i)
    printf("%d\n", v2[i]);
}

// ordena o vetor v com ordenacaoDital() e
// imprime o tempo de execucao
void ordena_por_digitos(char **v, int n, int m)
{
  clock_t t;
  double tempo;

  t = clock();
  ordenacaoDigital (v, n, m);
  t = clock() - t;

  tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Tempo da ordenacaoDigital(): %f seg.\n", tempo);
}

// ordena o vetor v com o qsort() e
// imprime o tempo de execucao
void quicksort(long long *v, int n, int m)
{
  clock_t t;
  double tempo;

  t = clock();
  qsort(v, n, sizeof(long long), comparador);
  t = clock() - t;

  tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Tempo do qsort():            %f seg.\n", tempo);
}

void insertion_sort(long long *v, int n) {

}

void insertion_sort_test(long long *v, int n) {
  clock_t t;
  double tempo;

  t = clock();
  insertion_sort(v, n);
  t = clock() - t;

  tempo = ((double)t) / CLOCKS_PER_SEC; // in seconds
  printf("Tempo do qsort():            %f seg.\n", tempo);
}

int main(int argc, char *argv[])
{
  int n, m;
  // recebe uma semente para o gerador aleatório
  // como primeiro parâmetro opcional
  if (argc == 4) {
    printf("seed = %u\n", atoi(argv[3]));
    srand((unsigned) atoi(argv[3]));
  }

  if (argc >= 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
  } else {
    printf("uso: ord-digital n m [seed]\n");
    exit(1);
  }

  // aloca um vetor de n strings de tamanho m cada para a ordenação digital
  // e um vetor de n inteiros para executar o quicksort
  char **v = malloc (n * sizeof (char *));
  long long *vi = malloc(n * sizeof(long long));
  long long *vi2 = malloc(n * sizeof(long long));

  for (int i=0; i<n; ++i)
    v[i] = malloc( (m+1)*sizeof(char) );

  // gera n strings aleatórias formadas por m dígitos cada
  strings_aleatorias(v, n, m);

  // copia as strings como números para vi, usado no quicksort
  for (int i=0; i<n; ++i) {
    vi2[i] = vi[i] = atoll(v[i]);
  }

  // Testa o QuickSort
  quicksort(vi, n, m);
  // print_vi("qsort", vi, n);

  // Ordenação Digital
  ordena_por_digitos(v, n, m);
  // print_v("digital", v, n);

  insertion_sort_test(vi2, n);

  return 0;
}


