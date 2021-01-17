#pragma once
#include "fonctions.h"

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::~Vec3()
{
}

Vec3::Vec3(double p_x, double p_y, double p_z) {

	x = p_x;
	y = p_y;
	z = p_z;
}

void Vec3::print(std::ostream& flux) const
{
	flux << "(" << x << " " << y << " " << z << ")";
}

Vec3 Vec3::gradient() {
	return Vec3(y + z - 1, x + z - 1, x + y - 1);
}

Vec3 Vec3::addition(Vec3 a) {

	Vec3 resultat;
	resultat.x = this->x + a.x;
	resultat.y = this->y + a.y;
	resultat.z = this->z + a.z;

	return resultat;
}

Vec3 Vec3::mult(double a) {

	Vec3 resultat;
	resultat.x = this->x * a;
	resultat.y = this->y * a;
	resultat.z = this->z * a;

	return resultat;
}

double Vec3::mult_vec3(Vec3 b)
{
	return this->get_coord(X) * b.get_coord(X) + this->get_coord(Y) * b.get_coord(Y) + this->get_coord(Z) * b.get_coord(Z);
}

Vec3 Vec3::descente()
{	
	return (this->gradient() * (-1));
}

double Vec3::get_coord(int composant)
{
	switch (composant)
	{
	case X:
		return this->x;
	case Y:
		return this->y;
	case Z:
		return this->z;
	default:
		std::cout << "Bad usage get_coord()" << std::endl;
		break;
	}
	return -1000;
}

double Vec3::h()
{
	return (x * y) + (x * z) + (y * z) - x - y - z;
}

double Vec3::norme_carre()
{
	Vec3 gradient = *this;
	double composantes[3];
	double calcul;

	composantes[X] = gradient.get_coord(X);
	composantes[Y] = gradient.get_coord(Y);
	composantes[Z] = gradient.get_coord(Z);
	// Calcul de la norme de X_k.
	calcul = composantes[X] * composantes[X] + composantes[Y] * composantes[Y] + composantes[Z] * composantes[Z];

	//calcul = sqrt(calcul);
	// On l'éleve au carré pour correspondre au dénominateur.
	//calcul = calcul * calcul;
	return calcul;
}

bool Vec3::valeur()
{
	double composantes[3];
	composantes[X] = get_coord(X);
	composantes[Y] = get_coord(Y);
	composantes[Z] = get_coord(Z);
	if (abs(composantes[X]) < 0.001 && abs(composantes[Y]) < 0.001 && abs(composantes[Z]) < 0.001)
		return false;
	return true;
}

void Vec3::pasfixe()
{
	Vec3 direction;
	double pas = -1, nb_iter = -1;
	
	std::string entree = "";
	do {
		std::cout << "Entrez le pas: " << std::endl;
		std::cin >> entree;
	} while (pas <= 0 && !entree_valide(entree, &pas));
	std::cout << "Votre pas: " << pas << std::endl;

	do {
		std::cout << "Combien d'iterations ?: " << std::endl;
		std::cin >> entree;
	} while (nb_iter <= 0 && !entree_valide(entree, &nb_iter));
	std::cout << "Nb: " << nb_iter << std::endl;

	for (unsigned int iter = 0; iter <= nb_iter; iter++)		
	{
		std::cout << "X" << iter << ": " << *this << std::endl;
		direction = this->descente();
		(*this) = (*this) + direction * pas;
		
	}
}

void Vec3::gradientoptimal()
{	
	Vec3 direction;
	double pas_opti;

	for (unsigned int iter = 0; iter < 100; iter++)
	{		
		direction = this->descente();
		
		std::cout << "X" << iter << ": " << *this << std::endl;
		pas_opti = pasoptimal(direction);
		if (std::isnan(pas_opti) || abs(pas_opti) < 0.001 || direction.valeur() == false) break;
		//std::cout << "pas opti: " << pas_opti << std::endl;
		(*this) = (*this) + direction * pas_opti;
		
		//std::cout << "X" << iter + 1 << ": " << *this << std::endl;	
		//std::cout << "h" << *this << " = " << this->h() << std::endl;
	}
}

double Vec3::pasoptimal(Vec3 direction)
{
	Vec3 point = *this;	
	
	double c_point[3], c_direction[3];

	c_point[X] = point.get_coord(X);
	c_point[Y] = point.get_coord(Y);
	c_point[Z] = point.get_coord(Z);

	c_direction[X] = direction.get_coord(X);
	c_direction[Y] = direction.get_coord(Y);
	c_direction[Z] = direction.get_coord(Z);

	double numerateur = -(c_direction[X] * (c_point[Y] + c_point[Z] - 1) + c_direction[Y] * (c_point[X] + c_point[Z] - 1) + c_direction[Z] * (c_point[X] + c_point[Y] - 1));
	double denominateur = 2 * ((c_direction[X] * c_direction[Y]) + (c_direction[X] * c_direction[Z]) + (c_direction[Y] * c_direction[Z]));

	return numerateur / denominateur;
}

void Vec3::gradientconjuge()
{
	Vec3 direction = this->descente();
	Vec3 direction_save = direction;
	//std::cout << "direction de descente ? " << ((this->gradient() * direction < 0) ? "oui" : "non") << std::endl;
	double pas_opti, numerateur, denominateur, beta = 1;

	for (unsigned int iter = 0; iter < 100; iter++)
	{		
		std::cout << "X" << iter << ": " << *this << std::endl;
		//std::cout << "D" << direction << std::endl;
		pas_opti = pasoptimal(direction);		
		if (std::isnan(pas_opti) || abs(pas_opti) < 0.001 || direction.valeur() == false) break;
		//std::cout << "pas opti: " << pas_opti << std::endl;
		
		denominateur = this->gradient().norme_carre();

		(*this) = (*this) + direction * pas_opti;

		//std::cout << "phi'() = " << this->gradient() * direction << std::endl;
 		numerateur = this->gradient().norme_carre();
		beta = numerateur / denominateur; // Calcul de Beta_k
		//std::cout << "beta " << beta << std::endl;
		direction = this->descente() + direction * beta;	
		//std::cout << "d_k+1 * d_k = " << direction * direction_save << std::endl;
		direction_save = direction;
	}
}

void Vec3::polak()
{
	Vec3 direction = this->descente();
	Vec3 gradient;
	double pas_opti, numerateur, denominateur, beta = 1;

	for (unsigned int iter = 0; iter < 100; iter++)
	{	
		gradient = this->gradient();
		std::cout << "X" << iter << ": " << *this << std::endl;
		pas_opti = pasoptimal(direction);
		if (std::isnan(pas_opti) || abs(pas_opti) < 0.001 || direction.valeur() == false) break;
		
		//std::cout << "pas opti: " << pas_opti << std::endl;

		denominateur = this->norme_carre();

		(*this) = (*this) + direction * pas_opti;		

		numerateur = this->gradient() * (this->gradient() + gradient * (-1));
		beta = numerateur / denominateur; // Calcul de Beta_k
	
		//std::cout << "X" << iter + 1 << ": " << *this << std::endl << "h(X" << iter + 1 << ") = " << this->h() << std::endl;						
		//std::cout << numerateur << " / " << denominateur << " = " << "beta_" << iter << " = " << beta << std::endl;
		
		direction = this->descente() + direction * beta; // Calcul : direction = a.direction + direction.mult(Beta_k) 
	}
}
// TODO : Arrêter si H(X+1) > H(X)
// TODO : Trouver l'erreur dans polak 

Vec3 operator+(Vec3 a, Vec3 b) {
	return a.addition(b);
}

double operator*(Vec3 a, Vec3 b)
{
	return a.mult_vec3(b);
}

Vec3 operator*(Vec3 a, double b)
{
	return a.mult(b);
}

std::ostream& operator<<(std::ostream& flux, Vec3 const& a)
{
	a.print(flux);
	return flux;
}

bool check_number(std::string str) {
	for (unsigned int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false && str[i] != '.')
			return false;	
	return true;
}

int entree_valide(std::string entree, double* choix)
{
	if (check_number(entree)) {
		*choix = std::stof(entree);
		return 1;
	}
	else {
		std::cout << "Vous avez entre une lettre !! L'entree n'est pas enregistree..." << std::endl;
		return 0;
	}
}