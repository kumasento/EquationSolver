#ifndef BAR_H__
#define BAR_H__

#include <cmath>

template <typename T>
class EquationSolver {
/**
 * This class will gracefully solve a equation as:
 * a * x^2 + b * x + c = 0 (1)
 */
public:
  /**
   * solve: Given all parameters, will create a equation and solve it
   * @ param a: a in the equation (1), default to be 0
   * @ param b: b in the equation (1), default to be 0
   * @ param c: c in the equation (1), default to be 0
   * @ param sol: Pointer to equation solutions.
   * @ return: Number of solutions, can only be 0, 1, 2.
   */
  int solve(T a = 0, T b = 0, T c = 0, T **sol = NULL) {
    // pointer to solution storage should not be null
    // or it will throw an exception
    if (sol == NULL) 
      throw "Pointer to solutions should not be NULL";    
    // core
    int num_sol = 0;
    T delta;
    if (a != 0) {
      delta = b * b - 4 * a * c;
      if (delta > 0) {
        // will have two results
        num_sol = 2;
        *sol = (T *) malloc(sizeof(T) * num_sol);
        if (*sol == NULL) 
          throw "Cannot allocate more memory";
        // two solutions
        (*sol)[0] = (-b + sqrt(delta))/(2 * a);
        (*sol)[1] = (-b - sqrt(delta))/(2 * a);
      } else if (delta < 0) {
        *sol = NULL; // there's no solution, set the solution pointer to NULL
      } else { /* delta == 0 */
        num_sol = 1;
        *sol = (T *) malloc(sizeof(T) * num_sol);
        if (*sol == NULL) 
          throw "Cannot allocate more memory";
        (*sol)[0] = -b / (2 * a); 
      }
    } else {
      if (b != 0) {
        num_sol = 1;
        *sol = (T *) malloc(sizeof(T) * num_sol);
        if (*sol == NULL) 
          throw "Cannot allocate more memory";
        (*sol)[0] = -c / b; 
      } else {
        if (c == 0) 
          return -1; // Infinite results
      }
    }

    return num_sol;
  }
};

#endif
