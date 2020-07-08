#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayStruct.h"
#include <math.h>

#define N_DIGITS pow(10, 12)
using namespace std;

bool debug = false;

// ========================= Global Vars =======================

// struct for the coordenates
typedef struct coords{
    double x;
    double y;
}Coord;

// nPoints : all 'n' points
Coord* nPoints;

// 
double** areaArray;

// areaArr: calculated areas
double* areaArr;
// sizeAreaArr: areaArr size
int sizeAreaArr;

// n : total number of points
int n;
// k : numb of selected points
int k;

// ========================= Aux Funcs =========================

// copies info from 'og' to 'copy'
void copyCoord(Coord* og, Coord* destiny){ destiny->x = og->x; destiny->y = og->y; }
// returns the lowest point
Coord* lowestPoint(Coord* p1, Coord* p2){ return (p1->y < p2->y)? p1:p2; }
// returns the min of x and y
int min(int x, int y){ return (x<y)? x:y; }

// ========================= Functions =========================

// gets the inputed information
// returns false in case of error
bool getInput(){

    // receives input 'n' and 'k'
    scanf("%d %d", &n, &k);

    // error control
    if( (n > 1200) || (k > n) || (n <= 0) || (k <= 0)) return false;

    // allocs the necessary memory for the arrays
    nPoints = (Coord*)calloc(n, sizeof(Coord));

    int in;
    for(in = 0; in < n; in++){

        // gets the 'x' and 'y' coord with 12 decimals precision
        scanf("%lf %lf", &nPoints[in].x, &nPoints[in].y);

        // [!!] FALTA VER SE OS PONTOS SAO VALIDOS [!!] //
         
        // turn the numb to a 12 digits double
        nPoints[in].x = floor(nPoints[in].x*N_DIGITS)/N_DIGITS;
        nPoints[in].y = floor(nPoints[in].y*N_DIGITS)/N_DIGITS;

        // error control
        if( (nPoints[in].x < 0) || (nPoints[in].y < 0) ) return false;
    }

    return true;
}

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

// calcs the common are of 'k' points
// and saves them in an array (areaArr)
void calcAllAreas(){
    // number of groups
    // exemple: n = 7, k = 4
    // total = 4 (7-4+1)
    sizeAreaArr = n - k+1;

    // allocing memory for the array
    areaArr = (double*)calloc(sizeAreaArr, sizeof(double));

    // calc and save areas
    /*  [EXPLANATION]
        . the biggest common areas are made from the closest points
        . the common area between >= 3 points is the common area of 
        the 'extreme' points
    */
    int index;
    for(index = 0; index < sizeAreaArr; index++){
        // calc area = highest.x * lowest.y
        areaArr[index] = nPoints[index+k-1].y * nPoints[index].x;
    }
}

// ========================= V2 ==============================

// subproblema P(i, j)
void calcAreaToArray(int indexUnion, int indexPoint){
    // o ponto nPoints[indexPoint] é sempre o mais alto
    // logo calcula se as areas: nPoints[i].x * (nPoints[i].y - nPoints[i-1].y)
    double bestArea = 0;
    double auxArea = 0;
    // nao e possivel fazer a uniao da area de 1 com pontos antes de 1
    if(!(indexPoint - indexUnion < 0)){
        for(int k=0; k<indexPoint; k++){
            if(debug) printf("\t\tk = %d\n", k);
            //if(!(k-indexUnion < 0)){
                auxArea = nPoints[indexPoint].x * (nPoints[indexPoint].y - nPoints[k].y);
                if(debug) printf("\t\t\tauxArea = %f\n", auxArea);
                if(areaArray[k][indexUnion-1] + auxArea > bestArea){
                    bestArea = areaArray[k][indexUnion-1] + auxArea;
                }if(debug) printf("\t\t\tBestArea = %f\n", bestArea);
            //}
        }
    }
    areaArray[indexPoint][indexUnion] = bestArea;
    if(debug) printf("\t\t\t[Done]\n");
}

// ========================= Main ==============================

/*  [OBJECTIVES]
    ✔ get the input points
    ✔ sort them from lowest to highest
    ✔ calc the area from 'k' to 'k'
    . sort the areas from lowest to highest
    . return the highest
*/

int main(){
    // get input
    if( getInput() ){ // if theres any error during the input step, shut down

        /*int i;
        for(i=0; i<n; i++){
            printf("%lf %lf\n", nPoints[i].x, nPoints[i].y);
        }*/
        
        //printf("\nPos MergeSort=====================\n\n");

        // sorts the points from lowest to highest
        mergeSort();

        /*for(int i=0; i<n; i++){
            printf("%lf %lf\n", nPoints[i].x, nPoints[i].y);
        }*/
       // printf("\nAreas=============================\n\n");

        // calc areas
        /*calcAllAreas();

        for(i=0; i<sizeAreaArr; i++){
            printf("%lf\n", areaArr[i]);
        }*/

        // inicializar o double array onde vao ficar as areas
        areaArray = (double**)calloc(n, sizeof(double*));
        for(int i=0; i<n; i++) areaArray[i] = (double*)calloc(k, sizeof(double));
        // preenche com as primeiras areas
        for(int i=0; i<n; i++) areaArray[i][0] = nPoints[i].x * nPoints[i].y;
        
        for(int i=1; i<k; i++){
            if(debug) printf("i = %d\n", i);
            for(int j=0; j<n; j++){
                if(debug) printf("\tj = %d\n", j);
                calcAreaToArray(i, j);
            }
        }

        double big = 0;
        for(int i=0; i<n; i++){
            if(debug) printf("%.12f\t", areaArray[i][k-1]);
            if(areaArray[i][k-1] > big){
                big = areaArray[i][k-1];
            }
        }

        printf("%.12f\n", big);
        // free alloced memory
        free(areaArray);
        free(nPoints);
        free(areaArr);
    }

}

