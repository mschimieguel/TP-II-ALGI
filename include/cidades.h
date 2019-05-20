#include <math.h>
#ifndef CIDADES_H
#define CIDADES_H
#define earthRadiusKm 6371.0
#define M_PI 3.14159265358979323846264338327

typedef struct cidade{
	int id;
	double lat;
	double lon;
} Cidade_t;

double deg2rad(double deg);
int distanceEarthKm(Cidade_t *cidade1,Cidade_t *cidade2);
void print_cidade(Cidade_t cidade);


#endif