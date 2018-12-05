#include <iostream>
#include "myAlgorithm.h"
#include <iomanip>
#include "Viewer.h"

using namespace std;
//SetUpParams (unsigned int independent_runs = 30, unsigned int nb_evolution_steps = 2000000, unsigned int population_size = 40, unsigned int solution_size = 20);
//Rosenbrock, Rastrigin, Ackley, Schwefel, Schaffer, Weierstrass

int main()
{
    Viewer fenetre {800,600};
    fenetre.openWindow();

    //cout << fixed << setprecision(30);
    SetUpParams setup{30, 1000, 40, 6};
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, Rastrigin};

    MyAlgorithm algo{p, setup};

    algo.run(fenetre);
    fenetre.closeWindow();

    cout << endl << setup << endl;
    cout << "Fitness de la meilleure solution : " << algo.best_solution().get_fitness() << endl;
    cout << algo.best_solution() << endl << endl;
}
