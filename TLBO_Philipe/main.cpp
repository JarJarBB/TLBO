#include <iostream>
#include "myAlgorithm.h"
#include <iomanip>

using namespace std;
//SetUpParams (unsigned int independent_runs = 30, unsigned int nb_evolution_steps = 2000000, unsigned int population_size = 40, unsigned int solution_size = 20);
//Rosenbrock: -5,10 Rastrigin: -5,5 Ackley -32,32, Schwefel: -500, 500, Schaffer: -100,100 Weierstrass -5,5
int main()
{
    //cout << fixed << setprecision(30);
    Viewer fenetre {800,600};
    fenetre.openWindow();

    SetUpParams setup{30, 1000, 40, 6};
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme,Schwefel};

    MyAlgorithm algo{p, setup};

    algo.run(fenetre);
    fenetre.closeWindow();

    cout << endl << endl << "Fitness de la meilleure solution : " << algo.best_solution().get_fitness() << endl;
    cout << algo.best_solution() << endl << endl;
    cout << setup << endl;
}
