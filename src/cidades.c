#include <stdio.h>
#include "cidades.h"

double deg2rad(double deg){
    return (deg * M_PI / 180);
}
int distanceEarthKm(Cidade_t *cidade1,Cidade_t *cidade2){
    
    double lat1r, lat2r, lon1r, lon2r, u, v;
    lat1r = deg2rad(cidade1->lat);
    lon1r = deg2rad(cidade1->lon);
    lat2r = deg2rad(cidade2->lat);
    lon2r = deg2rad(cidade2->lon);
    u = sin((lat2r-lat1r)/2);
    v = sin((lon2r-lon1r)/2);
    return (int) 2.0 * earthRadiusKm * asin(sqrt(u*u+cos(lat1r)*cos(lat2r)*v*v));
}
void print_cidade(Cidade_t cidade){
	printf("Cidade : %d\n",cidade.id);
	printf("  Latitude :  %lf \n",cidade.lat);
	printf("  Longitude : %lf \n",cidade.lon);
}