#include "edge.h"
#include "lista.h"
#ifndef GRAPH_H
#define GRAPH_H
typedef struct Graph{
	int **matrix;
	int n_nodes;
} GraphMatrix_t;

typedef struct Bfs{
	GraphMatrix_t* bfs_tree;
	int *visited;
	//lista_t* current_level;
}Bfs_t;

GraphMatrix_t* create_emptygraph(int n);
GraphMatrix_t* create_graph(Edge_t *edges,int n,int m);
void print_graph(GraphMatrix_t* Graph);
Bfs_t *create_bfs(GraphMatrix_t *Graph,int node);
int node_unvisited(int *array,int n);
int unconected_node(GraphMatrix_t* Graph,int node);
GraphMatrix_t* forest_of_graph(GraphMatrix_t *Graph,int node);
void add_edges(GraphMatrix_t *to_add,GraphMatrix_t *original);
GraphMatrix_t *MBST(GraphMatrix_t*Graph);
int number_of_edges(GraphMatrix_t *Graph);
Edge_t *edges_of_graph(GraphMatrix_t* Graph,int m);


#endif