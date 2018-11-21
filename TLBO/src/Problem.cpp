#include "Problem.h"

Problem::Problem(int dimension, fonction f):_dimension{dimension}, _fonction{f}
{}

Problem::~Problem()
{}

fonction Problem::func() const
{return _fonction;}

int Problem::dimension() const
{return _dimension;}
