#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void transposta(double** m, int linhas, int colunas) {
  
  double aux;
  for (int i = 0; i < linhas; ++i) {
    for (int j = i + 1; j < colunas; ++j) {
      aux = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = aux;
    }
  }
}

void multiplica(double** M1, double** M2, int l1, int c1, int c2) {
  double** M3 = (double*)malloc(l1 * sizeof(double));
  for (int i = 0; i < l1; i++)
    M3[i] = (double*)malloc(c2 * sizeof(double));

  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < c2; j++) {
      M3[i][j] = 0;
      for (int k = 0; k < c1; k++)
        M3[i][j] += M1[i][k] * M2[k][j];
    }
  }

  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < c2; j++)
      M1[i][j] = M3[i][j];
  }
}

void multiplicatransposta(double** M1, double** M2, int l1, int c1, int c2)
{
  double** M3 = (double*)malloc(l1 * sizeof(double));
  for (int i = 0; i < l1; i++)
    M3[i] = (double*)malloc(c2 * sizeof(double));

  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < c2; j++) {
      M3[i][j] = 0;
      for (int k = 0; k < c1; k++)
        M3[i][j] += M1[i][k] * M2[j][k];
    }
  }

  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < c2; j++)
      M1[i][j] = M3[i][j];
  }
}

int main(int argc, char *argv[ ]) 
{
  FILE *arquivo;
  clock_t inicio, fim;
  float tempo =  0.0;
  int l1, c1, l2, c2;

  l1 = atoi(argv[1]);
  c1 = atoi(argv[2]);
  l2 = atoi(argv[3]);
  c2 = atoi(argv[4]);

 // printf("L1 = %d\nC1 = %d\nL2 = %d\nC2 = %d\n", l1, c1, l2, c2);

  // aloca a primeira matriz
  double** A = (double*)malloc(l1 * sizeof(double));
  for (int i = 0; i < l1; i++)
    A[i] = (double*)malloc(c1 * sizeof(double));

  // gerando elementos aleatórios para a matriz A
  // printf("Matriz A: \n");
  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < c1; j++) {
      A[i][j] = rand() % 100;
    }
  }

  if (c1 != l2) {
    printf("Não atende aos criterios de multiplicação de matrizes");

    return 0;
  }

  double** B = (double*)malloc(l2 * sizeof(double));
  for (int i = 0; i < l2; i++)
    B[i] = (double*)malloc(c2 * sizeof(double));

 // gerando elementos aleatórios para a matriz B
 //printf("Matriz B: \n");
  for (int i = 0; i < l2; i++) {
    for (int j = 0; j < c2; j++) {
      B[i][j] = rand() % 100;
    } 
  }

  inicio = clock();
    if(!(strcmp(argv[5], "n")) || !(strcmp(argv[5], "N"))) 
  {
    //  printf("N\n");
      multiplica(A, B, l1, c1, c2);     
  }

  else if(!(strcmp(argv[5], "t")) || !(strcmp(argv[5], "T"))) 
  {
   // printf("T\n");
    transposta(B, l2, c2);
    multiplicatransposta(A, B, l1, c1, c2);
  }
  else
    printf("Invalido\n");
  fim = clock();

  tempo = (float) (((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
  arquivo = fopen("guarda.txt", "a+");
  
  if(arquivo == NULL)
  {
      printf("Erro na abertura do arquivo!");
      return 1;
  }
  fseek(arquivo, 0, SEEK_END);
  fprintf(arquivo, "%.7lf\n", tempo);
  return 0;
}
