#ifndef SOLUTION_H
#define SOLUTION_H
#include <iostream>
#include <vector>


#include "Problem.h"

using namespace std;

class Solution
{
 	//contient la declaration d'une solution
	public:
		Solution (const Problem& pbm);
		Solution (const Solution& sol) = default;
		~Solution() = default;

 		friend ostream& operator<< (ostream& os, const Solution& sol);
		friend istream& operator>> (istream& is, Solution& sol);

		const Problem& pbm() const;

		Solution& operator=  (const Solution& sol);
		bool operator== (const Solution& sol) const;
		bool operator!= (const Solution& sol) const;

		void initialize(const int MAX);
		void fitness();
		double get_fitness() const;

		unsigned int size() const;

		vector<double>& solution();

		double& position(const int index); //retournera une position du tableau _solution
        void  position(const int index, const double value);


	private:
        vector<double> _solution;
        double _current_fitness;
		const Problem& _pbm;
};

#endif // SOLUTION_H
