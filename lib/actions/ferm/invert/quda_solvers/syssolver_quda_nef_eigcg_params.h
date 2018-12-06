#ifndef __SYSSOLVER_QUDA_CLOVER_MDWF_EIGCG_PARAMS_H__
#define __SYSSOLVER_QUDA_CLOVER_MDWF_EIGCG_PARAMS_H__

#include "chromabase.h"
#include "io/xml_group_reader.h"

#include "actions/ferm/fermacts/nef_fermact_params_w.h"
#include "actions/ferm/invert/quda_solvers/enum_quda_io.h"
#include <string>
#include "handle.h"

namespace Chroma 
{
  struct SysSolverQUDANEFEIGCGParams { 
    SysSolverQUDANEFEIGCGParams(XMLReader& xml, const std::string& path);
    SysSolverQUDANEFEIGCGParams() {
      solverType=CG;
      cudaPrecision=DEFAULT;
      cudaReconstruct=RECONS_12;
      cudaSloppyPrecision=DEFAULT;
      cudaSloppyReconstruct=RECONS_12;
      asymmetricP = false; //< Use asymmetric version of the linear operator
      axialGaugeP = false; //< Fix Axial Gauge?
      SilentFailP = false; //< If set to true ignore lack of convergence. Default is 'loud' 
      RsdToleranceFactor = Real(10); //< Tolerate if the solution achived is better (less) than rsdToleranceFactor*RsdTarget
      tuneDslashP = false ; //< v0.3 autotune feature
      verboseP = false;
      innerParamsP = false;
      backup_invP = false;
      dump_on_failP = false;
      cgnrP=false;
      Pipeline=0;
    };

    SysSolverQUDANEFEIGCGParams( const SysSolverQUDANEFEIGCGParams& p) {
      NEFParams = p.NEFParams;
      AntiPeriodicT = p.AntiPeriodicT;
      MaxIter = p.MaxIter;
      RsdTarget = p.RsdTarget;
      Delta = p.Delta;
      solverType = p.solverType;
      verboseP = p.verboseP;
      asymmetricP = p.asymmetricP;
      cudaPrecision = p.cudaPrecision;
      cudaReconstruct = p.cudaReconstruct;
      cudaSloppyPrecision = p.cudaSloppyPrecision;
      cudaSloppyReconstruct = p.cudaSloppyReconstruct;
      axialGaugeP = p.axialGaugeP;
      SilentFailP = p.SilentFailP;
      RsdToleranceFactor = p.RsdToleranceFactor;
      tuneDslashP = p.tuneDslashP;
      innerParamsP = p.innerParamsP;
      backup_invP = p.backup_invP;
      backup_inv_param = p.backup_inv_param;
      dump_on_failP = p.dump_on_failP;
      cgnrP= p.cgnrP;
      Pipeline = p.Pipeline;
    }

   
    NEFFermActParams NEFParams;
    bool AntiPeriodicT;
    int MaxIter;
    Real RsdTarget;
    Real Delta;
    QudaSolverType solverType;
    bool verboseP;
    bool asymmetricP;
    QudaPrecisionType cudaPrecision;
    QudaReconsType cudaReconstruct;
    QudaPrecisionType cudaSloppyPrecision;
    QudaReconsType cudaSloppyReconstruct;
    bool axialGaugeP;
    bool SilentFailP;
    Real RsdToleranceFactor;
    bool tuneDslashP;
    bool innerParamsP;
    
    //Deflation params, split into a few groups below:
    int nev;
    int max_search_dim;
    int deflation_grid;
    double tol_restart;

    int eigcg_max_restarts;
    int max_restart_num;
    double inc_tol;
    double eigenval_tol;

    QudaExtLibType   solver_ext_lib;
    QudaExtLibType   deflation_ext_lib;
    QudaFieldLocation location_ritz;
    QudaMemoryType    mem_type_ritz;
	
    // XML for Backup Solver
    bool backup_invP;
    GroupXML_t backup_inv_param;
    bool dump_on_failP;
    bool cgnrP;    
    int Pipeline;

  };

  void read(XMLReader& xml, const std::string& path, SysSolverQUDANEFEIGCGParams& p);

  void write(XMLWriter& xml, const std::string& path, 
	     const SysSolverQUDANEFEIGCGParams& param);



}

#endif


