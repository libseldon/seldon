// Copyright (C) 2001-2008 Vivien Mallet
//
// This file is part of Seldon library.
// Seldon library provides matrices and vectors structures for
// linear algebra.
// 
// Seldon is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Seldon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the Seldon home page:
//     http://spacetown.free.fr/lib/seldon/

#ifndef SELDON_FILE_ITERATIVE_HXX

namespace Seldon
{
  //! Base class for preconditioners
  class Preconditioner_Base
  {
  public :
    
    Preconditioner_Base();
    
    // solving M z = r
    template<class T2, class Storage2, class Allocator2, class Matrix> 
    void Solve(const Matrix& A, const Vector<T2,Storage2,Allocator2> & r,
	       Vector<T2,Storage2,Allocator2> & z);
    
    // solving M^t z = r
    template<class T2, class Storage2, class Allocator2, class Matrix> 
    void TransSolve(const Matrix& A, const Vector<T2,Storage2,Allocator2> & r,
		    Vector<T2,Storage2,Allocator2> & z);
    
  };
  
  
  //! Class containing parameters for an iterative resolution
  /*!
    Titer is the precision (float or double), the solved
    linear system can be real or complex
   */
  template<class Titer>
  class Iteration
  {
  protected :
    Titer tolerance; //!< stopping criterion
    Titer facteur_reste; //!< inverse of norm of first residual
    int max_iter; //!< maximum number of iterations
    int nb_iter; //!< number of iterations
    int error_code; //!< error code returned by iterative solver
    bool fail_convergence; //!< true if the iterative solver has converged
    //! print level
    /*!
      0 -> no display
      1 -> displays residual after each 100 iterations
      6 -> displays residual after each iteration
    */
    int print_level;
    bool init_guess_null; //!< true if initial guess is null
    int type_solver; //!< iterative solver used
    int parameter_restart; //!< restart parameter (for Gmres and Gcr)
    int type_preconditioning; //!< preconditioner used
    
  public :
    
    Iteration();
    Iteration(int max_iteration, const Titer& tol);    
    Iteration(const Iteration<Titer>& outer);
    
    int GetTypeSolver() const;
    int GetRestart() const;
    Titer GetFactor() const;
    Titer GetTolerance() const;
    int GetNumberIteration() const;
    
    void SetSolver(int type_resolution, int param_restart, int type_prec);
    void SetRestart(int m);
    void SetTolerance(Titer stopping_criterion);
    void SetMaxNumberIteration(int max_iteration);
    void SetNumberIteration(int nb);
    
    void ShowMessages();
    void ShowFullHistory();
    void HideMessages();
    
    template<class T,class Storage,class Allocator>
    int Init(const Vector<T,Storage,Allocator>& r);
    bool First() const;

    bool IsInitGuess_Null() const;
    void SetInitGuess(bool type) { init_guess_null = type; }

    template<class T,class Storage,class Allocator>
    bool Finished(const Vector<T,Storage,Allocator>& r) const;
    bool Finished(const Titer& r) const;
    
    void Fail(int i, const string& s);
    
    Iteration& operator ++ (void);
    
    int ErrorCode() const;
    
  };  
  
} // end namespace

#define SELDON_FILE_ITERATIVE_HXX
#endif