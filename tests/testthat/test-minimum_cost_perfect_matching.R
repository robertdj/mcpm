test_that("Minimum cost perfect matching", {
    # Input from C++ repo example
    graph <- data.frame(
        from = c(0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8),
        to = c(1, 2, 2, 5, 6, 3, 4, 4, 6, 7, 8, 6, 7, 8, 9, 9),
        cost = c(10, 4, 3, 2, 2, 1, 2, 5, 4, 1, 3, 1, 2, 3, 2, 1)
    )

    nvertices = length(unique(c(graph$from, graph$to)))
    nedges = nrow(graph)

    result <- minimum_cost_perfect_matching(nvertices, nedges, graph)

    expect_equal(result$cost, 14)

    expect_equal(
        result$edges,
        matrix(c(0, 1, 2, 3, 4, 7, 5, 6, 8, 9), ncol = 2, byrow = TRUE)
    )
})
