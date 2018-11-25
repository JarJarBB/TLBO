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
    vector<double> MeanPerColumn() const;
    double Difference_Mean(int j, const vector<double>& Means, double r) const;
    void Teaching();
    void Learning();


    const vector<Solution*>& solutions() const;
    unsigned int upper_cost() const;
    unsigned int lower_cost() const;
    Solution& solution(const unsigned int index) const;
    double fitness(const unsigned int index) const;


    double best_cost() const;
    double worst_cost() const;
    Solution& best_solution() const;
    Solution& worst_solution() const;
    
    /** il faudra peut-etre remplacer la fonction run() par cette fonction evolution() du prof... */
    void evolution(int iter); /*makes an evolution step*/

};

#endif
