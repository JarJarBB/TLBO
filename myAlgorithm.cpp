#include "myAlgorithm.h"
#include <random>
#include <ctime>

int tabRand[] = {1, 1, 2};

MyAlgorithm::MyAlgorithm(const Problem& pbm,const SetUpParams& setup) : _setup{setup}, _solutions(setup.population_size()), _best_solution{nullptr}, Moyenne{0.0}
{
    for (auto& i : _solutions)
        i = new Solution{pbm};
}

MyAlgorithm::~MyAlgorithm()
{
    for (auto i : _solutions)
        delete i;
}

void MyAlgorithm::initialize()
{
    for (auto i : _solutions)
        i->initialize();
}

vector<double> MyAlgorithm::MeanPerColumn() const
{
    vector<double> Means(_setup.solution_size(), 0.0);
    
    for (auto k : _solutions)
    {
        vector<double>& S = k->solution();
        for (int i = 0; i < S.size(); ++i)
            Means[i] += S[i];
    }
    
    for (auto& i : Means)
        i /= _setup.population_size();
    
    return Means;
}

double MyAlgorithm::Difference_Mean(int j, const vector<double>& Means, double r) const
{
    double Xbest = _best_solution->solution()[j];
    double Tf = tabRand[rand() % 3]; //'One' is twice as likely to be chosen as '2'
    double M = Means[j];
    
    return r * (Xbest - Tf * M);
}

const vector<Solution*>& MyAlgorithm::solutions() const
{
    return _solutions;
}

void MyAlgorithm::evaluateFitness()
{
    for(auto i : _solutions)
        i->fitness();
}

void MyAlgorithm::determineBestSolution()
{
    if (_solutions.size())
    {
        double min = _solutions[0]->get_fitness();
        _best_solution = _solutions[0];

        for (auto i : _solutions)
        {
            if (i->get_fitness() < min)
            {
                min = i->get_fitness();
                _best_solution = i;
            }
        }
    }
}

Solution& MyAlgorithm::best_solution() const
{
    return *_best_solution;
}

void MyAlgorithm::Teaching()
{
    vector<double> Means = MeanPerColumn();
    determineBestSolution();
    double r = rand() * 1.0 / RAND_MAX;
    for (int k = 0; k < _setup.population_size(); ++k)
    {
        if (_solutions[k] != _best_solution)
        {
            Solution* newSolution = new Solution{*_solutions[k]};
            vector<double>& tabNewSolution{ newSolution->solution() };
            
            for (int j = 0; j < _setup.solution_size(); ++j)
                tabNewSolution[j] += Difference_Mean(j, Means, r);
            
            newSolution->fitness();
            
            if (abs(newSolution->get_fitness()) < abs(_solutions[k]->get_fitness()))
            {
                delete _solutions[k];
                _solutions[k] = newSolution;
            }
            else delete newSolution;
        }
    }
}

void MyAlgorithm::Learning()
{
    
    
    
    
    
    
}


void MyAlgorithm::run()
{
    
    initialize();
    evaluateFitness();

    int i = 0;
    while (i < 100)// !!!   "i < _setup.nb_evolution_steps()" j'ai mis 100 pour raccourcir le temps d'execution
    {
        Teaching();
        Learning();
        ++i;
    }

}