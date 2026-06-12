// ... existing tests (Example1, Example2, Example3, etc.) ...

TEST(MakingALargeIslandTest, AllOnesLargeGrid) {
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    // No zeros to flip, the largest island is the entire grid
    EXPECT_EQ(sol.largestIsland(grid), 9);
}

TEST(MakingALargeIslandTest, SingleZero) {
    Solution sol;
    std::vector<std::vector<int>> grid = {{0}};
    // Flipping the only zero gives an island of size 1
    EXPECT_EQ(sol.largestIsland(grid), 1);
}

TEST(MakingALargeIslandTest, SingleOne) {
    Solution sol;
    std::vector<std::vector<int>> grid = {{1}};
    // No zeros to flip, returns the existing island size
    EXPECT_EQ(sol.largestIsland(grid), 1);
}

TEST(MakingALargeIslandTest, ConnectFourSeparateIslands) {
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    // Flipping the central 0 at (1,1) connects the 4 surrounding 1s
    // Total size: 1 (center) + 4 (surrounding components of size 1) = 5
    EXPECT_EQ(sol.largestIsland(grid), 5);
}

TEST(MakingALargeIslandTest, OptimalStrategicFlip) {
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {1, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 1}
    };
    // The largest existing component is a 2x2 square of 1s (size 4).
    // The right side has a 2x1 rectangle of 1s (size 2).
    // Flipping the 0 at (2,2) connects the size 4 and size 2 components.
    // Total size: 4 + 2 + 1 (the flipped zero) = 7.
    EXPECT_EQ(sol.largestIsland(grid), 7);
}

TEST(MakingALargeIslandTest, LargeAllZeros) {
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    // Flipping any zero gives a max island size of exactly 1
    EXPECT_EQ(sol.largestIsland(grid), 1);
}