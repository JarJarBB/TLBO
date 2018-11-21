#ifndef INC_METAHEURISTIC
#define INC_METAHEURISTIC
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "SetUpParams.h"
#include "Problem.h"
#include "Solution.h"


using namespace std;



class MyAlgorithm
{
private:
    vector<Solution*> _solutions;     // individuals in population
    const SetUpParams& _setup;
    unsigned int _upper_cost,_lower_cost; // lower and upper fitness of individuals in population

    // Cette variable a ete ajoute
    Solution* _best_solution;
    double Moyenne;

public:
    MyAlgorithm(const Problem& pbm,const SetUpParams& setup);
    ~MyAlgorithm();

    friend ostream& operator<< (ostream& os, const MyAlgorithm& myAlgo);
    friend istream& operator>> (istream& is, MyAlgorithm& myAlgo);
    MyAlgorithm& operator= (const MyAlgorithm& myAlgo);
    const SetUpParams& setup() const;
    void initialize();

    // Ces fonctions ont ete ajoute
    void run();
    void evaluateFitness();
    void determineBestSolution();
    void Calcul_Moyenne();
    double Difference_Mean(const Solution* S) const;

    // creates a array with fitness of all solutions in MyAlgorithm and its position in the MyAlgorithm
    /** Cette fonction ne sert à mon avis à rien (pour nous) puisqu'on n'a pas à utiliser la "struct fitness" :*/
    //void evaluate();

    const vector<Solution*>& solutions() const;
    unsigned int upper_cost() const;
    unsigned int lower_cost() const;
    Solution& solution(const unsigned int index) const;
  // vector<struct particle>&  fitness_values();
    double fitness(const unsigned int index) const;


    double best_cost() const;
    double worst_cost() const;
    Solution& best_solution() const;
    Solution& worst_solution() const;

    void evolution(int iter); /*makes an evolution step*/

};

#endif
