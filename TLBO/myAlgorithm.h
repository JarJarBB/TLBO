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

public:
    MyAlgorithm(const Problem& pbm, SetUpParams& setup);
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
    void learnFromTeacher(int k, const vector<double>& Means, double r);
    void Teaching(double r);
    void learnFromPeer(int P, int Q, double r);
    void Learning(double r);
    void UpdateBestSolutionOverall(Solution* &OverallBestSolution);


    const vector<Solution*>& solutions() const;
    unsigned int upper_cost() const;
    unsigned int lower_cost() const;
    Solution& solution(const unsigned int index) const;
    double fitness(const unsigned int index) const;


    double best_cost() const;
    double worst_cost() const;
    Solution& best_solution() const;
    Solution& worst_solution() const;

    void evolution(int iter); /*makes an evolution step*/

};

#endif
