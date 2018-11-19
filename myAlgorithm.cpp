#include "myAlgorithm.h"


MyAlgorithm::MyAlgorithm(const Problem& pbm,const SetUpParams& setup) : _setup{setup}, _solutions(setup.population_size()), _best_solution{nullptr}
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


void MyAlgorithm::run()
{
    initialize();
    evaluateFitness();
    determineBestSolution();
}
