test_that("Minimum cost perfect matching", {
    # Input from C++ repo example
    graph <- matrix(
        c(0, 1, 10,
        0, 2, 4,
        1, 2, 3,
        1, 5, 2,
        1, 6, 2,
        2, 3, 1,
        2, 4, 2,
        3, 4, 5,
        4, 6, 4,
        4, 7, 1,
        4, 8, 3,
        5, 6, 1,
        6, 7, 2,
        7, 8, 3,
        7, 9, 2,
        8, 9, 1),
        ncol = 3, byrow = TRUE
    )

    input_file <- tempfile()
    write("10", file = input_file)
    write("16", file = input_file, append = TRUE)
    write.table(graph, file = input_file, append = TRUE, row.names = FALSE, col.names = FALSE)

    result <- minimum_cost_perfect_matching(input_file)

    expect_equal(result$cost, 14)

    expect_equal(
        result$edges,
        matrix(c(0, 1, 2, 3, 4, 7, 5, 6, 8, 9), ncol = 2, byrow = TRUE)
    )
})
