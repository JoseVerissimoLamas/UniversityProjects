#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
    José Veríssimo Lamas
    2017259895
*/

#define N_DIGITS pow(10, 12)
using namespace std;

// ========================= Global Vars =======================

// struct for the coordenates
typedef struct coords{
    double x;
    double y;
}Coord;

// nPoints : os 'n' pontos
Coord* nPoints;

// n : total de pontos
int n;
// k : numero de pontos a formar a area
int k;

// areaArray : array 2d a guardar as areas aux
double** areaArray;

// ========================= Aux Funcs =========================

// copia a info do 'og' para 'copy'
void copyCoord(Coord* og, Coord* destiny){ destiny->x = og->x; destiny->y = og->y; }
// devolve o ponto com menor y
Coord* lowestPoint(Coord* p1, Coord* p2){ return (p1->y < p2->y)? p1:p2; }
// devolve o menor entre 'x' e 'y'
int min(int x, int y){ return (x<y)? x:y; }

// ========================= Functions =========================

// obtem e guarda os valores de input
void getInput(){

    // recebe o 'n' e o 'k'
    scanf("%d %d", &n, &k);

    // aloca a memoria para o array
    nPoints = (Coord*)calloc(n, sizeof(Coord));

    int in;
    for(in = 0; in < n; in++){

        // recebe o x e o y do ponto
        scanf("%lf %lf", &nPoints[in].x, &nPoints[in].y);
    }

}

// merge dos dois subarrays
// arr[left .. mid] && arr[mid+1 .. right]
void mergeArray(int left, int mid, int right){

    // tamanho dos array auxiliares
    int szLeft = mid-left+1;
    int szRight = right-mid;
    // aux arrays
    Coord* auxLeft = (Coord*)calloc(szLeft, sizeof(Coord));
    Coord* auxRight = (Coord*)calloc(szRight, sizeof(Coord));

    // copia a info para os arrays aux
    int i;
    for(i = 0; i < szLeft; i++){
        copyCoord(&nPoints[left + i], &auxLeft[i]);
    }
    int j;
    for(j = 0; j < szRight; j++){
        copyCoord(&nPoints[mid+1 + j], &auxRight[j]);
    }    

    // junta os arrays auxiliares ao original
    i = 0; j = 0; int k = left;
    while(i < szLeft && j < szRight){
        // organiza no array original
        if(auxLeft[i].y <= auxRight[j].y){
            copyCoord(&auxLeft[i], &nPoints[k]);
            i++;
        }else{
            copyCoord(&auxRight[j], &nPoints[k]);
            j++;
        }
        k++;
    }

    // copia o resto do auxLeft (se houver)
    while (i < szLeft){ 
        copyCoord(&auxLeft[i], &nPoints[k]);
        i++; 
        k++; 
    }
    // copia o resto do auxRight (se houver)
    while (j < szRight){ 
        copyCoord(&auxRight[j], &nPoints[k]);
        j++; 
        k++; 
    }
}

// ordena o array dos pontos
void mergeSort(){
    
    // subSize : tamanho do subarray [1 - n/2]
    int subSize;
    // leftIndex : index do subarray da esquerda
    int leftIndex;

    // Merge Sort usando a tecnica Bottom-Up (iterative)
    // o primeiro subarray vai ter tamanho 1
    // os proximos teram o dobro do tamanho do seu antecedente
    for(subSize = 1; subSize <= n-1; subSize *= 2){

        // index do primeiro elemento do subarray
        for(leftIndex = 0; leftIndex < n-1; leftIndex += 2*subSize){
            
            // midIndex+1 primeiro ponto do subarray da direita
            int midIndex = min(leftIndex + subSize-1, n-1);
            // index do ponto mais a direita do subarray
            int rightIndex = min(leftIndex + 2*subSize-1, n-1);

            // merge aos subarrays 
            // arr[leftindex .. midIndex] & arr[midIndex+1 .. rightIndex]
            mergeArray(leftIndex, midIndex, rightIndex);
        }
    }
}

// subproblema P(i, j)
void calcAreaToArray(int i, int j){

    // o ponto nPoints[j] é sempre o mais alto (maior y)
    // logo calcula se as areas: nPoints[j].x * (nPoints[j].y - nPoints[k].y)
    double bestArea = 0;
    double auxArea = 0;

    // nao e possivel fazer a uniao da area de 1 com pontos antes de 1 (p.ex.)
    for(int k=0; k<j; k++){
        // area extra do ponto nPoints[j]
        auxArea = nPoints[j].x * (nPoints[j].y - nPoints[k].y);
        // verificar se a uniao da area em areaArray[k][i-1] com o ponto nPoints[j]
        if(areaArray[k][i-1] + auxArea > bestArea){
            bestArea = areaArray[k][i-1] + auxArea;
        }
    }
    // registar a maior area
    areaArray[j][i] = bestArea;
}

// ========================= Main ==============================

/*  [OBJETIVOS]
    ✔ obter os inputs
    ✔ ordena-los do menor para o maior (y)
    ✔ preencher o array das areas
        ✔ array formado por 'k' linhas e 'n' colunas
        ✔ o index da linha refere-se ao numero de pontos a unir
    ✔ obter a maior area

    [ESTRATEGIA]
    . ordenar os pontos do menor para o maior (y)
    . preencher a primeira linha do array com as areas formadas
      por cada ponto individualmente
    . ir preenchendo o array da seguinte forma:
        . na posicao areaArray[j][i] vai estar a maior area formada
          pelo ponto nPoints[j] e a area pela uniao de um dos pontos
          anteriores juntamente com pontos anteriores a esse
          (area na pos areaArray[k][i-1] onde 'k' vai de 0 ate 'j'-1)
        . onde nao e possivel preencher (nos casos em que 'j'>'i'),
          o valor registado sera 0 (zero)
        . exemplo da tabela 'n'= 5 'k'= 4
          (o ultimo numero e o mais recentemente adicionado):
            | a1  | a2  | a3   | a4    | a5    |
            |  0  | a21 | a32  | a42   | a54   |
            |  0  |  0  | a213 | a324  | a425  |
            |  0  |  0  |  0   | a2134 | a3245 |
            maior area a2134 ou a3245
    . obter a maior area da ultima linha
*/

int main(){
    
    // input
    getInput();

    // organiza os pontos do MENOR para o MAIOR (y)
    mergeSort();

    // inicializar o double array onde vao ficar as areas
    areaArray = (double**)calloc(n, sizeof(double*));
    for(int i=0; i<n; i++){
        areaArray[i] = (double*)calloc(k, sizeof(double));
        // preenche com as primeiras areas
        areaArray[i][0] = nPoints[i].x * nPoints[i].y;
    } 
        
    for(int i=1; i<k; i++){
        for(int j=i; j<n; j++){
            calcAreaToArray(i, j);
        }
    }

    double maxArea = 0;
    for(int i=0; i<n; i++){
        if(areaArray[i][k-1] > maxArea){
            maxArea = areaArray[i][k-1];
        }
    }

    printf("%.12f\n", maxArea);

    // libertar memoria alocada
    free(areaArray);
    free(nPoints);
}

