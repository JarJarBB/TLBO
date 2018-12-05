#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>

using namespace std;

enum fonction {Rosenbrock, Rastrigin, Ackley, Schwefel, Schaffer, Weierstrass};

class Problem
{
	public:
		Problem(int dimension, fonction f, int max_intervalle=500, int min_intervalle=-500);
		~Problem();

		friend ostream& operator<< (ostream& os, const Problem& pbm);
		friend istream& operator>> (istream& is, Problem& pbm);

		Problem& operator=  (const Problem& pbm) = default;
		bool operator== (const Problem& pbm) const;
		bool operator!= (const Problem& pbm) const;

		int dimension() const;
		double LowerLimit, UpperLimit;
		fonction func() const;

		void max_intervalle (const int val);
		void min_intervalle (const int val);

		const int   max_intervalle ()const;
		const int   min_intervalle ()const;

	private:

		int _dimension;
		fonction _fonction;
        int   _max_intervalle;
		int   _min_intervalle;
};

#endif // PROBLEM_H
