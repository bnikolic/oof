/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file minim.hxx

*/
#ifndef __BNMIN__ALGO__MINIM_HXX
#define __BNMIN__ALGO__MINIM_HXX

#include <string>
#include <vector>


#include "paramctr.hxx"
#include "minimmodel.hxx"

/// Namespace for the BNMin1 library
namespace Minim {

  // Forward declarations
  class Monitor;

  
  /** \brief Description of a model for an obseration, providing
      functions for handling parameters

   This class can hold the model description but can not do the
   actuall minimisation as it does not demand that the model has a
   figure-of-merit function.

  */
  class ModelDesc {
    
  protected :
    
    Model & mod;

  public:

    /* --------- Public data ---------------------- */
    std::vector <DParamCtr> pars ;
    
    /* --------- Constructors / Desctructors ------- */

    ModelDesc( Model &mod );

    virtual ~ModelDesc(void);

    // ---------- Public interface --------------------------

    // Routines to access the model parameters
    DParamCtr * operator[] (const std::string &name);
    DParamCtr * getbyname  (const std::string &name) { return this->operator[](name);};

    // Routines to access the model parameters by id number
    DParamCtr * operator[] (unsigned i) { return &pars[i]; }
    DParamCtr * getbynumb  (unsigned i) {  return this->operator[](i); };

    /*! Returns the total number of params, both fitted and not
     *  fitted */
    unsigned NTotParam(void) const { return pars.size() ; }

    /*! Copies the parameter values from the supplied ModelDesc */
    void CopyParsFrom ( ModelDesc & mod2 );

    /** Returns the number of parameters to be fitted, i.e. excluding
	those with do fit set to false
    */
    unsigned NParam(void) const;

    /** Copy supplied values to parameters

	Only fitted-for parameters are copied to
    */
    void copytopars(const double *x) ;

    /** Like copytopars but take a vector 
     */
    void put(const std::vector<double>  & x)
    {
      if (x.size() != NParam())
      {
	throw NParsErr("ModelDesc::Put", NParam(), x.size());
      }
      copytopars(&x[0]);
    }

    /** Copy parameters to supplied vector
     */
    void copyfrompars(double *x) ;

    void get(std::vector<double>  & x)
    {
      copyfrompars(&x[0]) ;
    }



  };


  /** \brief Provides the "solve" interface function

      Demands that a Minimisable is passed to the constructor, hence
      provides the "solve" function interface
   */
  class Minimiser: 
    public ModelDesc 
  {

  private:
    unsigned iter;
    Minimisable &m;
    std::vector< double >   res;
  protected:
    bool MonitorChi;
    int  MonitorChi_stride;
    int  MonitorChi_cno;

  public:

    // Monitor class is called every iteration
    std::vector<Monitor *>  mons;
    void AddMon (Monitor * mon);

    // --------- Constructors / Desctructors -------------------
    
    Minimiser (Minimisable &pm) ;
    virtual ~Minimiser(void ) {} ;


    /// Evaluate the residuals for the current model
    void ResEval       (void ) ;

    /// Calculats the ChiSquared i.e. the sum of the squares of the
    /// values stored in the res vector
    double ChiSquared(void) ;

    /// Initialises the residue vector to enough space for all the residues
    void InitRes (void);

    /// Collects all the parameters which can be minimised
    void CollectParams ( Model & m );



    unsigned NRes(void)   const { return res.size() ; };

    virtual void solve(void) = 0;


    void copyres (double *x) { std::copy( res.begin() , res.end(), x) ; }


  };



  

}


#endif //  __BNMIN__ALGO__MINIM_HXX
