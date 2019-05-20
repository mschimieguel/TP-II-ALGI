#include<stdio.h>
#include<stdlib.h>
#include "lista.h"

lista_t *createlist(){
    lista_t *lista=(lista_t*)malloc(sizeof(lista_t));
    lista->head=NULL;
    lista->tail=NULL;
    lista->tamanho = 0;
    return lista; 
}
void adicionar_elemento_inicio(lista_t *lista,int valor){
    node_t *no_novo=(node_t*)malloc(sizeof(node_t));
    
    no_novo->valor = valor;
    no_novo->next = lista->head;
    lista->tamanho++;
    
    if (lista->head == NULL){
        lista->head=no_novo;
        lista->tail=no_novo;
    }
    else {
         no_novo -> next = lista->head;
        lista->head=no_novo;    
    }    
}
void adicionar_elemento_fim(lista_t *lista,int valor){
    
	node_t *no_novo=(node_t*)malloc(sizeof(node_t));
    node_t *tovisit = lista->head;
  
    no_novo->valor= valor;
    no_novo->next = NULL;
    lista->tamanho++;
     no_novo->repetido=0;

    if (lista->head == NULL){
        lista->head=no_novo;
        lista->tail=no_novo;
		no_novo->repetido=0;   
    }
    else {
        lista->tail->next = no_novo;
        lista->tail=no_novo;
		while(tovisit != lista->tail){
			if (valor == tovisit->valor )
				no_novo->repetido=1;
			tovisit=tovisit->next;
		}
		    
    }    
}
void adicionar_elemento(lista_t *lista,int valor,int pos){
    int i=0;
        
    if (pos>0 && pos < lista->tamanho-1){
        node_t *tovisit=lista->head;
        for (i=0;i<pos-1;i++){
            tovisit=tovisit->next;
        }
        node_t *ultrapassado = tovisit->next;
        node_t *no_novo=(node_t*)malloc(sizeof(node_t));
        tovisit->next=no_novo;
        no_novo->next=ultrapassado;
        no_novo->valor = valor;
        lista->tamanho++;
    }
    else if (pos == 0)
        adicionar_elemento_inicio(lista,valor);
    else if (pos == lista->tamanho)
        adicionar_elemento_fim(lista,valor);
    else 
        printf("posicao nao permitida\n");
     
}
int retirar_elemento_inicio(lista_t *lista){
    
    node_t *tofree = lista->head;
    int toreturn=tofree->valor;
    lista->head=lista->head->next;
    lista->tamanho--;

    free(tofree);
    return toreturn;
}
int retirar_elemento_fim(lista_t *lista){
    
    node_t *previus = lista->head;
    while(previus->next != lista->tail)
        previus = previus->next;
    
    node_t *tofree=previus->next;
    int toreturn=tofree->valor;
    
    lista->tail = previus;
    previus->next = NULL;
    free(tofree);
    lista->tamanho--;
    return toreturn;
}
int retirar_elemento(lista_t *lista,int pos){
    
    if (pos>0 && pos < lista->tamanho - 1){
        node_t *tovisit =lista->head;
        node_t *tofree = NULL;
        int i;
        for (i=0;i<pos-1;i++)
            tovisit=tovisit->next;
        tofree = tovisit->next;
        tovisit->next = tofree->next;
        lista->tamanho--;
        int toreturn = tofree->valor;
        free(tofree);
        return toreturn;
    }    
    else if (pos==0)
        return retirar_elemento_inicio(lista);
    else if (pos == lista->tamanho - 1)
        return retirar_elemento_fim(lista);
    else {
        printf ("posicao inexistente ou nao permitida\n");
        return -1;
    } 
        
}
void destruir_lista(lista_t *lista){
    while (lista->head != NULL){
         retirar_elemento_inicio(lista);
    }
    free(lista);    
}
void limpar_lista(lista_t *lista){
   while (lista->head != NULL){
         retirar_elemento_inicio(lista);
    } 
}
void imprimir_lista(lista_t *lista){
    if (lista->head != NULL){
        node_t *tovisit=lista->head;
        while (tovisit != NULL){
            printf("%d ",tovisit->valor);
            //printf("R==%d ",tovisit->repetido);
            tovisit = tovisit->next;
        }
        printf("\n");
    }
    else 
        printf("Lista Vazia\n");    
}
int busca_valor_desde(lista_t *lista, int valor){
	printf("entrou");
	int pos=0;
	node_t *atual= lista->head;
	if (lista->head==NULL){
		printf("Error, sem memoria!!");
    	exit(1);
	}
	while(atual->valor!= valor && atual->next != NULL){
		printf("ciclo\n");
		atual=atual->next;
		pos++;
	}
	if (atual->valor== valor)
		return pos;
	if (atual->next==NULL)
		return -1;
}
void remove_duplicados(lista_t *lista){
    node_t *tovisit = lista->head;
    node_t *tofree = NULL;
    
    while(tovisit != NULL){
        while(tovisit->next->repetido == 1){
            tofree = tovisit->next;
            tovisit->next =tofree->next;
            if (tovisit->next == NULL){
                lista->tail=tovisit;
                break;
            }
            free(tofree);
        }    
        tovisit=tovisit->next;
    }    
}

