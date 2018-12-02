#include "myAlgorithm.h"
#include <random>
#include <ctime>

const int MAX_INTERVAL = 1000;
int tabRand[] = {1, 1, 2};

MyAlgorithm::MyAlgorithm(const Problem& pbm, const SetUpParams& setup) :
            _setup{setup},
            _solutions(setup.population_size()),
            _best_solution{nullptr}
{
    for (auto& i : _solutions)
        i = new Solution{pbm};
}

MyAlgorithm::~MyAlgorithm()
{
    for (auto i : _solutions)
        delete i;

    delete _best_solution;
}

void MyAlgorithm::initialize(const int MAX)
{
    for (auto i : _solutions)
        i->initialize(MAX); // i->Solution::initialize(MAX);
}

vector<double> MyAlgorithm::MeanPerColumn() const
{
    vector<double> Means(_setup.solution_size(), 0.0);

    for (auto k : _solutions)
    {
        if (k != _best_solution)
        {
            vector<double>& S = k->solution();
            for (int i = 0; i < S.size(); ++i)
                Means[i] += S[i];
        }
    }

    for (auto& i : Means)
        i /= _setup.population_size() - 1;

    return Means;
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
        int k = rand() % _setup.population_size();
        double min = _solutions[k]->get_fitness();
        _best_solution = _solutions[k];

        for (auto i : _solutions)
        {
            if (abs(i->get_fitness()) < abs(min))
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

double MyAlgorithm::Difference_Mean(int j, const vector<double>& Means, double r) const
{
    double Xbest = _best_solution->solution()[j];
    double Tf = tabRand[(rand() % 2)+1]; //'One' is twice as likely to be chosen as '2' : euh pas sur que ce soit bon
    double M = Means[j];

    return r * (Xbest - Tf * M);
}

void MyAlgorithm::learnFromTeacher(int k, const vector<double>& Means, double r)
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

void MyAlgorithm::Teaching(double r)
{
    vector<double> Means = MeanPerColumn();
    for (int k = 0; k < _setup.population_size(); ++k)
    {
        if (_solutions[k] != _best_solution)
        {
            learnFromTeacher(k, Means, r);
        }
    }
}

void MyAlgorithm::learnFromPeer(int P, int Q, double r)
{
    Solution* newP = new Solution{*_solutions[P]};
    vector<double>& tabNewP{ newP->solution() };
    vector<double>& tabQ{ _solutions[Q]->solution() };

    if (abs(newP->get_fitness()) < abs(_solutions[Q]->get_fitness()))
    {
        for (int j = 0; j < _setup.solution_size(); ++j)
            tabNewP[j] += r * (tabNewP[j] - tabQ[j]);
    }
    else
    {
        for (int j = 0; j < _setup.solution_size(); ++j)
            tabNewP[j] += r * (tabQ[j] - tabNewP[j]);
    }

    newP->fitness();

    if (abs(newP->get_fitness()) < abs(_solutions[P]->get_fitness()))
    {
        delete _solutions[P];
        _solutions[P] = newP;
    }
    else delete newP;
}

void MyAlgorithm::Learning(double r)
{
    for (int k = 0; k < _setup.population_size(); ++k)
    {
        int Q = rand() % _setup.population_size();
        learnFromPeer(k, Q, r);
    }
}

void MyAlgorithm::evolution(int iter)
{
    int i = 0;
    while (i < iter && _best_solution->get_fitness()!=0)
    {
        double r = rand() * 1.0 / RAND_MAX;
        Teaching(r);
        Learning(r);
        determineBestSolution();
        ++i;

        cout << endl << "Fitness: " << _best_solution->get_fitness() << endl;
        cout << *_best_solution << endl;
    }
}

void MyAlgorithm::UpdateBestSolutionOverall(Solution* &OverallBestSolution)
{
    if (!OverallBestSolution)
        OverallBestSolution = new Solution{*_best_solution};
    else if (abs(OverallBestSolution->get_fitness()) > abs(_best_solution->get_fitness()))
        *OverallBestSolution = *_best_solution;
}

void MyAlgorithm::run()
{
    srand(static_cast<unsigned int>(time(NULL)));
    vector<int> TRIALS;
    TRIALS.reserve(_setup.independent_runs());
    for (int i = 0; i < TRIALS.capacity(); ++i)
        TRIALS.push_back(rand() % MAX_INTERVAL + 1);

    Solution* OverallBestSolution = nullptr;

    for (int MAXi : TRIALS)
    {
        initialize(MAXi);
        evaluateFitness();
        determineBestSolution();
        evolution(_setup.nb_evolution_steps());
        UpdateBestSolutionOverall(OverallBestSolution);
        if (_best_solution->get_fitness()==0) break;
    }
    _best_solution = OverallBestSolution;
}
