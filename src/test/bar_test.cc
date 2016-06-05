
#include "gtest/gtest.h"
#include "bar.h"

float *sol;
int num_sol;
EquationSolver<float> *equation_solver = NULL;

TEST(FloatEquationSolverTest, TwoSolutionTest) {
  /**
   * x^2 - 1 = 0
   * solutions: +1, -1
   */
  num_sol = equation_solver->solve(1, 0, -1.0, &sol);
  EXPECT_EQ(num_sol, 2);
  EXPECT_FLOAT_EQ(sol[0], 1.0);
  EXPECT_FLOAT_EQ(sol[1], -1.0);

  /**
   * x^2 + 3x + 1 = 0
   * solutions: 
   */
  num_sol = equation_solver->solve(1.0, 3.0, 1.0, &sol);
  EXPECT_EQ(num_sol, 2);
  EXPECT_FLOAT_EQ(sol[0], -0.381966);
  EXPECT_FLOAT_EQ(sol[1], -2.618033);
}

TEST(FloatEquationSolverTest, OneSolutionTest) {
  /**
   * x^2 - 2x + 1 = 0
   * solutions: +1
   */
  num_sol = equation_solver->solve(1, -2.0, 1.0, &sol);
  EXPECT_EQ(num_sol, 1);
  EXPECT_FLOAT_EQ(sol[0], 1.0);

  /**
   * 2x + 1 = 0
   * solutions: -0.5
   */
  num_sol = equation_solver->solve(0, 2.0, 1.0, &sol);
  EXPECT_EQ(num_sol, 1);
  EXPECT_FLOAT_EQ(sol[0], -0.5);
}

TEST(FloatEquationSolverTest, ZeroSolutionTest) {
  /**
   * x^2 - 2x + 3 = 0
   * no solution
   */
  num_sol = equation_solver->solve(1.0, -2.0, 3.0, &sol);
  EXPECT_EQ(num_sol, 0);

  /**
   * 3 = 0
   * no solution
   */
  num_sol = equation_solver->solve(0, 0, 3.0, &sol);
  EXPECT_EQ(num_sol, 0);
}

TEST(FloatEquationSolverTest, InfSolutionTest) {
  /**
   * 0 = 0
   * infinite solution
   */
  num_sol = equation_solver->solve(0, 0, 0, &sol);
  EXPECT_EQ(num_sol, -1);
}
// Test NULL pointer exception
TEST(FloatEquationSolverTest, NullSolPtrTest) {
  /**
   * If solve takes no parameter, then the last pointer will be NULL
   * And then an exception will be thrown
   */
  ASSERT_ANY_THROW(equation_solver->solve());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  equation_solver = new EquationSolver<float>();
  return RUN_ALL_TESTS();
}
