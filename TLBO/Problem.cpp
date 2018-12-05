#include "Problem.h"

Problem::Problem(int dimension, fonction f, int max_intervalle,int min_intervalle):
                _dimension{dimension}, _fonction{f}, _max_intervalle{max_intervalle},_min_intervalle{min_intervalle}
{}

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

const int   Problem::max_intervalle ()const
{
    return _max_intervalle;
}

const int   Problem::min_intervalle ()const
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
