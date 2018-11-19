#include <iostream>
#include "myAlgorithm.h"

using namespace std;

int main() {
    SetUpParams setup{};
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, Weierstrass};
    MyAlgorithm algo{p, setup};
    
    algo.run();
    
    cout << algo.best_solution() << endl;
    
    return 0;
}
