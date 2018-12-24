#include "Problem.h"

//Rosenbrock: -5,10 Rastrigin: -5,5 Ackley -32,32, Schwefel: -500, 500, Schaffer: -100,100 Weierstrass -5,5

Problem::Problem(int dimension, fonction f):
                _dimension{dimension}, _fonction{f},
                _max_intervalle{}, _min_intervalle{},
                _calls_to_function{0}
{
    switch (_fonction)
    {
        case Rosenbrock:
            _max_intervalle=10;
            _min_intervalle=-5;
        break;

        case Rastrigin:
             _max_intervalle=5;
            _min_intervalle=-5;
        break;

        case Ackley:
             _max_intervalle=32;
            _min_intervalle=-32;
        break;

        case Schwefel:
             _max_intervalle=500;
            _min_intervalle=-500;
        break;

        case Schaffer:
             _max_intervalle=100;
            _min_intervalle=-100;
        break;

        case Weierstrass:
             _max_intervalle=5;
            _min_intervalle=-5;
        break;
    }
}

Problem::~Problem()
{}

fonction Problem::func() const
{
    return _fonction;
}

int Problem::dimension() const
{
    return _dimension;
}

string Problem::name() const
{
    switch (_fonction)
    {
        case Rosenbrock:
            return "Rosenbrock";
        break;

        case Rastrigin:
            return "Rastrigin";
        break;

        case Ackley:
            return "Ackley";
        break;

        case Schwefel:
            return "Schwefel";
        break;

        case Schaffer:
            return "Schaffer";
        break;

        case Weierstrass:
            return "Weierstrass";
        break;
    }
}

const int Problem::max_intervalle () const
{
    return _max_intervalle;
}

const int Problem::min_intervalle () const
{
    return _min_intervalle;
}

void Problem::max_intervalle (const int val)
{
    _max_intervalle=val;
}

void Problem::min_intervalle (const int val)
{
    _min_intervalle=val;
}

long long int Problem::callsToFunction() const
{
    return _calls_to_function;
}

Problem& Problem::operator++()
{
    ++_calls_to_function;
    return *this;
}
