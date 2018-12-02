#include "SetUpParams.h"

SetUpParams::SetUpParams(unsigned int independent_runs,
                         unsigned int nb_evolution_steps,
                         unsigned int population_size,
                         unsigned int solution_size):
                             _independent_runs{independent_runs} ,
                             _nb_evolution_steps{nb_evolution_steps} ,
                             _population_size{population_size} ,
                             _solution_size{solution_size} {}

const unsigned int SetUpParams::independent_runs() const
{
    return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const
{
    return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const
{
    return _population_size;
}

const unsigned int SetUpParams::solution_size() const
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

ostream& operator<< (std::ostream& os, const SetUpParams& setup)
{
    os<<"Le nombre de runs independants est "<<setup.independent_runs()<<std::endl<<"Le nombre d'evolutions est "<<setup.nb_evolution_steps()
    <<std::endl<<"Le nombre d'individu est "<<setup.population_size()<<std::endl<<"La taille d'une solution est "<<setup.solution_size()<<std::endl;
    return os;
}

istream& operator>> (std::istream& is, SetUpParams& setup)
{
    int val;
    cout<<"Number of independant run?"<<std::endl;
    is>>val;
    cout<<std::endl;
    if(val>=0)
    {
        setup.independent_runs(val);
    }
    cout<<"Number of evolutions steps?"<<std::endl;
    is>>val;
    cout<<std::endl;
    if(val>=0)
    {
        setup.nb_evolution_steps(val);
    }
    cout<<"Size of population?"<<std::endl;
    is>>val;
    cout<<std::endl;
    if(val>=0)
    {
        setup.population_size(val);
    }
    cout<<"Size of solution?"<<std::endl;
    is>>val;
    cout<<std::endl;
    if(val>=0)
    {
        setup.solution_size(val);
    }
    return is;
}


SetUpParams::~SetUpParams()
{
    //dtor
}
