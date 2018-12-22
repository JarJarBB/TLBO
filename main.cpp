#include <iostream>
#include <fstream>
#include <iomanip>
#include "myAlgorithm.h"
using namespace std;
//SetUpParams (independent_runs = 30, nb_evolution_steps = 50000, population_size = 40, solution_size = 20);
//Rosenbrock: -5,10 Rastrigin: -5,5 Ackley: -32,32, Schwefel(420.968746): -500, 500, Schaffer: -100,100 Weierstrass: -5,5

SetUpParams setup{30, 32, 40, 20};

void TLBO(fonction f);
void TLBOfile(ostream& outputFile);


int main()
{
    TLBO(Schaffer);

   // ofstream outputFile{"aTLBO201819.txt"}; TLBOfile(outputFile);

    return 0;
}


void TLBO(fonction f)
{
    //cout << fixed << setprecision(16);
    Viewer fenetre {};
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, f};
    MyAlgorithm algo{p, setup};
    algo.run(fenetre);
    fenetre.closeWindow();
}

void TLBO(fonction f, ostream& outputFile)
{
    //cout << fixed << setprecision(16);
    NoViewer fenetre {};
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, f};
    MyAlgorithm algo{p, setup};
    algo.run(fenetre);
    fenetre.closeWindow();

    algo.outputSummary(outputFile);
}

void TLBOfile(ostream& outputFile)
{
    outputFile << endl;
    outputFile << "TBLO 201819 - Vanulli A. - Vix P. - Freyburger H. - Chevalier P.\n" << endl;
    outputFile << setup << endl;
    TLBO(Rosenbrock, outputFile);
    outputFile << endl;
    TLBO(Rastrigin, outputFile);
    outputFile << endl;
    TLBO(Ackley, outputFile);
    outputFile << endl;
    TLBO(Schwefel, outputFile);
    outputFile << endl;
    TLBO(Schaffer, outputFile);
    outputFile << endl;
    TLBO(Weierstrass, outputFile);
    outputFile << endl;
}
