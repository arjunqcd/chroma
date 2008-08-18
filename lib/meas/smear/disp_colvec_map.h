// -*- C++ -*-
// $Id: disp_colvec_map.h,v 1.1 2008-08-06 15:19:41 edwards Exp $
/*! \file
 * \brief Holds displaced color vectors
 */

#ifndef __disp_colvec_map_h__
#define __disp_colvec_map_h__

#include "chromabase.h"
#include <map>

namespace Chroma 
{ 
  /*!
   * \ingroup smear
   *
   * @{
   */
  //----------------------------------------------------------------------------
  //! The key for displaced color vectors
  struct KeyDispColorVector_t
  {
    int  colvec;                  /*!< Colorvector index */
    multi1d<int> displacement;    /*!< Orig plus/minus 1-based directional displacements */
  };


  //! Support for the keys of smeared and displaced color vectors
  bool operator<(const KeyDispColorVector_t& a, const KeyDispColorVector_t& b);


  //! The value of the map
  struct ValDispColorVector_t
  {
    LatticeColorVector vec;
  };


  //----------------------------------------------------------------------------
  //! The displaced objects
  class DispColorVectorMap
  {
  public:
    //! Constructor for displaced map 
    DispColorVectorMap(int disp_length,
		       const multi1d<LatticeColorMatrix>& u_smr,
		       const multi1d<LatticeColorVector>& eigen_source);

    //! Destructor
    ~DispColorVectorMap() {}

    //! Accessor
    const LatticeColorVector& getDispVector(const KeyDispColorVector_t& key);

  protected:
    //! Displace an object
    const LatticeColorVector& displaceObject(const KeyDispColorVector_t& key);
			
  private:
    //! Lattice color vectors
    const multi1d<LatticeColorVector>& eigen_source;

    //! Gauge field 
    const multi1d<LatticeColorMatrix>& u;
			
    //! Displacement length
    int displacement_length;
			
    //! Maps of displaced color vectors 
    map<KeyDispColorVector_t, ValDispColorVector_t> disp_src_map;
  };

  /*! @} */  // end of group smear

} // namespace Chroma

#endif