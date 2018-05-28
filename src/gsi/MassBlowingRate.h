#ifndef MASS_BLOWING_RATE_H
#define MASS_BLOWING_RATE_H

#include "Utilities.h"

#include "DataMassBlowingRate.h"

namespace Mutation {
    namespace GasSurfaceInteraction {

/**
 * Abstract class which returns the mass blowing rate for a heterogeneous
 * reactions. It is the base of a Null object (not used yet) which returns
 * zero blow flux. This is imporatnt for the case of purely catalytic or
 * oxydation reactions. In the case where ablative reactions take place,
 * a solid class ablation is available.
 */

class MassBlowingRate
{
public:
	/**
	 * Required for self registering different type of mass blowing rate.
	 */
    typedef const DataMassBlowingRate& ARGS;

	/// Returns name of this type.
	static std::string typeName() { return "MassBlowingRate"; }

    /**
     * Destructor
     */
    virtual ~MassBlowingRate(){ }

    /**
     * Purely virtual function which return the blowing flux in kg/m^2-s.
     */
    virtual double computeBlowingFlux() = 0;

    virtual void getEquilibriumParameters(
        double elementalMassDiff,
        double elementalCharMassFraction,
        double elementalGasMassFraction)
    {
        std::cerr << "setEquilibriumParameters can only be called for surfaces "
                  << "in equilibrium." << std::endl;
        exit(1);
    };

}; // class MassBlowingRate


    } // namespace GasSurfaceInteraction
} // namespace Mutation

#endif // MASS_BLOWING_RATE_H
