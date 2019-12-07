#include <Rcpp.h>
using namespace Rcpp;
#include <string>
#include "Matching.h"
#include "Graph.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
// #include <string>
#include <sstream>
using namespace std;


pair< Graph, vector<double> > ReadWeightedGraph1(string filename)
{
	//Please see Graph.h for a description of the interface

	ifstream file;
	file.open(filename.c_str());

	string s;
	getline(file, s);
	stringstream ss(s);
	int n;
	ss >> n;
	getline(file, s);
	ss.str(s);
	ss.clear();
	int m;
	ss >> m;

	Graph G(n);
	vector<double> cost(m);
	for(int i = 0; i < m; i++)
	{
		getline(file, s);
		ss.str(s);
		ss.clear();
		int u, v;
		double c;
		ss >> u >> v >> c;

		G.AddEdge(u, v);
		cost[G.GetEdgeIndex(u, v)] = c;
	}

	file.close();
	return make_pair(G, cost);
}


//' @export
// [[Rcpp::export]]
Rcpp::List minimum_cost_perfect_matching(String filename) {
    Graph G;
    vector<double> cost;

    pair< Graph, vector<double> > p = ReadWeightedGraph1(filename);

	G = p.first;
	cost = p.second;

	Matching M(G);
    pair< list<int>, double> solution = M.SolveMinimumCostPerfectMatching(cost);

	list<int> matching = solution.first;
	double obj = solution.second;

	NumericMatrix edges(matching.size(), 2);

	int row_idx = 0;
	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
	{
		pair<int, int> e = G.GetEdge( *it );

	    edges(row_idx, 0) = e.first;
	    edges(row_idx, 1) = e.second;
	    row_idx++;
	}

    return Rcpp::List::create(Rcpp::Named("cost") = obj,
                              Rcpp::Named("edges") = edges);
}
