#include <iostream>
#include <fstream>
#include <iomanip>
#include "myAlgorithm.h"
#include "ViewerBGI.h"

using namespace std;

//SetUpParams (independent_runs = 30, nb_evolution_steps = 9000, population_size = 40, solution_size = 20);
//Rosenbrock: -5,10 Rastrigin: -5,5 Ackley: -32,32, Schwefel(420.968746): -500, 500, Schaffer: -100,100 Weierstrass: -5,5

SetUpParams setup{2, 400, 40, 20};

void TLBO(fonction f);
void TLBOtoFile(ostream& outputFile);


int main()
{
    TLBO(Schwefel);

    //ofstream outputFile{"aTLBO201819.txt"}; TLBOtoFile(cout);

    return 0;
}


void TLBO(fonction f)
{
    //cout << fixed << setprecision(16);
    ViewerBGI fenetre {};
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, f};
    MyAlgorithm algo{p, setup};
    algo.run(fenetre);
    fenetre.closeWindow();
}

void TLBO(fonction f, ostream& output)
{
    //cout << fixed << setprecision(16);
    Viewer fenetre {};
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p{taille_probleme, f};
    MyAlgorithm algo{p, setup};
    algo.run(fenetre);
    fenetre.closeWindow();

    algo.outputSummary(output);
}

void TLBOtoFile(ostream& outputFile)
{
    ostringstream ostr{};
    ostr << "\nTLBO 201819 - Vanulli A. - Vix P. - Freyburger H. - Chevalier P.\n" << endl;
    ostr << setup;
    ostr << endl;
    TLBO(Rosenbrock, ostr); ostr << endl;
    TLBO(Rastrigin, ostr); ostr << endl;
    TLBO(Ackley, ostr); ostr << endl;
    TLBO(Schwefel, ostr); ostr << endl;
    TLBO(Schaffer, ostr); ostr << endl;
    TLBO(Weierstrass, ostr);

    outputFile << ostr.str();
}
