#include "Solution.h"
#include <cmath>
#include <cstdlib>

const double PI = 3.1415926535;
const double E = 2.7182818284;

Solution::Solution(Problem& pbm): _solution(), _current_fitness(), _pbm(pbm)
{}

Solution::Solution(const Solution& sol):
    _solution(sol._solution),
    _current_fitness(sol._current_fitness),
    _pbm(sol._pbm)
{}

Solution::~Solution()
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

double generateDouble(double min = 0.0, double max = 1.0);

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
    double A = 10.0;
    double sum = 0;

    for (unsigned i = 0; i < X.size(); ++i)
        sum += X[i] * X[i] - A * cos(2.0 * PI * X[i]);

    return A * X.size() + sum;
}

double fonctionAckley(const std::vector<double> &X)
{
    double a = 20.0, b = 0.2, c = 2.0 * PI;
    double sum1 = 0.0, sum2 = 0.0;
    double d = X.size();

    for (unsigned i = 0; i < X.size(); ++i)
    {
        sum1 += X[i] * X[i];
        sum2 += std::cos(c * X[i]);
    }

    return -a * std::exp(-b * std::sqrt(sum1 / d)) - std::exp(sum2 / d) + a + std::exp(1.0);
}

double fonctionSchwefel(const std::vector<double> &X)
{
    double sum = 0;

    for (unsigned i = 0; i < X.size(); ++i)
        sum += X[i] * std::sin(std::sqrt(std::abs(X[i])));

    return 418.9828872724337998 * X.size() - sum;
}

double fonctionSchaffer(const std::vector<double> &X)
{
    if (X.size() < 2) return -1.0;

    double x = X[0], y = X[1];
    double c1 = std::sin(x * x - y * y);
    double c2 = 1.0 + 0.001 * (x * x + y * y);

    return 0.5 + (c1 * c1 - 0.5) / (c2 * c2);
}

double fonctionWeierstrass(const std::vector<double> &X)
{
    double a = 0.5, b = 3.0;
    double kMax = 20.0;
    double sum1 = 0.0;

    for (unsigned i = 0; i < X.size(); ++i)
    {
        double sum2 = 0.0;

        for (int k = 0; k <= kMax; ++k)
            sum2 += std::pow(a, k) * std::cos( 2.0 * PI * std::pow(b, k) * (X[i] + 0.5) );

        sum1 += sum2;
    }

    double sum3 = 0.0;

    for (int k = 0; k <= kMax; ++k)
        sum3 += std::pow(a, k) * std::cos( 2.0 * PI * std::pow(b, k) * 0.5 );

    return sum1 - X.size() * sum3;
}

double fonctionTheSpecialFunction(const std::vector<double> &X)
{
    double sum = 0.0;

    for (unsigned i = 0; i < X.size(); ++i)
    {
        if (i + 1 == 2) sum += std::pow(std::fabs(X[i] - E), 2);
        else if (i + 1 == 3) sum += std::pow(std::fabs(X[i] - PI), 2);
        else sum += std::pow(std::fabs(X[i] - (i + 1)), 2);
    }
    
    return double{sum};
}

// ====================================================

void Solution::fitness()
{
    ++_pbm;
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

        case TheSpecialFunction:
            value = fonctionTheSpecialFunction(_solution);
        break;
    }
    _current_fitness = value;
}

// ====================================================

double Solution::get_fitness() const
{
    return _current_fitness;
}

void  Solution::set_fitness(double fitness)
{
    _current_fitness = fitness;
}

void Solution::generateDoubleWithinInterval(double& minborne, double& maxborne)
{
    minborne = generateDouble(_pbm.min_intervalle(), _pbm.max_intervalle());
    maxborne = generateDouble(minborne, _pbm.max_intervalle());
}

void Solution::initialize()
{
    _solution.clear();
    _solution.reserve(_pbm.dimension());

    double minborne, maxborne;
    generateDoubleWithinInterval(minborne, maxborne);

    for (int i = 0; i < _pbm.dimension(); ++i)
        //_solution.push_back(generateDouble(minborne, maxborne));
        _solution.push_back(generateDouble(_pbm.min_intervalle(), _pbm.max_intervalle()));
}

Solution& Solution::operator*=(double factor)
{
    for (unsigned i = 0; i < _solution.size(); ++i)
        _solution[i] *= factor;

    return *this;
}

Solution Solution::operator*(double factor) const
{
    Solution S2(*this);
    S2 *= factor;

    return S2;
}

ostream& operator<<(ostream& os, const Solution& sol)
{
    unsigned i;
    for (i = 0; i < sol._solution.size() - 1; ++i)
        os << sol._solution[i] << ", ";
    os << sol._solution[i];
    return os;
}
