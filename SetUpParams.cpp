#include "SetUpParams.h"

SetUpParams::SetUpParams(unsigned int independent_runs,
                         unsigned int nb_evolution_steps,
                         unsigned int population_size,
                         unsigned int solution_size):
                             _independent_runs(independent_runs),
                             _nb_evolution_steps(nb_evolution_steps),
                             _population_size(population_size),
                             _solution_size(solution_size)
{}

unsigned int SetUpParams::independent_runs() const
{
    return _independent_runs;
}

unsigned int SetUpParams::nb_evolution_steps() const
{
    return _nb_evolution_steps;
}

unsigned int SetUpParams::population_size() const
{
    return _population_size;
}

unsigned int SetUpParams::solution_size() const
{
    return _solution_size;
}

void SetUpParams::independent_runs(const unsigned int val)
{
    _independent_runs = val;
}

void SetUpParams::nb_evolution_steps(const unsigned int val)
{
    _nb_evolution_steps = val;
}

void SetUpParams::population_size(const unsigned int val)
{
    _population_size = val;
}

void SetUpParams::solution_size(const unsigned int val)
{
    _solution_size = val;
}

ostream& operator<<(ostream& os, const SetUpParams& setup)
{
    os << "Le nombre de runs independants est " << setup.independent_runs() << endl;
    os << "Le nombre d'evolutions est " << setup.nb_evolution_steps() << endl;
    os << "Le nombre d'individu est " << setup.population_size() << endl;
    os << "La taille d'une solution est " << setup.solution_size() << endl;

    return os;
}

istream& operator>>(istream& is, SetUpParams& setup)
{
    int val;
    
    cout << "Nombre de run independant ? " << endl;
    is >> val;
    cout << endl;
    if (val >= 0) setup.independent_runs(val);
    
    cout << "Nombre de generation ? " << endl;
    is >> val;
    cout << endl;
    if (val >= 0) setup.nb_evolution_steps(val);
    
    cout << "Taille de la population ? " << endl;
    is >> val;
    cout << endl;
    if (val >= 0) setup.population_size(val);
    
    cout << "Taille d'une solution ? " << endl;
    is >> val;
    cout << endl;
    if (val >= 0) setup.solution_size(val);

    return is;
}


SetUpParams::~SetUpParams()
{

}
