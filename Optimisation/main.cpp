#include "fonctions.h"
#include "tests.h"

int main(void) {	
	double x, y, z, choix;
	std::string entree;
	Vec3 initial;

	//test_operateurs();
	test_calculs();

	std::cout << "Bonjour M.Labourdette, dans ce programme, nous vous proposons d'observer la fonction h(x,y,z) = xy + xz + yz - x - y - z" << std::endl << "Veuillez entrer le point initial" << std::endl;

	do {
		std::cout << "Coordonnee en x : ";
		std::cin >> entree;
	} while (!entree_valide(entree, &x));

	do {
		std::cout << "Coordonnee en y : ";
		std::cin >> entree;
	} while (!entree_valide(entree, &y));

	do {
		std::cout << "Coordonnee en z : ";
		std::cin >> entree;
	} while (!entree_valide(entree, &z));
	
	initial = Vec3(x, y, z);
	//std::cout << "X = " << initial << std::endl << "h(X) = " << initial.h() << std::endl;
		
	do {
		choix = -1;
		std::cout << "\nQuelle methode voulez vous choisir ?\n1: Pas fixe\n2: Gradient optimal \n3: Gradient conjuge\n4: Polak-Ribiere\n> ";
		std::cin >> entree;
	}
	while (!entree_valide(entree, &choix) || ((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4)));	
		
	switch ((int)choix)
	{
		case(1):
			//pasfixe(initial);
			initial.pasfixe();
			break;
		case(2):
			//gradientoptimal(initial);			
			initial.gradientoptimal();
			break;
		case(3):
			//gradientconjuge(initial);			
			initial.gradientconjuge();
			break;
		case(4):
			//polak(initial);			
			initial.polak();
			break;
		default:
			break;
	}
	std::cout << "\nFait par Cisternas Nicolas, 4A" << std::endl;
	system("pause");
	return 0;
}