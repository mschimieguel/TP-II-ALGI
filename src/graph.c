#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "graph.h"
#define MAX_DISTANCE 1000000
GraphMatrix_t* create_emptygraph(int n){
	GraphMatrix_t *to_return = (GraphMatrix_t *) malloc(sizeof(GraphMatrix_t));
	to_return->n_nodes = n;
	to_return->matrix = (int**)malloc(n*sizeof(int*));
	for(int i = 0;i< n;i++){
		to_return->matrix[i] =(int*)calloc(n,sizeof(int));
	}
	return to_return;
}
GraphMatrix_t* create_graph(Edge_t *edges,int n,int m){
	GraphMatrix_t *to_return = create_emptygraph(n);
	for(int i = 0;i < m;i++){
		to_return->matrix[edges[i].node1][edges[i].node2] = edges[i].weight;
		to_return->matrix[edges[i].node2][edges[i].node1] = edges[i].weight;
	}
	return to_return;
}
void print_graph(GraphMatrix_t* Graph){
	//printf("----------------------------------\n");
	//printf("n_nodes == %d\n",Graph->n_nodes);
	printf("Grafo :\n");
	for(int i = 0; i < Graph->n_nodes;i++){
		printf("   ");
		for(int j = 0;j < Graph->n_nodes;j++)
			printf ("%d ",Graph->matrix[i][j]);
		printf("\n");
	}
	printf("----------------------------------\n");
}
int Bottleneck(GraphMatrix_t* Graph){
	//int visited[Graph->n_nodes];
	
	int distances[Graph->n_nodes];
	int visited[Graph->n_nodes];
	int PosVisitedNodes[Graph->n_nodes];

	for(int i = 0; i < Graph->n_nodes;i++){
		distances[i] = MAX_DISTANCE;
		visited[i] = 0;
	}
	distances[0] = 0;
	PosVisitedNodes[0] = -1;
	for(int i = 0;i <Graph->n_nodes-1;i++){
		int min = smallestDistance(distances,visited,Graph->n_nodes);
		visited[min] = 1;
		for(int j = 0;j < Graph->n_nodes;j++)
			if(Graph->matrix[min][j] && visited[j] == 0 && Graph->matrix[min][j] < distances[j] ){
				PosVisitedNodes[j] = min;
				distances[j] = Graph->matrix[min][j];
			}
	}
	int WeightEdgesMST[Graph->n_nodes-1];
	for(int i = 1;i < Graph->n_nodes;i++){
		WeightEdgesMST[i-1] = Graph->matrix[PosVisitedNodes[i]][i];
	}
	int max = -1;
	for(int i = 0;i < Graph->n_nodes -1;i++){
		if(WeightEdgesMST[i] > max)
			max = WeightEdgesMST[i];
	}
	return max;
}

int smallestDistance(int distances[],int visited[],int n){
	int min = MAX_DISTANCE;
	int  min_pos; 
  
	for (int i = 0; i < n; i++) 
    	if (visited[i] == 0 && distances[i] < min){
			min = distances[i];
        	min_pos = i; 
    	}
  
	return min_pos; 
}


















Bfs_t *create_bfs(GraphMatrix_t *Graph,int node){
	Bfs_t *BFS = (Bfs_t*)malloc(sizeof(Bfs_t));
	BFS->bfs_tree = create_emptygraph(Graph->n_nodes);
	lista_t* current_level = createlist();
	lista_t* next_level = createlist();
	adicionar_elemento_inicio(current_level,node);
	BFS->visited = (int *)calloc(Graph->n_nodes,sizeof(int));
	BFS->visited[node] = 1;
	node_t* to_visit =  current_level->head;
	int pivo;
	int removido;
	//int existe_vizinho = 1;
	


	for(int i = 0;i < Graph->n_nodes;i++){	
		if(unconected_node(Graph,i) == 1){
			BFS->visited[i] = -1;
		}
		if (Graph->matrix[node][i] > 0 && i != node){
			adicionar_elemento_inicio(next_level,i);
			BFS->bfs_tree->matrix[node][i] = Graph->matrix[node][i];
			BFS->bfs_tree->matrix[i][node] = Graph->matrix[node][i];
			BFS->visited[i] = 1;
			printf("bfs node == %d\n",i);
		}
		//printf("BFS->visited[%d] == %d\n",i,BFS->visited[i]);
	}
	
	while(next_level->tamanho){
		//existe_vizinho = 0;
		limpar_lista(current_level);
		while (next_level->head != NULL){
	    	removido = retirar_elemento_inicio(next_level);
	        adicionar_elemento_inicio(current_level,removido);
		}
		to_visit =  current_level->head;
		while(to_visit != NULL){
			pivo = to_visit->valor;
			for(int j = 0; j < Graph->n_nodes;j++){
				if( j != pivo && BFS->visited[j] == 0 && Graph->matrix[pivo][j] > 0 ){
					//existe_vizinho = 1;
					BFS->bfs_tree->matrix[pivo][j] = Graph->matrix[pivo][j];
					BFS->bfs_tree->matrix[j][pivo] = Graph->matrix[pivo][j];
					BFS->visited[j] = 1;
					adicionar_elemento_inicio(next_level,j);
				}
			}
			to_visit = to_visit->next;
		}	
	}	
	return BFS;
}
int node_unvisited(int *array,int n){
	for (int i = 0;i < n ;i++)
		if(array[i] == 0)
			return i;
	return -1;
}
int unconected_node(GraphMatrix_t* Graph,int node){
	int unconected = 1;
	for(int i = 0;i < Graph->n_nodes;i++)
		if (Graph->matrix[node][i] > 0)
			unconected = 0;
	return unconected;
}
GraphMatrix_t* forest_of_graph(GraphMatrix_t *Graph,int node){
	GraphMatrix_t *to_return = create_emptygraph(Graph->n_nodes);
	Bfs_t *BFS = create_bfs(Graph,node);
	add_edges(to_return,BFS->bfs_tree);
	int *visited_nodes = (int *)calloc(Graph->n_nodes,sizeof(int));
	for(int i = 0 ;i < Graph->n_nodes;i++)
		visited_nodes[i] = BFS->visited[i];
	
	while (node_unvisited(visited_nodes,Graph->n_nodes) >= 0){
		//destruir BFS
		BFS = NULL;
		BFS = create_bfs(Graph,node_unvisited(visited_nodes,Graph->n_nodes));
		add_edges(to_return,BFS->bfs_tree);
		for(int i = 0 ;i < Graph->n_nodes;i++)
			if(BFS->visited[i] ==  1)
				visited_nodes[i] = 1;
	}
	return to_return;
}
void add_edges(GraphMatrix_t *to_add,GraphMatrix_t *original){
	if (to_add->n_nodes == original->n_nodes){
		for(int i = 0;i <to_add->n_nodes;i++){
			for(int j = 0;j < to_add->n_nodes;j++){
				if (i != j && original->matrix[i][j] > 0){
					to_add->matrix[i][j] = original->matrix[i][j];
				}
			}
		}
	}
}
GraphMatrix_t *MBST(GraphMatrix_t* Graph){
	int m = number_of_edges(Graph);
	printf("m == %d \n",m);
	printf("Graph MBST :\n");
	print_graph(Graph);
	Edge_t *Edges = edges_of_graph(Graph,m);
	//for(int i = 0; i < m;i++)
	//	print_edge(Edges[i]);
	if (m == 1){
		//print_edge(Edges[0]);
		return create_graph(Edges,Graph->n_nodes,m);
	}
	else {
		
		Edge_t median = randomized_select(Edges,0,m-1,(int)m/2);
		GraphMatrix_t *A = create_emptygraph(Graph->n_nodes);
		GraphMatrix_t *B = create_emptygraph(Graph->n_nodes);

		int Bi;
		for(int i = 0;i < Graph->n_nodes;i++){
			for(int j = 0;j < Graph->n_nodes;j++){
				if(Graph->matrix[i][j] > median.weight)
					A->matrix[i][j] = Graph->matrix[i][j];					
				if(Graph->matrix[i][j] <= median.weight){
					B->matrix[i][j] = Graph->matrix[i][j];
					Bi = i;
				}
				
			}	
		}
		int spanning_tree = 1;
		printf("A :\n");
		print_graph(A);
		printf("B :\n");
		print_graph(B);
		GraphMatrix_t *F = forest_of_graph(B,Bi);
		Bfs_t *F_bfs = create_bfs(B,Bi);
		printf("F_bfs :\n");
		print_graph(F_bfs->bfs_tree);

		for(int i = 0;i < Graph->n_nodes;i++)
			if(F_bfs->visited[i] != 1 )
				spanning_tree = 0;

		if (spanning_tree){
			return MBST(B);
		}
		else{
			printf("SUPER VERTICE ? \n");
			GraphMatrix_t* to_return = create_emptygraph(Graph->n_nodes);
			GraphMatrix_t* mbst_A = MBST(A);
			add_edges(to_return,mbst_A);
			add_edges(to_return,F);
			printf("to_return :\n");
			print_graph(to_return);
			return to_return;	
		}	
	}

}
int number_of_edges(GraphMatrix_t *Graph){
	int count = 0;
	for(int i = 0;i < Graph->n_nodes;i++){
		for(int j = i + 1;j < Graph->n_nodes;j++){
			if (Graph->matrix[i][j] > 0)
				count++;
		}
	}
	return count;
}
Edge_t *edges_of_graph(GraphMatrix_t* Graph,int m){
	Edge_t *Edges = (Edge_t*)malloc(m*sizeof(Edge_t));
	int k = 0;
	for(int i = 0;i < Graph->n_nodes;i++){
		for(int j = i + 1;j < Graph->n_nodes;j++){
			if (Graph->matrix[i][j] > 0){
				Edges[k].node1 = i;
				Edges[k].node2 = j;
				Edges[k].weight = Graph->matrix[i][j];
				k++;
			}			
		}
	}
	return Edges;
}