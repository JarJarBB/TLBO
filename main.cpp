#include <iostream>
#include "myAlgorithm.h"

using namespace std;

//SetUpParams (unsigned int independent_runs = 30, unsigned int nb_evolution_steps = 2000000, unsigned int population_size = 40, unsigned int solution_size = 20);
//Rosenbrock, Rastrigin, Ackley, Schwefel, Schaffer, Weierstrass
int main() {

    SetUpParams setup{30, 1000, 40, 20};
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, Ackley};
    MyAlgorithm algo{p, setup};
    
    algo.run();
    
    cout << endl << "Fitness de la meilleure solution : " << algo.best_solution().get_fitness() << endl;
    cout << endl << "Meilleure solution : " << endl;
    cout << algo.best_solution() << endl;
    
    return 0;
}
