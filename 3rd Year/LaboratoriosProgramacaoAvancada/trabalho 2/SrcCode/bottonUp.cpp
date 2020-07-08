#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "arrayStruct.h"
#include <math.h>
#include <stdbool.h>

#define N_DIGITS pow(10, 12)
using namespace std;


/*input

5 3
0.376508963445 0.437693410334
0.948798695015 0.352125307881
0.176318878234 0.493630156084
0.029394902328 0.951299438575
0.235041868262 0.438197791997

output

0.381410589193
*/


// ========================= Global Vars =======================

// struct for the coordenates
typedef struct coords{
    double x;
    double y;
}Coord;

// nPoints : all 'n' points
Coord* nPoints;

// n : total number of points
int n;
// k : numb of selected points -> elementos em cada grupo
int k;

// ========================= Dados ==============================
// gets the inputed information
// returns false in case of error
bool getInput(){
    // receives input 'n' points and 'k' numbs (grupos)
    scanf("%d %d", &n, &k);

    // error control - k tem de ser <= n e ambos positivos
    if( (n > 1200) || (k > n) || (n <= 0) || (k <= 0)) return false;

    // allocs the necessary memory for the arrays
    nPoints = (Coord*)calloc(n, sizeof(Coord));

    int in;
    for(in = 0; in < n; in++){

        // gets the 'x' and 'y' coord with 12 decimals precision
        scanf("%lf %lf", &nPoints[in].x, &nPoints[in].y);

		// error control - coordenadas negativas não são válidas
        if( (nPoints[in].x < 0) || (nPoints[in].y < 0) ) return false;
		// error control - comparação de coordenadas
		/*  [EXPLANATION]
		cada ponto não terá ambas coordenadas maiores do que
		qualquer das coordenadas de todos os outros pontos 
        */
         
        // turn the numb to a 12 digits double
        nPoints[in].x = floor(nPoints[in].x*N_DIGITS)/N_DIGITS;
        nPoints[in].y = floor(nPoints[in].y*N_DIGITS)/N_DIGITS;
    }
    return true;
}

// ========================= Ordenação ==============================

// ========================= Aux
// copies info from 'og' to 'copy' - for merge
void copyCoord(Coord* og, Coord* destiny){ 
	destiny->x = og->x; 
	destiny->y = og->y;
}
// returns the lowest point - for merge
Coord* lowestPoint(Coord* p1, Coord* p2){ return (p1->y < p2->y)? p1:p2; }
// returns the min of x and y - for merge
int min(int x, int y){ return (x<y)? x:y; }

// ========================= Funções
// merges two subarrays within the array
// arr[left .. mid] && arr[mid+1 .. right]
void mergeArray(int left, int mid, int right){

    // size of aux arrays
    int szLeft = mid-left+1;
    int szRight = right-mid;
    // aux arrays
    Coord* auxLeft = (Coord*)calloc(szLeft, sizeof(Coord));
    Coord* auxRight = (Coord*)calloc(szRight, sizeof(Coord));

    // copy info to aux arrays
    int i;
    for(i = 0; i < szLeft; i++){
        copyCoord(&nPoints[left + i], &auxLeft[i]);
    }
    int j;
    for(j = 0; j < szRight; j++){
        copyCoord(&nPoints[mid+1 + j], &auxRight[j]);
    }    

    // merge aux arrays back to the original
    i = 0; j = 0; int k = left;
    while(i < szLeft && j < szRight){
        // sort in the original array
        if(auxLeft[i].y <= auxRight[j].y){
            copyCoord(&auxLeft[i], &nPoints[k]);
            i++;
        }else{
            copyCoord(&auxRight[j], &nPoints[k]);
            j++;
        }
        k++;
    }

    // copy the rest of auxLeft (if any)
    while (i < szLeft){ 
        copyCoord(&auxLeft[i], &nPoints[k]);
        i++; 
        k++; 
    }
    // copy the rest of auxRight (if any)
    while (j < szRight){ 
        copyCoord(&auxRight[j], &nPoints[k]);
        j++; 
        k++; 
    }
}
// sorts the list of points
void mergeSort(){
    
    // subSize : size of the subarray [1 - n/2]
    int subSize;
    // leftIndex : index of the left subarray
    int leftIndex;

    // Merge Sort using Bottom-Up tecnique (iterative)
    // the first subarray will have size of 1
    // after that, every subarray will double the previous's size
    for(subSize = 1; subSize <= n-1; subSize *= 2){

        // index of the subarray's first element
        for(leftIndex = 0; leftIndex < n-1; leftIndex += 2*subSize){
            
            // midIndex+1 is the starting point of the right subarray
            int midIndex = min(leftIndex + subSize-1, n-1);
            // subarray's right index
            int rightIndex = min(leftIndex + 2*subSize-1, n-1);

            // merge the subarrays 
            // arr[leftindex .. midIndex] & arr[midIndex+1 .. rightIndex]
            mergeArray(leftIndex, midIndex, rightIndex);
        }
    }
}

// ========================= Areas ==============================

// pretende-te percorrer os n pontos formando grupos de k pontos
// após cada grupo constituido, calcular a área do coberta pelos pontos do grupo
// percorre-se o indice de pontos construindo grupos recurssivamente
// bigArea é a variável que retem a maior área calculada
// iPonto é o indice do primeiro ponto de um grupo, será percorrido até n
// units é o número de pontos já no grupo, será várias vezes percorrido até k
// belogArr é o vetor boleano q marca cd ponto q pertence ao grupo em construção
double calcArea(int iPoint, int units, int* belongArr) { 
	double newArea; // resultado do cálculo da área
	double bigArea = 0; // maior área
	double areaIntersect; // auxiliar para cálculo da área de interseção
	int iPrior = 0; // indice do ponto anterior para cálculo da área de interseção
	
	// se um grupo de k elementos está completo
	if (units == k) {
		// CÁLCULO da área coberta pelos pontos do grupo
		// método - cálculo, 2 a 2, da área acumulada entre os k pontos
		bigArea = 0;
		// percorre os pontos para cálcular a área coberta pelo grupo
		//	pelos k pontos do grupo
		for (int i = 0; i < n; i++) {
			// se o ponto faz parte do grupo, calcula-se a área
			if (belongArr[i] == 1) {
				if (bigArea == 0) {
					// cálculo da área do 1º ponto do grupo
					bigArea = nPoints[i].x*nPoints[i].y;
					iPrior = i; // retem como ponto anterior
				}else{
					// cálculo da área dos restantes pontos do grupo
					// excluindo a área comum com o ponto anterior
					areaIntersect = nPoints[i].x * nPoints[iPrior].y;
					bigArea = bigArea + nPoints[i].x*nPoints[i].y - areaIntersect;
					iPrior = i; }// retem como ponto anterior
				//printf("%.12lf %.12lf %.12lf %.12lf\n", nPoints[i].x, nPoints[i].y,
				//	nPoints[i].area, bigArea); 
			}
		}
		return bigArea;	}
	
	// se os pontos terminaram a recursividade termina
	if (iPoint == n) { return bigArea; }
	
	// o indice de um ponto é escolhido para fazer parte do grupo 
	// no vetor, o indice do ponto é marcada com 1
	// adiciona-se um ao contador de elementos no grupo (units+1) e
	// passa-se ao ponto seguinte (iPoint+1)
	belongArr[iPoint] = 1;
	newArea = calcArea(iPoint + 1, units + 1, belongArr);
	// salvaguarda a maior das áreas
	if ( newArea > bigArea ) { bigArea = newArea; }
	// depois, no momento seguinte, não é escolhido e
	// passa-se ao ponto seguinte (iPoint+1)
	belongArr[iPoint] = 0;
	newArea = calcArea(iPoint + 1, units, belongArr);
	// salvaguarda a maior das áreas
	if ( newArea > bigArea ) { bigArea = newArea; }
	
	return bigArea;
}
// pretende-te percorrer os n pontos formando grupos de k pontos
// após cada grupo constituido, calcular a área do coberta pelos pontos do grupo
// percorre-se o indice de pontos construindo grupos recurssivamente
// bigArea é a variável que retem a maior área calculada
// iPoint é o indice do primeiro ponto de um grupo, será percorrido até n
// units é o número de pontos já no grupo, será várias vezes percorrido até k
// groupArr é o vetor que guarda os ponto q pertence ao grupo em construção
double calcAreaV2(int iPoint, int units, int* groupArr) { 
	double newArea; // resultado do cálculo da área
	double bigArea = 0; // maior área
	double areaIntersect; // auxiliar para cálculo da área de interseção
	int iPrior = 0; // indice do ponto anterior para cálculo da área de interseção
	
	// se um grupo de k elementos está completo
	if (units == k) {
		// CÁLCULO da área coberta pelos pontos do grupo
		// método - cálculo, 2 a 2, da área acumulada entre os k pontos
		bigArea = 0;
		// percorre os pontos para cálcular a área coberta pelo grupo
		//	pelos k pontos do grupo
		for (int i = 0; i < k; i++) {
			// se o ponto faz parte do grupo, calcula-se a área
			if (bigArea == 0) {
				// cálculo da área do 1º ponto do grupo
				bigArea = nPoints[groupArr[i]].x*nPoints[groupArr[i]].y;
				iPrior = groupArr[i]; // retem como ponto anterior
			}else{
				// cálculo da área dos restantes pontos do grupo
				// excluindo a área comum com o ponto anterior
				areaIntersect = nPoints[groupArr[i]].x * nPoints[iPrior].y;
				bigArea = bigArea + nPoints[groupArr[i]].x*nPoints[groupArr[i]].y - areaIntersect;
				iPrior = groupArr[i]; }// retem como ponto anterior
				//printf("%.12lf %.12lf %.12lf\n", 
				//nPoints[groupArr[i]].x, nPoints[groupArr[i]].y, bigArea); 
			}
		return bigArea;	}
	
	// porque o grupo não está completo continua-se a percorrer os pontos
	for (int i = iPoint; i <= (n - 1) && (n - i) >= k - units; i++){
		groupArr[units] = i;
		newArea = calcAreaV2(i+1, units+1, groupArr);
		// salvaguarda a maior das áreas
		if ( newArea > bigArea ) { bigArea = newArea; }
	}
	
	//printf("============================================ %.12lf\n", bigArea); 
	return bigArea;
}
// ========================= Main ==============================
/*	[ESTRATÉGIA] bottom-up para o cálculo das áreas
    ✔ get the input points (FALTA VALIDAR PONTOS)
    ✔ sort them from lowest to highest
		. o método (em baixo) necessita que os pontos estejam ordenados
		. ordenação merge bottom-up
	. método (cálculo das área dos grupos com uma abordagem bottom-up):	
		https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
		[obs] só funciona para pontos com esta especificidade
			(nenhum ponto existe neste conjunto com valores de 
			coordenadas maiores ou iguais que qualquer outro 
			ponto no conjunto para os eixos x e y)
		✔ se k = 1, ordena-se as áreas e apresenta-se o resultado
		✔ determina-se os pontos que formam um grupo usando botton-up (com recursividade)
			https://algorithms.tutorialhorizon.com/print-all-combinations-of-subset-of-size-k-from-given-array/
			. os grupos são as combinações posiveis de n pontos k a k
		✔ calcula-se a área de cada grupo de k pontos ponto a ponto
			✔ para o 1º ponto calcula-se apenas a sua área no quadrante
			✔ para os restantes pontos do grupo
				✔ calcula-se a área de interseção entre o ponto e o anterior
				✔ à área do ponto subtrai-se a área de interseção
				✔ soma-se o resultado à área total acumulada
		✔ determina-se a maior das áreas dos grupos
		✔ apresenta-se o resultado

	  [OBJECTIVES] - old, descontinuado
    ✔ get the input points (FALTA VALIDAR PONTOS)
    ✔ sort them from lowest to highest
    ✔ calc the area from 'k' to 'k'
    . sort the areas from lowest to highest
    . return the highest
*/
int main(){
    
	// get input
    if( getInput() ){ // on error during the input step, shut down
        // sorts the points from lowest to highest 
		/* [EXPLICAÇÃO]
		A ordenação é um requesito para o metodo de cálculo escolhido
		das áreas unidadas - cálculo de áreas de 2 em 2 pontos
		*/
        mergeSort();
		// motra todos os pontos
        //for(int i=0; i<n; i++){ printf("%.12lf %.12lf\n", nPoints[i].x, nPoints[i].y); }
		//printf("============================================\n"); 
		
		// calc areas, ver [ESTRATÉGIA]
		double bigArea;
		int i;
        if (k == 1) { 
			// determina a maior área e mostra-a
			bigArea = 0;
			for (i=1; i<n; i++) {
				if (nPoints[i].x*nPoints[i].y > bigArea) { 
					bigArea = nPoints[i].x*nPoints[i].y; }
			}
		}else{ 
			// Três parametros:
			//	1- o ponto inicial dos n pontos, 
			//	2- a quantidades de pontos já no grupo, neste caso, no primeiro grupo,
			// 	3- um vetor de controlo que marca cada indice dos pontos com V, 
			//	pertencente ao grupo em construção
			int* groupArr = (int*)calloc(n, sizeof(int));
			bigArea = calcAreaV2(0, 0, groupArr);
		}
		
		// mostra o resultado, a mario área
		bigArea = floor(bigArea*N_DIGITS)/N_DIGITS;		
		printf("%.12lf", bigArea);
					
        // free alloced memory
        free(nPoints);
    }
}

