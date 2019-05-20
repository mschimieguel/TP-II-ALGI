#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cidades.h"
#include "edge.h"
#include "graph.h"


int main(int argc,char *argv[]){
	srand(time(NULL));
	FILE *ARQ_cidades = fopen(argv[1],"r");
	if(!ARQ_cidades){
		printf("Arquivo de cidades Inexistente\n");
		return 0;
	}
	int n;
	fscanf(ARQ_cidades,"%d",&n);
	int m = (n*(n-1))/2;
	Cidade_t Cidades[n];
	for(int i = 0;i < n;i++){
		Cidades[i].id = i;
		fscanf(ARQ_cidades,"%lf %lf",&Cidades[i].lat,&Cidades[i].lon);
		//print_cidade(Cidades[i]);
	}
	Edge_t *Edges = Edges_K_graph(Cidades,n); //(Edge_t*)malloc(4*sizeof(Edge_t));
		
	printf("----------------------------------\n");
	GraphMatrix_t* G = create_graph(Edges,n,m);
	
	

	return 0;
}
// for(int i = 0; i < m;i++)
	// 	print_edge(Edges[i]);
	// printf("----------------------------------\n");
	// printf("median Edge :\n");
	// Edge_t e = randomized_select(Edges,0,m-1,(int)(m+1)/2);
	// print_edge(e);









// Edges[0].node1 = 0;
	// Edges[0].node2 = 1;
	// Edges[0].weight = 3;

	// Edges[1].node1 = 2;
	// Edges[1].node2 = 3;
	// Edges[1].weight = 7;

	// Edges[2].node1 = 0;
	// Edges[2].node2 = 4;
	// Edges[2].weight = 5;

	// Edges[3].node1 = 1;
	// Edges[3].node2 = 4;
	// Edges[3].weight = 9;

	//GraphMatrix_t*  teste = 

	//printf("GRAFO COMPLETO :\n");
	//print_graph(G);
	//GraphMatrix_t* A = forest_of_graph(G,0);
	//print_graph(A);
	//Edge_t *EdgesG = edges_of_graph(G,m);
	//for(int i = 0; i < m;i++)
	//	print_edge(EdgesG[i]);

	//printf("n edges == %d\n",number_of_edges(G));
	//Bfs_t *B = create_bfs(G,0);
	//Bfs_t *B1 = create_bfs(G,1);
	//GraphMatrix_t *F_Gb = create_emptygraph(n) ;//forest_of_graph(G,0);//forest_of_graph(G,0);
	//add_edges(F_Gb,B->bfs_tree);
	//add_edges(F_Gb,B1->bfs_tree);
	//print_graph(B->bfs_tree);
	//print_graph(B1->bfs_tree);
	//print_graph(F_Gb);
	


// TESTE 1 
	// Edge_t *Edges1 = (Edge_t*)malloc(2*sizeof(Edge_t));
	// Edges1[0] = Edges[0];
	// //Edges1[1] = Edges[3];
	// Edges1[1] = Edges[5];
	// for(int i = 0; i < 3;i++)
	// 	print_edge(Edges1[i]);
	// GraphMatrix_t *teste1 = create_graph(Edges1,4,2);
	// print_graph(teste1);
	// Bfs_t *bfs_teste1 = create_bfs(teste1,3);
	// GraphMatrix_t *Forest = forest_of_graph(teste1,3);
	// print_graph(bfs_teste1->bfs_tree);
	// print_graph(Forest);