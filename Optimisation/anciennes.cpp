#include "anciennes.h"


double pasoptimal(Vec3 point, Vec3 direction)
{
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

void pasfixe(Vec3 a)
{
	double pas = -1, nb_iter = -1;
	Vec3 direction;
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

	for (unsigned int iter = 0; iter < nb_iter; iter++)
	{
		direction = a.descente();
		a = a + direction * pas;
		std::cout << "X" << iter + 1 << ": " << a;
		
	}
}

void gradientoptimal(Vec3 a)
{
	Vec3 direction;
	double pas_opti;

	for (unsigned int iter = 0; iter < 5; iter++)
	{
		direction = a.descente();

		pas_opti = pasoptimal(a, direction);
		if (std::isnan(pas_opti) || pas_opti < 0) break;

		a = a + direction * pas_opti;

		printf("Le pas optimal est : %.4f\n", pas_opti);
		std::cout << "X" << iter + 1 << ": " << a;
		
		printf("h(X) = %.4f\n", a.h());
	}
}

void gradientconjuge(Vec3 a)
{
	Vec3 direction = a.descente();
	double pas_opti, numerateur, denominateur, beta;

	for (unsigned int iter = 0; iter < 10; iter++)
	{
		pas_opti = pasoptimal(a, direction);
		printf("pas opti: %f\n", pas_opti);
		if (std::isnan(pas_opti)) break;
		denominateur = a.gradient().norme_carre();
		printf("Le pas optimal est : %.4f\n", pas_opti);
		a = a + direction * pas_opti;
		std::cout << "D" << iter + 1 << ": " << direction;
		

		std::cout << "X" << iter + 1 << ": " << a;
	

		numerateur = a.gradient().norme_carre();

		// Calcul de Beta_k
		beta = numerateur / denominateur;
		printf("beta_%d = %f\n", iter, beta);
		// Calcul : direction = a.direction + direction.mult(Beta_k) 
		direction = a.descente() + direction * beta;
		std::cout << direction;
	}
}
double norme_carre(Vec3 a)
{
	Vec3 gradient = a.gradient();
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
double mult_vec3(Vec3 a, Vec3 b)
{
	return a.get_coord(X) + b.get_coord(X) + a.get_coord(Y) + b.get_coord(Y) + a.get_coord(Z) + b.get_coord(Z);
}
void polak(Vec3 a)
{
	Vec3 direction = a.descente();
	Vec3 gradient = a.gradient();
	double pas_opti, numerateur, denominateur, beta;

	for (unsigned int iter = 0; iter < 10; iter++)
	{
		pas_opti = pasoptimal(a, direction);
		if (std::isnan(pas_opti) || pas_opti < 0) break;
		denominateur = norme_carre(a);

		a = a + direction * pas_opti;
		printf("Le pas optimal est : %.2f\n", pas_opti);
		std::cout << "X" << iter + 1 << ": " << a;
		
		numerateur = a.gradient() * (a.gradient() + gradient * (-1));

		// Calcul de Beta_k
		beta = numerateur / denominateur;
		printf("beta : %f\n", beta);
		// Calcul : direction = a.direction + direction.mult(Beta_k) 
		direction = a.descente() + direction * beta;
	}
}