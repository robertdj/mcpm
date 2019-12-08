#include <Rcpp.h>
using namespace Rcpp;

#include "Matching.h"
#include "Graph.h"

pair< Graph, vector<double> > CreateGraph(int nvertices, int nedges, Rcpp::DataFrame edges) {
    Rcpp::IntegerVector to = edges["to"];
    Rcpp::IntegerVector from = edges["from"];
    vector<double> input_cost = edges["cost"];

    Graph G(nvertices);
	vector<double> cost(nedges);

    for (int i = 0; i < nedges; i++)
    {
        G.AddEdge(from[i], to[i]);
        cost[G.GetEdgeIndex(from[i], to[i])] = input_cost[i];
    }

    return make_pair(G, cost);
}


//' Compute minimum cost perfect matching
//'
//' @param nvertices The number of vertices in the graph.
//' @param nedges The number of edges in the graph.
//' @param edges A dataframe representing the edges and their cost with columns `from`, `to` and
//' `edges`.
//'
//' @return A list with entries `cost` (a number) and `edges` (a matrix).
//'
//' @export
//'
// [[Rcpp::export]]
Rcpp::List minimum_cost_perfect_matching(int nvertices, int nedges, Rcpp::DataFrame edges) {
    pair< Graph, vector<double> > p = CreateGraph(nvertices, nedges, edges);

	Graph G = p.first;
	vector<double> cost = p.second;

	Matching M(G);
    pair< list<int>, double> solution = M.SolveMinimumCostPerfectMatching(cost);

	list<int> matching = solution.first;

	NumericMatrix matching_edges(matching.size(), 2);
	int row_idx = 0;
	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
	{
		pair<int, int> e = G.GetEdge( *it );

	    matching_edges(row_idx, 0) = e.first;
	    matching_edges(row_idx, 1) = e.second;
	    row_idx++;
	}

    return Rcpp::List::create(Rcpp::Named("cost") = solution.second,
                              Rcpp::Named("edges") = matching_edges);
}
