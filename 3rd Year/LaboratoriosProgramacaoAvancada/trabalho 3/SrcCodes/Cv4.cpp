#include <stdio.h>
#include <stdlib.h>
#include <climits>

// variáveis gerai (todas são globais para minimizar a passagem de argumentos)
//int adjEdge[][] adjacency matrix - usamos um vetor linear
int *adjEdge; // edges of a undirected graph: all 'n' equipments of un network
int subNet; // count de subredes
int n;    // number of vertices in the graph (number of equipments)
int i, j; // vertices in the graph (network equipments)
int e;    // edge value in the graph (cable length)
// variáeis para encontrar os articulation points (servers)
int *low, *dfs, *visited, *parent, *server, t;
int s;    // number of articulation points (servers)
int sTotal;    // number TOTAL of articulation points (servers)
// variáeis determinar o cabo total usando Dijkstra's algorithm
// (distâncias 2 a 2 entre todos os servidores)
// visited e servers tb é usado aqui
int *length; // distâncias
int minPairs;  // acumulador de distâncias entre pares de servers
int minPairsTotal;  // acumulador TOTAL de distâncias entre pares de servers
int minTreeTotal;
// variáeis determinar a topologia em árvore usando Kruskal's algorithm
// - minimum spanning tree [MST] (minimo caminho entre servidores)
// parent tb é usado aqui
int vStart, vFinal;

// =========================================================== DFS
void DFS(int v){
	visited[v] = 1; // 1 is true
	for ( int jj = 0; jj < n; jj++) {
		if (adjEdge[v * n + jj] > 0 && visited[jj] != 1) DFS(jj);
	}
}

// =========================================================== DFS
int isConnected(int v){
	DFS(v);
	for ( int ii = v; ii < n; ii++) {
		if (visited[ii] != 1) return ii; // not connected
	}
	return n; // is connected
}
 
// =========================================================== find servers
/* A recursive function that find servers (articulation points) using DFS traversal 
v --> the vertex to be visited next 
dfs[] --> stores discovery times of visited vertices 
parent[] --> stores parent vertices in DFS tree 
server[] --> store server (articulation points)
*/
void findServer(int v)
{
    // Initialize discovery time and low value 
	dfs[v] = low[v] = ++t;
	for (int w = vStart; w < vFinal; w++){
		if (adjEdge[v*n+w] > 0) { // there is a edge between vertixs
			// If w is not visited yet, then make it a child of v 
			// in DFS tree and recur for it 
			if (dfs[w] == 0) { // has no value
				//children++;
				parent[w] = v; 
				findServer(w);
				// Check if the subtree rooted with w has a
				// connection to one of the ancestors of v 				
				low[v] = (low[v] < low[w]) ? low[v] : low[w];
				// v is an articulation point in following cases:	  
				// (1) v is root of DFS tree and has two or more chilren 
				if (dfs[v] == 1 && dfs[w] != 2 ) server[v] = 2; // 2 is true 
				// (2) if v is not root and low value of one of its
				// child is more than discovery value of v 
				if (dfs[v] != 1 && low[w] >= dfs[v]) server[v] = 1; // 1 is true
			}  
			// update low value of v for parent function calls. 
			else if (w != parent[v] && low[v] >= dfs[w]) low[v] = dfs[w];	
		}
	}
}


// =========================================================== Dijkstra
/*  Function to implement Dijkstra
*   src: source vertex to start traversing graph with
*   n: number of vertices
*/

// determina a distância minima entre vertices
int minLength()
{
	// initialize min value
	int min = INT_MAX, minIndex = 0;
	for ( int v = vStart; v < vFinal; v++) {
		if (visited[v] == 0 && length[v] <= min) {
			min = length[v]; minIndex = v; 
		}
	}
	return minIndex;
}

// acumula as distâncias entre o vertice v e os restantes
void findLenth(int v)
{
	// allocs the necessary memory for the array of distances
	length = (int*)calloc(n, sizeof(int));	
	free(visited);
	visited = (int*)calloc(n, sizeof(int));
	
    // initialize all distances as INFINITE and stpSet[] as false
	for (int ii = vStart; ii < vFinal; ii++) {
		length[ii] = INT_MAX;
		visited[ii] = 0; // 0 is false
	}
  
	// distance of source vertex from itself is always 0
	length[v] = 0; // no distance
	
	for (int count = vStart; count < vFinal - 1; count++) {
		int w = minLength(); // w is the closest vertex to i
		visited[w] = 1; // 1 is true

		for (int jj = vStart; jj < vFinal; jj++) {
			if (visited[jj] == 0 && adjEdge[w * n + jj] != 0
				&& length[w] != INT_MAX 
				&& length[w] + adjEdge[w * n + jj]  < length[jj]) {
				length[jj] = length[w] + adjEdge[w * n + jj];
//        printf("\nno %d dist %d\n", jj+1, length[jj]);
			}
		}
	}
	
	for (int jj = v +1; jj < vFinal; jj++) { // compute total length
 //       printf("%d \t\t %d\n", jj+1, length[jj]);
		if (length[jj] < INT_MAX && server[jj] != 0) {
			// acumula o total de cabo
			minPairs += length[jj];
			// acumula para este server só para controlo
//			length[v] += length[jj]; 
			// constroi a matrix de servidores
			adjEdge[v * n + jj] = length[jj];
			adjEdge[jj * n + v] = length[jj]; // simetrico
		}
	}
  
//    printf("\nCabo para ligar o server %d: %d\n", v +1, length[v]);
	
}


// =========================================================== tree topology
/* utils used on Kruskal's algorithm
*/
// find set of vertex v 
int find(int v) { 
	while (parent[v] != v) v = parent[v]; 
	return v; 
} 
// does union of v and w - it returns false if v and w are already in same set
void join(int v, int w) { 
	int a = find(v); 
	int b = find(w); 
	parent[a] = b; 
}

// =========================================================== main
int main()
{
// ================================== INPUT NETWORK DATA

	// receives input 'n' network equipments
	while (scanf("%d", &n) >= 0) {
		
		// allocs the necessary memory for the array of edges
		adjEdge = (int*)calloc(n*n, sizeof(int));
		
		// receives each edge (length of a cable between 2 equipments)
		scanf("%d", &i);
		while (i > 0) { 
			scanf("%d %d", &j, &e);
// printf("\n%d %d %d index %d %d", i, j, e, (i-1) * n + (j-1), (j-1) * n + (i-1));
			adjEdge[--i * n + --j] = e;
			adjEdge[j * n + i] = e; // add simetric vertex for dfs tree
			scanf("%d", &i);
		}
/*
		// print just for check
		printf("\n============ rede com %d equipamentos", n);
		// print liner array just for check
		printf("\n");
		for ( i = 0; i < n * n; i++) { 
			j = i % n ; if ( j == 0 ) printf(" |");
			printf("%3d", adjEdge[i]); }
		printf("\n");
*/		
		// subdivisão de subredes
		vStart = 0, vFinal = 0;
		minTreeTotal = sTotal = minPairsTotal = 0; 
		visited = (int*)calloc(n, sizeof(int));
		do { 
			vFinal = isConnected(vStart);

printf("Start %d Final %d \n",vStart +1 , vFinal +1);
			
			
			


// ================================== FIND SERVERS

		// allocs the necessary memory for each network
		low = (int*)calloc(n, sizeof(int));
		dfs = (int*)calloc(n, sizeof(int));
		parent = (int*)calloc(n, sizeof(int));
		server = (int*)calloc(n, sizeof(int));
		t = 0; // initialize time or hops between edges
		
		// call the recursive function to find servers 
		// (articulation points) in DFS tree rooted with vertex i 
		for (int i = vStart; i < vFinal; i++) { 
//			printf("\nINICIO rede com %d equipamentos",n);
			if (dfs[i] == 0) { findServer(i); }
		}
		// count servers
		int s = 0;
		for (int i = vStart; i < vFinal; i++) if (server[i] != 0) s++;
/*
		// print results 
		printf("\n\n Servidores: ");
		int s = 0;
		for (int i = 0; i < n; i++) {
			if (server[i] != 0) { printf ("%d ", i + 1);}	
			if (server[i] == 2) { printf ("(root) "); } }
		printf("(total %d)", s); 
		printf("\n dfs: ");
		for (int i = 0; i < n; i++) { printf ("%d ", dfs[i]); }
		printf("\n low: ");
		for (int i = 0; i < n; i++) { printf ("%d ", low[i]); }
		printf("\n");
*/
// ================================== CONNECT ALL SERVERS
/*
		// print just for check
		printf("\n============ rede com %d equipamentos", n);
		// print liner array just for check
		printf("\n");
		for (int i = 0; i < n * n; i++) { 
			j = i % n ; if ( j == 0 ) { printf(" |"); }
			printf("%3d", adjEdge[i]); }
		printf("\n");
*/
		minPairs = 0; // iniciar acumulador e contador
		// percorre os servidores para calcular as distâncias
		for (int i = vStart; i < vFinal -1; i++) if (server[i] != 0) findLenth(i);
			
//printf("\n Cabo total para ligar os srvidores: %d \n", minPairs); 
/*
		// print just for check
		printf("\n============ rede com %d servidores", s);
		// print liner array just for check
		printf("\n");
		for (int i = 0; i < n * n; i++) { 
			j = i % n ; if ( j == 0 ) { printf(" |"); }
			printf("%3d", adjEdge[i]); }
		printf("\n");
*/		
// ================================== TREE TOPOLOGY
		
		// simple implementation of Kruskal's algorithm 
		// finds minimum spanning tree [MST] 
		int minTree = 0; // cost of min MST
		// initialize sets of disjoint sets 
		free(parent);
		parent = (int*)calloc(n, sizeof(int));
		for ( i = vStart; i < vFinal; i++) parent[i] = i; 
		// include minimum weight edges one by one 
		int serverCount = 0; 
		while (serverCount < s - 1) { // termina depois de passar por todos os servers
			int min = INT_MAX, a = -1, b = -1; 
			
			for ( i = vStart; i < vFinal; i++) { 
				if (server[i] != 0){
					for ( j = vStart; j < vFinal; j++) { 
						if (adjEdge[i*n+j] == 0) adjEdge[i*n+j] = INT_MAX;
	//printf(" (%d, %d) value:%d \n", i+1, j+1, adjEdge[i*n+j]);
						if (find(i) != find(j) && adjEdge[i*n+j] < min
							 && server[j] != 0) { // se são servers
							min = adjEdge[i*n+j]; 
							a = i; b = j; 
						} 
					} 
				}
			}
			join(a, b); serverCount++;
//printf("edge %d: (%d, %d) length: %d \n",serverCount++ +1, a+1, b+1, min); 
			minTree += min; 
		} 

		sTotal += s;
		minPairsTotal += minPairs;
		minTreeTotal += minTree;
		
		
		
		
		
		
		
		vStart = vFinal;
		}
		while (vStart < n);
//		printf(" Cabo para a topologia em árvore: %d \n", minTree); 

//		printf("\n====================================================\n");
		if ( sTotal == 0) { printf ("no server\n"); }
		else { printf("%d %d %d\n",sTotal ,minPairsTotal ,minTreeTotal); }
//		printf("\n====================================================\n");
		// free memory for each graph (network)
		free(adjEdge);
	}
}