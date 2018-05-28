#ifndef SURFACE_PROPERTIES_H
#define SURFACE_PROPERTIES_H

#include "DataSurfaceProperties.h"

namespace Mutation {
    namespace GasSurfaceInteraction {

class SurfaceProperties{

public:
	/**
	 *
	 */
    typedef const DataSurfaceProperties& ARGS;

	/// Returns name of this type.
	static std::string typeName() { return "SurfaceProperties"; }

    /**
     *
     */
    SurfaceProperties(ARGS args){ }

    /**
     *
     */
    virtual ~SurfaceProperties(){ }

public:
    // Finite Rate Chemistry Data
//    const FRCSurfaceProperties& getFrcData(){ return NULL; }

    virtual int globalSpeciesIndex(const std::string& str_sp) const { return -1; };
    virtual size_t nWallSpecies() const { return 0; }
    virtual size_t nSiteCategories() const { return 0; }
    virtual double nTotalSites() const { return 0.; }
    virtual int globalIdxtoGasIdx(const size_t& id_sp_global) const {return -1;}

    virtual int globalSurfaceCompositionSpeciesIndex(const std::string& str_sp) const { return -1; };

    virtual double fracSite(const int& i_site) const { return 0.; }
    virtual int nSpeciesinSite(const int& i_site) const { return 0; };

    // Su
    virtual bool surfaceConstraint() const {return false;}
    virtual std::string surfaceSpecies() const {return "";}
    virtual double BprimePyro() const {return 0;}
    virtual void getSurfaceCompositions(
                                     Eigen::VectorXd & lv_pyrolisysComposition, 
                                     Eigen::VectorXd & lv_charComposition) const {}

}; // class SurfaceProperties

    } // namespace GasSurfaceInteraction 
} // namespace Mutation

#endif // SURFACE_PROPERTIES_H
