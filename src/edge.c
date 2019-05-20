#include "edge.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void troca(Edge_t *edge1,Edge_t *edge2){
	Edge_t aux = *edge1;
 	*edge1 = *edge2;
 	*edge2 = aux;
}
int partition(Edge_t *graph,int start,int end){
 	Edge_t x = graph[end];
 	int i = start;
 	for (int j = start;j <= end -1;j++){
 		if(graph[j].weight <= x.weight){
 			troca(&graph[i],&graph[j]);
 			i++;
 		}
 	}
 	troca(&graph[i],&graph[end]);
 	return i;
 }
 int randomized_partition(Edge_t *graph,int start,int end){
 	int n = end-start+1; 
    int pivot = rand() % n; 
    troca(&graph[start + pivot], &graph[end]); 
    return partition(graph,start,end);


 	// int i = (rand() % (end - start + 1));
 	// i = i + start;
 	// troca(&graph[end],&graph[i]);
 	// return partition(graph,start,end);
}
Edge_t randomized_select(Edge_t *graph,int start,int end,int i){
 	if(i > 0 && i <= end -start + 1){
 		int index = randomized_partition(graph,start,end);
 		if(index - start == i - 1)
 			return graph[index];
 		if(index - start >i -1)
 			return randomized_select(graph,start,index- 1,i);
 		return randomized_select(graph,index+1,end,i - index + start - 1);
 	}
 	Edge_t erro;
 	erro.node1 = -1234568;
	erro.node2 = -1234568;
 	erro.weight = -1234568;
	return erro;	
 	// if (start == end)
 	// 	return graph[start];
 	// int q = randomized_partition(graph,start,end);
 	// int k = q - start + 1;
 	// if(i == k)
 	// 	return graph[q];
 	// else if (i < k)
 	// 	return randomized_select(graph,start,q - 1,i);
 	// else
 	// 	return randomized_select(graph,q+1,end,i - k);
 }
void print_edge(Edge_t edge){
	printf("Edge : (%d,%d)\n",edge.node1,edge.node2);
	printf("   Weight : %d\n",edge.weight );
}
Edge_t* Edges_K_graph(Cidade_t* Cidades,int n){
	int m = (n*(n-1))/2;
	Edge_t *Edges = (Edge_t*)malloc(m*sizeof(Edge_t));
	int i = 0;
	for (int j = 0;j < n;j++){
		for(int k = j + 1; k  < n;k++){
			Edges[i].node1 = j;
			Edges[i].node2 = k;
			Edges[i].weight = distanceEarthKm(&Cidades[j],&Cidades[k]);
			i++;
		}
	}
	return Edges;
}