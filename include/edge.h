#include "cidades.h"
#ifndef EDGE_H
#define EDGE_H

typedef struct edge{
	int node1;
	int node2;
	int weight;
} Edge_t;
Edge_t* Edges_K_graph(Cidade_t* Cidades,int n);
void troca(Edge_t *edge1,Edge_t *edge2);
int partition(Edge_t *graph,int start,int end);
int randomized_partition(Edge_t *graph,int start,int end);
void print_edge(Edge_t edge);
Edge_t randomized_select(Edge_t *graph,int start,int end,int i);


#endif