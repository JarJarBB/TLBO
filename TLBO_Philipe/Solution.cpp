#include "Solution.h"
#include <cmath>
#include <cstdlib>


Solution::Solution(const Problem& pbm): _pbm{pbm}
{}

Solution& Solution::operator=(const Solution& sol)
{
    _solution = sol._solution;
    _current_fitness = sol._current_fitness;

    return *this;
}

vector<double>& Solution::solution()
{
    return _solution;
}

// ====================================================

double fonctionRosenbrock(const std::vector<double> &X)
{
    double sum = 0.0;

    for (unsigned i = 0; i < X.size() - 1; ++i)
    {
        double c1 = (X[i + 1] - X[i] * X[i]);
        double c2 = (X[i] - 1.0);
        sum += 100.0 * c1 * c1 + c2 * c2;
    }

    return sum;
}

double fonctionRastrigin(const std::vector<double> &X)
{
    double pi = 3.1415926535;
    double A = 10.0;
    double sum = 0;

    for (auto Xi : X)
        sum += Xi * Xi - A * cos(2.0 * pi * Xi);

    return A * X.size() + sum;
}

double fonctionAckley(const std::vector<double> &X)
{
 double pi = 3.1415926535;
    double a = 20.0, b = 0.2, c = 2.0 * pi;
    double sum1 = 0.0, sum2 = 0.0;
    double d = X.size();

    for (auto Xi : X)
    {
        sum1 += Xi * Xi;
        sum2 += std::cos(c * Xi);
    }

    return -a * std::exp(-b * std::sqrt(sum1 / d)) - std::exp(sum2 / d) + a + std::exp(1.0);
}

double fonctionSchwefel(const std::vector<double> &X)
{
    double sum = 0;
    for (auto Xi : X)
        sum += Xi * sin(std::sqrt(std::abs(Xi)));

    return 418.9829 * X.size() - sum;
}

double fonctionSchaffer(const std::vector<double> &X)
{
    double x = X[0], y = X[1];
    double c1 = std::sin(x * x - y * y);
    double c2 = 1.0 + 0.001 * (x * x + y * y);

    return 0.5 + (c1 * c1 - 0.5) / (c2 * c2);
}

double fonctionWeierstrass(const std::vector<double> &X)
{
    double pi = 3.1415926535;
    double a = 0.5, b = 3.0;
    double kMax = 20.0;
    double sum1 = 0.0;

    for (auto Xi : X)
    {
        double sum2 = 0.0;

        for (int k = 0; k <= kMax; ++k)
            sum2 += std::pow(a, k) * std::cos( 2.0 * pi * std::pow(b, k) * (Xi + 0.5) );

        sum1 += sum2;
    }

    double sum3 = 0.0;

    for (int k = 0; k <= kMax; ++k)
        sum3 += std::pow(a, k) * std::cos( 2.0 * pi * std::pow(b, k) * 0.5 );


    return sum1 - X.size() * sum3;
}

// ====================================================

void Solution::fitness()
{
    double value = -1.0;
    switch(_pbm.func())
    {
         case Rosenbrock:
             value = fonctionRosenbrock(_solution);
         break;

         case Rastrigin:
             value = fonctionRastrigin(_solution);
         break;

         case Ackley:
             value = fonctionAckley(_solution);
         break;

         case Schwefel:
             value = fonctionSchwefel(_solution);
         break;

         case Schaffer:
             value = fonctionSchaffer(_solution);
         break;

         case Weierstrass:
             value = fonctionWeierstrass(_solution);
         break;
    }
    _current_fitness = value;
}

// ====================================================

double Solution::get_fitness() const
{
    return _current_fitness;
}

double generateDouble(int min, int max)
{
    return min + (max - min) * (rand() * 1.0 / RAND_MAX);
}

void Solution::generateDoubleWithinInterval(double& minborne,double& maxborne){
    minborne=generateDouble(_pbm.min_intervalle(), _pbm.max_intervalle());
    maxborne=generateDouble(minborne, _pbm.max_intervalle());
    _solution.push_back(generateDouble(minborne,maxborne));
}

void Solution::initialize()
{
    _solution.clear();
    _solution.reserve(_pbm.dimension());
    double minborne,maxborne;
    for (int i = 0; i < _pbm.dimension(); ++i)
    {
        generateDoubleWithinInterval(minborne,maxborne);
    }

}

ostream& operator<<(ostream& os, const Solution& sol)
{
    unsigned int i;
    for (i = 0; i < sol._solution.size() - 1; ++i)
        os << sol._solution[i] << ", ";
    os << sol._solution[i];
    return os;
}