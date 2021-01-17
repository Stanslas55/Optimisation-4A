#ifndef ANCIENNES
#define ANCIENNES
#include "fonctions.h"
double mult_vec3(Vec3 a, Vec3 b);
double norme_carre(Vec3 a);

void pasfixe(Vec3 a);
void gradientoptimal(Vec3 a);
double pasoptimal(Vec3 point, Vec3 direction);
void gradientconjuge(Vec3 a);
void polak(Vec3 a);
#endif // !ANCIENNES