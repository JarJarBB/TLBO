#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>

using namespace std;

enum fonction {Rosenbrock, Rastrigin, Ackley, Schwefel, Schaffer, Weierstrass, TheSpecialFunction};

class Problem
{
	public:
		Problem(int dimension, fonction f);
		~Problem();

		friend ostream& operator<<(ostream& os, const Problem& pbm);
		friend istream& operator>>(istream& is, Problem& pbm);

		Problem& operator=(const Problem& pbm);
		bool operator==(const Problem& pbm) const;
		bool operator!=(const Problem& pbm) const;
		Problem& operator++();

        string name() const;
		int dimension() const;
		fonction func() const;
        long long int callsToFunction() const;
		void max_intervalle (const int val);
		void min_intervalle (const int val);
		double max_intervalle () const;
		double min_intervalle () const;

	private:
		int _dimension;
		fonction _fonction;
        double _max_intervalle;
		double _min_intervalle;
		long long int _calls_to_function;
};

#endif // PROBLEM_H
