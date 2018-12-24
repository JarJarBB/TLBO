#ifndef SOLUTION_H
#define SOLUTION_H
#include <iostream>
#include <vector>
#include "SetUpParams.h"
#include "Problem.h"

using namespace std;

class Solution
{
	public:
		Solution(Problem& pbm);
		Solution(const Solution& sol) = default;
		~Solution() = default;

 		friend ostream& operator<<(ostream& os, const Solution& sol);
		friend istream& operator>>(istream& is, Solution& sol);

		const Problem& pbm() const;

		Solution& operator=(const Solution& sol);
		bool operator==(const Solution& sol) const;
		bool operator!=(const Solution& sol) const;
		Solution& operator*=(double factor); //added
		Solution operator*(double factor) const; //added

		void initialize();
		void fitness();
		double get_fitness() const;

		unsigned int size() const;

		vector<double>& solution();

		double& position(const int index);
        void  position(const int index, const double value);

	private:
        vector<double> _solution;
        double _current_fitness;
		Problem& _pbm;
		void generateDoubleWithinInterval(double& min, double& max);
};

#endif // SOLUTION_H
