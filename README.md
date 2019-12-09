# mcpm

<!-- badges: start -->
[![Travis build status](https://travis-ci.org/robertdj/mcpm.svg?branch=master)](https://travis-ci.org/robertdj/mcpm)
[![AppVeyor build status](https://ci.appveyor.com/api/projects/status/github/robertdj/mcpm?branch=master&svg=true)](https://ci.appveyor.com/project/robertdj/mcpm)
<!-- badges: end -->

This R package is an interface to the C++ code from this repository:
<https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching>


## Installation

This package is only on GitHub and can be installed with the [remotes package](https://remotes.r-lib.org):

``` r
remotes::install_github("robertdj/mcpm")
```

## Example

There is currently one function in the *mcpm* package, `minimum_cost_perfect_matching` operating on a graph represented as a dataframe with columns `from`, `to` and `cost`, where each row represents an edge.
The vertices are assumed to be numbered from 0 and onwards.

This example is also used in the tests and the values are from the original C++ repository:

``` r
library(mcpm)
graph <- data.frame(
    from = c(0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8),
    to = c(1, 2, 2, 5, 6, 3, 4, 4, 6, 7, 8, 6, 7, 8, 9, 9),
    cost = c(10, 4, 3, 2, 2, 1, 2, 5, 4, 1, 3, 1, 2, 3, 2, 1)
)
```

Here the number of vertices in the graph is 10 and the number of edges is 16.
The output is a list with entries `cost` (a number) and `edges` (a matrix).
With the [zeallot package](https://github.com/r-lib/zeallot):

``` r
library(zeallot)
c(cost, edges) %<-% minimum_cost_perfect_matching(10, 16, graph)
```

The output is then
``` r
> cost
[1] 14
> edges
     [,1] [,2]
[1,]    0    1
[2,]    2    3
[3,]    4    7
[4,]    5    6
[5,]    8    9
```

## License

The original C++ is MIT licensed, but [by using Rcpp](https://cloud.r-project.org/web/packages/Rcpp/vignettes/Rcpp-FAQ.pdf) the version in this repository has to be licensed by GPL2.

