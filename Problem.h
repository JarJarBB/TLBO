#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>

using namespace std;

enum fonction {Rosenbrock, Rastrigin, Ackley, Schwefel, Schaffer, Weierstrass};

class Problem
{
	public:
		Problem(int dimension, fonction f);
		~Problem();

		friend ostream& operator<< (ostream& os, const Problem& pbm);
		friend istream& operator>> (istream& is, Problem& pbm);

		Problem& operator=  (const Problem& pbm);
		bool operator== (const Problem& pbm) const;
		bool operator!= (const Problem& pbm) const;

		int dimension() const;
		double LowerLimit, UpperLimit;
		fonction func() const;

	private:

		int _dimension;
		fonction _fonction;
};

#endif // PROBLEM_H
