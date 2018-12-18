#include "myAlgorithm.h"
#include <random>
#include <ctime>

const double MAXSPEED = 1.6;
int tabRand[] = {1, 1, 2};

MyAlgorithm::MyAlgorithm(const Problem& pbm, SetUpParams& setup) :
            _setup{setup},
            _solutions(setup.population_size()),
            _best_solution{nullptr},
            _pbm{pbm}
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

void MyAlgorithm::initialize()
{
    for (auto i : _solutions)
        i->initialize(); // i->Solution::initialize(MAX);
}

void MyAlgorithm::speedControl(const vector<double> &oldS, vector<double> &newS) const
{
    for (int i = 0; i < oldS.size(); ++i)
    {
        double signe;
        if (newS[i] / oldS[i] >= 0.0) signe = 1.0;
        else signe = -1.0;

        if (abs(newS[i]) > abs(oldS[i] * MAXSPEED))
            newS[i] = signe * oldS[i] * MAXSPEED;
        else if (abs(newS[i]) < abs(oldS[i] / MAXSPEED))
            newS[i] = signe * oldS[i] / MAXSPEED;
    }
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
    double Tf = tabRand[rand() % 3]; //'One' is twice as likely to be chosen as '2'
    double M = Means[j];

    return r * (Xbest - Tf * M);
}

void MyAlgorithm::VerificationSolutionWithinInterval(vector<double>& tabNewP, int j, double add)
{
    if (tabNewP[j] + add <= _pbm.max_intervalle())
    {
        if(tabNewP[j] + add >= _pbm.min_intervalle())
        {
            tabNewP[j] += add;
        }
        else
        {
            int tamp=tabNewP[j]-_pbm.min_intervalle();
            tabNewP[j]-=tamp*(rand() * 1.0 / RAND_MAX);
        }
    }
    else
    {
        int tamp=_pbm.max_intervalle()-tabNewP[j];
        tabNewP[j]+=tamp*(rand() * 1.0 / RAND_MAX);
    }
}

void MyAlgorithm::learnFromTeacher(int k, const vector<double>& Means, double r)
{
    Solution* newSolution = new Solution{*_solutions[k]};
    vector<double>& tabNewSolution{ newSolution->solution() };

    for (int j = 0; j < _setup.solution_size(); ++j)
    {
        double diffMean = Difference_Mean(j, Means, r);
        VerificationSolutionWithinInterval(tabNewSolution, j, diffMean);
    }
    speedControl(_solutions[k]->solution(), tabNewSolution);
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
            learnFromTeacher(k, Means, r);
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
        {
            double add = r * (tabNewP[j] - tabQ[j]);
            VerificationSolutionWithinInterval(tabNewP,j,add);
        }
    }
    else
    {
        for (int j = 0; j < _setup.solution_size(); ++j)
        {
            double add = r * (tabQ[j] - tabNewP[j]);
            VerificationSolutionWithinInterval(tabNewP,j,add);
        }
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

void MyAlgorithm::evolution(int iter,Viewer& fenetre)
{
    int i = 0;
    while (i < iter && _best_solution->get_fitness() != 0.0)
    {
        double r = rand() * 1.0 / RAND_MAX;
        Teaching(r);
        Learning(r);
        determineBestSolution();
        ++i;
        /** Affichage graphique*/
        /*
        fenetre.add(_best_solution->get_fitness());
        fenetre.clear();
        fenetre.afficheInit(); *//** Fin */
        //delay(100);
        cout << "\nFitness: " << _best_solution->get_fitness() << endl;
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

void MyAlgorithm::run(Viewer& fenetre)
{
    srand(static_cast<unsigned int>(time(NULL)));

    Solution* OverallBestSolution = nullptr;

    for (int i = 0; i < _setup.independent_runs(); ++i)
    {
        initialize();
        evaluateFitness();
        determineBestSolution();
        evolution(_setup.nb_evolution_steps(),fenetre);
        UpdateBestSolutionOverall(OverallBestSolution);
        if (OverallBestSolution->get_fitness() == 0.0) {
            fenetre.waitUntilButton();
            break;
        }
    }
    _best_solution = OverallBestSolution;
}
