// Bojan Nikolic
// $Id: minim.hxx,v 1.3 2005/08/21 02:42:03 bnikolic Exp $
#ifndef __BNMIN__ALGO__MINIM_HXX
#define __BNMIN__ALGO__MINIM_HXX

#include <string>
#include <vector>


#include "paramctr.hxx"
#include "minimmodel.hxx"

namespace Minim {

  // Forward declarations
  class Monitor;

  
  /*!
   * This class can hold the model description but can not do the
   * actuall minimisation as it does not demand that the model has a
   * figure-of-merit function.
   */
  class ModelDesc {
    
  protected :
    
    Model & mod;

  public:

    std::vector <DParamCtr> pars ;
    
    ModelDesc( Model &mod );

    // Routines to access the model parameters
    DParamCtr * operator[] (std::string name);
    DParamCtr * getbyname  (std::string name) { return this->operator[](name);};

    // Routines to access the model parameters by id number
    DParamCtr * operator[] (unsigned i) { return &pars[i]; }
    DParamCtr * getbynumb  (unsigned i) {  return this->operator[](i); };

    /*! Returns the total number of params, both fitted and not
     *  fitted */
    unsigned NTotParam(void) const { return pars.size() ; }

    /*! Copies the parameter values from the supplied ModelDesc */
    void CopyParsFrom ( ModelDesc & mod2 );

  };


  class Minimiser : public ModelDesc {

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



    /// Returns the number of parameters to be fitted, i.e. excluding
    /// those with do fit set to false
    unsigned NParam(void) const;

    unsigned NRes(void)   const { return res.size() ; };

    virtual void solve(void) = 0;

    /// Copies values from the supplied array to the pars vector
    void copytopars(double *x) ;
    /// Copies values from vector pars to the supplied double array
    void copyfrompars(double *x) ;

    void copyres (double *x) { std::copy( res.begin() , res.end(), x) ; }


  };



  

}


#endif //  __BNMIN__ALGO__MINIM_HXX
