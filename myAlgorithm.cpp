#include "myAlgorithm.h"
#include <random>
#include <ctime>

int tabRandDiff[] = {1, 1, 2};
const double MAXSPEED = 1.6; // MAXSPEED > 1
const double SCALE_MIN = 1.0; // SCALE_MIN >= 1
const double SCALE_MAX = 200.0; // SCALE_MAX > SCALE_MIN && SCALE_MAX > 100
const double PM = 0.1; // Mutation rate
const int SIZE_CHOICE_INTERVAL = 6;
double tabChoiceInterval[SIZE_CHOICE_INTERVAL] = {3, 3, 3, 2, 1, 0};

MyAlgorithm::MyAlgorithm(const Problem& pbm, SetUpParams& setup) :
            _setup{setup},
            _solutions(setup.population_size()),
            _best_solution{nullptr},
            _pbm{pbm}, _results{}
{
    for (auto& i : _solutions)
        i = new Solution{pbm};
    _results.reserve(_setup.population_size());
}

MyAlgorithm::~MyAlgorithm()
{
    for (auto i : _solutions)
        delete i;

    delete _best_solution;
}

double generateDouble(double min = 0.0, double max = 1.0)
{
    return (rand() * 1.0 / (1.0 * RAND_MAX)) * (max - min) + min;
}

void MyAlgorithm::initialize()
{
    for (auto i : _solutions)
        i->initialize(); // i->Solution::initialize();
}

void MyAlgorithm::evaluateFitness()
{
    for(auto i : _solutions)
        i->fitness();
}

const vector<Solution*>& MyAlgorithm::solutions() const
{
    return _solutions;
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

void MyAlgorithm::determineBestSolution()
{
    if (_solutions.size())
    {
        int k = rand() % _setup.population_size();
        double minimum = _solutions[k]->get_fitness();
        _best_solution = _solutions[k];

        for (auto i : _solutions)
        {
            if (abs(i->get_fitness()) < abs(minimum))
            {
                minimum = i->get_fitness();
                _best_solution = i;
            }
        }
    }
}

void MyAlgorithm::UpdateBestSolutionOverall(Solution* &OverallBestSolution)
{
    if (!OverallBestSolution)
        OverallBestSolution = new Solution{*_best_solution};
    else if (abs(OverallBestSolution->get_fitness()) > abs(_best_solution->get_fitness()))
        *OverallBestSolution = *_best_solution;
}

Solution& MyAlgorithm::best_solution() const
{
    return *_best_solution;
}

double MyAlgorithm::Difference_Mean(int j, const vector<double>& Means, double r) const
{
    double Xbest = _best_solution->solution()[j];
    double Tf = tabRandDiff[rand() % 3]; //'One' is twice as likely to be chosen as '2'
    double M = Means[j];

    return r * (Xbest - Tf * M);
}

double MyAlgorithm::valueAdaptedToPbmInterval(double original, double current)
{
    double val;
    if (current <= _pbm.max_intervalle())
    {
        if(current >= _pbm.min_intervalle())
        {
            val = current;
        }
        else
        {
            int tamp = original - _pbm.min_intervalle();
            val = original - tamp * (rand() * 1.0 / RAND_MAX);
        }
    }
    else
    {
        int tamp = _pbm.max_intervalle() - original;
        val = original + tamp * (rand() * 1.0 / RAND_MAX);
    }

    return val;
}

void MyAlgorithm::changeSolutionWithinInterval(vector<double>& tabNewP, int j, double add)
{
    tabNewP[j] = valueAdaptedToPbmInterval(tabNewP[j], tabNewP[j] + add);
}

void MyAlgorithm::changeSolutionWithinIntervalAfterFactor(vector<double>& tabNewP, int j, double factor)
{
    tabNewP[j] = valueAdaptedToPbmInterval(tabNewP[j], tabNewP[j] * factor);
}

unsigned int absMinimumOfArray(double* t, int d)
{
    unsigned int pos = 0;
    for (int i = 1; i < d; ++i)
        if (abs(t[i]) < abs(t[pos])) pos = i;

    return pos;
}

double GenerateScale(int choiceInterval = -1)
{
    double SCALE;
    if (choiceInterval == -1) choiceInterval = rand() % 4;

    if (choiceInterval == 0) SCALE = generateDouble(SCALE_MIN, SCALE_MAX);
    else if (choiceInterval == 1) SCALE = generateDouble(SCALE_MIN, SCALE_MAX / 10.0);
    else if (choiceInterval == 2) SCALE = generateDouble(SCALE_MIN, SCALE_MAX / 100.0);
    else
    {
        double d = pow(10.0, rand() % 8 + 1); //increase the '8' for more precision after the comma
        SCALE = generateDouble(SCALE_MIN, SCALE_MIN + generateDouble(1.0 / d, 10.0 / d));
    }

    return SCALE;
}

double GenerateScaleWithType(int choiceInterval = -1, int type = -1)
{
    if (type == -1) type = rand() % 4;
    switch (type)
    {
        case 0: return 1.0 / GenerateScale(choiceInterval);
                break;
        case 1: return -1.0 / GenerateScale(choiceInterval);
                break;
        case 2: return GenerateScale(choiceInterval);
                break;
        default: return -GenerateScale(choiceInterval);
                break;
    }
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

const vector<double>& MyAlgorithm::results() const
{
    return _results;
}

double MyAlgorithm::meanResults() const
{
    double sum = accumulate(_results.begin(), _results.end(), 0.0);
    return sum / _results.size();
}

double MyAlgorithm::sdResults() const
{
    double mean = meanResults(), sum = 0.0;
    for (int i = 0; i < _results.size(); ++i)
       sum += (_results[i] - mean) * (_results[i] - mean);
    return sqrt( sum / _results.size() );
}

void MyAlgorithm::outputSummary(ostream& outputFile)
{
    outputFile << "Fonction : " << _pbm.name() << endl;
    outputFile << "Meilleure fitness : " << _best_solution->get_fitness() << " --- Solution :" << endl;
    outputFile << *_best_solution << endl;
    outputFile << "Moyenne : " << meanResults() << " Ecart-type : " << sdResults() << endl;
}

void MyAlgorithm::learnFromTeacher(int k, const vector<double>& Means, double r)
{
    Solution* newSolution = new Solution{*_solutions[k]};
    vector<double>& tabNewSolution{ newSolution->solution() };

    for (int j = 0; j < _setup.solution_size(); ++j)
    {
        double diffMean = Difference_Mean(j, Means, r);
        changeSolutionWithinInterval(tabNewSolution, j, diffMean);
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

void MyAlgorithm::TeachingPhase(double r)
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
            changeSolutionWithinInterval(tabNewP, j, add);
        }
    }
    else
    {
        for (int j = 0; j < _setup.solution_size(); ++j)
        {
            double add = r * (tabQ[j] - tabNewP[j]);
            changeSolutionWithinInterval(tabNewP, j, add);
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

void MyAlgorithm::LearningPhase(double r)
{
    for (int k = 0; k < _setup.population_size(); ++k)
    {
        int Q = rand() % _setup.population_size();
        learnFromPeer(k, Q, r);
    }
}

void MyAlgorithm::TutorPhase()
{
    double SCALE = GenerateScale(tabChoiceInterval[rand() % SIZE_CHOICE_INTERVAL]);
    const int ScaleTabSIZE = 4;
    double tabRandSCALE[] = {SCALE, 1.0 / SCALE, -1.0 / SCALE, -SCALE};

    vector<double>& trainee{_best_solution->solution()};

    double values[ScaleTabSIZE + 1];
    double fitness[ScaleTabSIZE + 1];

    for (int j = 0; j < _setup.solution_size(); ++j)
    {
        values[0] = trainee[j];

        for (int i = 1; i < ScaleTabSIZE + 1; ++i)
            values[i] = valueAdaptedToPbmInterval(values[0], tabRandSCALE[i - 1] * values[0]);

        for (int i = 0; i < ScaleTabSIZE + 1; ++i)
        {
            trainee[j] = values[i];
            _best_solution->fitness();
            fitness[i] = _best_solution->get_fitness();
        }
        int posMinFitness = absMinimumOfArray(fitness, ScaleTabSIZE + 1);

        trainee[j] = values[posMinFitness];
    }

    _best_solution->fitness();
}

void MyAlgorithm::solutionTranported(int pos)
{
    //double choiceInterval = rand() % 4;
    //double type = rand() % 4;

    Solution* newS = new Solution{*_solutions[pos]};
    vector<double>& tabNewS{ newS->solution() };

    for (int j = 0; j < _setup.solution_size(); ++j)
    {
        if (generateDouble() < PM)
        {
            double factor = GenerateScaleWithType(/*choiceInterval, type*/);
            changeSolutionWithinIntervalAfterFactor(tabNewS, j, factor);
        }
    }

    newS->fitness();
    if (abs(newS->get_fitness()) < abs(_solutions[pos]->get_fitness()))
    {
        delete _solutions[pos];
        _solutions[pos] = newS;
    }
    else
    {
        delete newS;
    }
}

void MyAlgorithm::TransportationPhase()
{
    for (int k = 0; k < _setup.population_size(); ++k)
        solutionTranported(k);
}

void MyAlgorithm::evolution(int iter, Viewer& fenetre)
{
    int i = 0;
    while (i < iter && _best_solution->get_fitness() != 0.0)
    {
        double r = generateDouble();
        TutorPhase();
        TeachingPhase(r);
        TransportationPhase();
        LearningPhase(r);
        determineBestSolution();

        /** Affichage graphique */
        fenetre.add(_best_solution->get_fitness());
        fenetre.clear();
        fenetre.afficheInit();
        /** Fin */

        cout << "\nFitness: " << _best_solution->get_fitness() << endl;
        cout << *_best_solution << endl;

        ++i;
    }
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
        evolution(_setup.nb_evolution_steps(), fenetre);
        _results.push_back(_best_solution->get_fitness());
        UpdateBestSolutionOverall(OverallBestSolution);
    }
    _best_solution = OverallBestSolution;

    cout << "\n---------------------------------------------------------\n";
    cout << "Fitness de la meilleure solution : " << _best_solution->get_fitness() << endl;
    cout << *_best_solution << "\n" << endl;
    cout << "Moyenne : " << meanResults() << " Ecart-type : " << sdResults() << "\n" << endl;
    cout << _setup << endl;
    cout << "Probleme optimise : la fonction " << _pbm.name() << endl;
    cout << "---------------------------------------------------------\n";
}
