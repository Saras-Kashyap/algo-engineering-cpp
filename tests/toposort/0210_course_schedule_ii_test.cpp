#include <gtest/gtest.h>
#include <vector>
#include "toposort/0210_course_schedule_ii.hpp" // Strictly pathed and lowercased

TEST(CourseScheduleIITest, Example1_Simple) {
    Solution sol;
    std::vector<std::vector<int>> prerequisites = {{1, 0}};
    std::vector<int> expected = {0, 1};
    EXPECT_EQ(sol.findOrder(2, prerequisites), expected);
}

TEST(CourseScheduleIITest, Example2_MultiplePaths) {
    Solution sol;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    // Kahn's algorithm will process neighbors in the order they were added to adj list
    // This yields {0, 1, 2, 3} for this specific setup
    std::vector<int> expected = {0, 1, 2, 3}; 
    EXPECT_EQ(sol.findOrder(4, prerequisites), expected);
}

TEST(CourseScheduleIITest, ImpossibleCycle) {
    Solution sol;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {0, 1}};
    std::vector<int> expected = {}; // Returns empty array if impossible
    EXPECT_EQ(sol.findOrder(2, prerequisites), expected);
}

TEST(CourseScheduleIITest, NoPrerequisites) {
    Solution sol;
    std::vector<std::vector<int>> prerequisites = {};
    // If no prerequisites, the queue is filled from 0 to numCourses - 1
    std::vector<int> expected = {0, 1, 2, 3}; 
    EXPECT_EQ(sol.findOrder(4, prerequisites), exected);
}