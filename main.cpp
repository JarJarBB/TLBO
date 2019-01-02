#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "myAlgorithm.h"
#include "ViewerBGI.h"

using namespace std;

/* SetUpParams (independent_runs = 30, nb_evolution_steps = 10050, population_size = 40, solution_size = 20)
 --------------- Benchmarks : ---------------
Rosenbrock(1): -5,10 Rastrigin(0): -5,5 Ackley(0): -32,32 Schwefel(420.968746): -500, 500
Schaffer(0): -100,100 Weierstrass(0): -5,5 TheSpecialFunction(0, 1, e, pi, 4, 5,..., n) -1000,1000 */

SetUpParams setup(2, 400, 40, 20);

void TLBO(fonction f);
void TLBOtoFile(ostream& outputFile);


int main()
{
    TLBO(Schwefel);

    //ofstream outputFile("aTLBO201819.txt"); TLBOtoFile(outputFile);

    return 0;
}


void TLBO(fonction f)
{
    //cout << fixed << setprecision(5);
    ViewerBGI fenetre;
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p(taille_probleme, f);
    MyAlgorithm algo(p, setup);
    algo.run(fenetre);
    fenetre.closeWindow();
}

void TLBO(fonction f, ostream& output)
{
    //cout << fixed << setprecision(5);
    Viewer fenetre;
    fenetre.openWindow();
    const int taille_probleme = setup.solution_size();
    Problem p(taille_probleme, f);
    MyAlgorithm algo(p, setup);
    algo.run(fenetre);
    fenetre.closeWindow();
    algo.outputSummary(output);
}

void TLBOtoFile(ostream& outputFile)
{
    ostringstream ostr;

    ostr << "\nTLBO 201819 - Chevalier P. - Vix P. - Freyburger H. - Vanulli A." << endl;
    ostr << "Optimisation - Sous la tutelle du Professeur Idoumghar Lhassane.\n\n" << endl;

    ostr << setup << '\n' << endl;

    TLBO(Rosenbrock, ostr); ostr << endl;
    TLBO(Rastrigin, ostr); ostr << endl;
    TLBO(Ackley, ostr); ostr << endl;
    TLBO(Schwefel, ostr); ostr << endl;
    TLBO(Schaffer, ostr); ostr << endl;
    TLBO(Weierstrass, ostr); ostr << endl;
    TLBO(TheSpecialFunction, ostr); ostr << endl;

    std::time_t t = std::time(0); // get current time and date
    std::tm* now = std::localtime(&t);
    ostr << "\n******* " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday
        << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << " *******" << endl;

    outputFile << ostr.str();
}
