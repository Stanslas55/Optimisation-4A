#ifndef FONCTIONS
#define FONCTIONS
#pragma once
#include <iostream>
#include <string>
#include <math.h>


#define X 0
#define Y 1
#define Z 2

class Vec3
{
public:
	Vec3();
	~Vec3();
	Vec3(double p_x, double p_y, double p_z);

	void print(std::ostream& flux) const;
	Vec3 gradient(); /*	Renvoie un vecteur de coordonnées (y + z - 1, x + z - 1, x + y - 1) */
	Vec3 addition(Vec3 a);
	Vec3 mult(double a);
	double mult_vec3(Vec3 b); // Eventuelement surcharger l'opérateur '*' entre les Vec3
	Vec3 descente();

	double get_coord(int composant);
	double h(); // J'ai choisi la fonction h(x,y,z) = xy + xz + yz - x - y - z
	double norme_carre();
	bool valeur();

	void pasfixe();
	void gradientoptimal();
	double pasoptimal(Vec3 direction);
	void gradientconjuge();
	void polak();

private:
	double x;
	double y;
	double z;
};

Vec3 operator+(Vec3 a, Vec3 b);
double operator*(Vec3 a, Vec3 b);
Vec3 operator*(Vec3 a, double b);
std::ostream& operator<<(std::ostream& flux, Vec3 const& a);

bool check_number(std::string str);
int entree_valide(std::string entree, double* choix);


#endif // !FONCTIONS





