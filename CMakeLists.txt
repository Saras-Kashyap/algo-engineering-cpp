cmake_minimum_required(VERSION 3.14)
project(LeetCodeEnterprise CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and incorporate Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Include your source files so the tests can find them
include_directories(src)

# --- Add Your Test Files Here ---
add_executable(two_sum_test tests/arrays/two_sum_test.cpp)
target_link_libraries(two_sum_test gtest_main)
add_test(NAME TwoSumTest COMMAND two_sum_test)

add_executable(best_time_to_buy_and_sell_stock_test tests/arrays/best_time_to_buy_and_sell_stock_test.cpp)
target_link_libraries(best_time_to_buy_and_sell_stock_test gtest_main)
add_test(NAME BestTimeToBuyAndSellStockTest COMMAND best_time_to_buy_and_sell_stock_test)