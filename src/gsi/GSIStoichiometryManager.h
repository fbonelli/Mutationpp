#ifndef GSI_STOICHIOMETRY_MANAGER_H
#define GSI_STOICHIOMETRY_MANAGER_H

#include <eigen3/Eigen/Dense>
#include <vector>

namespace Mutation {
    namespace GasSurfaceInteraction {

//=======================================================================================

template <int N>
class Stoich
{
public:

    Stoich(){
        m_rxn = 0;
        for (int i = 0; i < N; ++i) m_sps[i] = 0;
    }

    inline void multReaction( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r) const {
        for (int i = 0; i < N; ++i) p_r(m_rxn) *= p_s(m_sps[i]);
    }
    inline void incrReaction( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r) const {
        for (int i = 0; i < N; ++i) p_r(m_rxn) += p_s(m_sps[i]);
    }
    inline void decrReaction( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r) const {
        for (int i = 0; i < N; ++i) p_r(m_rxn) -= p_s(m_sps[i]);
    }
    inline void incrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s) const {
        for (int i = 0; i < N; ++i) p_s(m_sps[i]) += p_r(m_rxn);
    }
    inline void decrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s) const {
        for (int i = 0; i < N; ++i) p_s(m_sps[i]) -= p_r(m_rxn);
    }

protected:

    size_t m_rxn;
    size_t m_sps[N];

}; //class Stoich<N>

//=======================================================================================

class Stoich1 : public Stoich<1> {
public:
    Stoich1(size_t rxn, size_t sp1) {
        m_rxn = rxn; m_sps[0] = sp1;
    }
};

//=======================================================================================

class Stoich2 : public Stoich<2> {
public:
    Stoich2(size_t rxn, size_t sp1, size_t sp2) {
        m_rxn = rxn;
        if (sp1 <= sp2) {
            m_sps[0] = sp1; m_sps[1] = sp2;
        } else {
            m_sps[0] = sp2; m_sps[1] = sp1;
        }
    }
};

//=======================================================================================

class Stoich3 : public Stoich<3>
{
public:
    Stoich3(size_t rxn, size_t sp1, size_t sp2, size_t sp3) {
        m_rxn = rxn;
        if (sp1 <= sp2) {
            m_sps[0] = sp1; m_sps[1] = sp2;
        } else {
            m_sps[0] = sp2; m_sps[1] = sp1;
        }

        if (m_sps[1] <= sp3) m_sps[2] = sp3;
        else {
            if (sp3 <= m_sps[0]) {
                m_sps[2] = m_sps[1]; m_sps[1] = m_sps[0]; m_sps[0] = sp3;
            } else {
                m_sps[2] = m_sps[1]; m_sps[1] = sp3;
            }
        }
    }
};


//=======================================================================================

/**
 * Provides sparse-matrix type operations for quantities that depend on reaction
 * stoichiometries.
 */
class GSIStoichiometryManager{
public:
    GSIStoichiometryManager( ){ }

    void addReaction( const int rxn, const std::vector<int>& sps );
    virtual void multReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    virtual void incrReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    virtual void decrReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    virtual void incrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const;
    virtual void decrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const;
    virtual void incrSpeciesSurf( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const {}
    virtual void decrSpeciesSurf( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const {}

    virtual ~GSIStoichiometryManager(){ }

private:
    std::vector<Stoich1> m_stoich1_vec;
    std::vector<Stoich2> m_stoich2_vec;
    std::vector<Stoich3> m_stoich3_vec;

};

//=======================================================================================

class GSIStoichiometryManagerFRC : public GSIStoichiometryManager {
public:
    void multReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    void incrReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    void decrReactions( const Eigen::VectorXd& p_s, Eigen::VectorXd& p_r ) const;
    void incrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const;
    void decrSpecies( const Eigen::VectorXd& p_r, Eigen::VectorXd& p_s ) const;

private:
    std::vector<Stoich1> m_stoich1_vec;
    std::vector<Stoich2> m_stoich2_vec;
    std::vector<Stoich3> m_stoich3_vec;

};

//=======================================================================================

    }// namespace GasSurfaceInteraction
} // namespace Mutation

#endif // GSI_STOICHIOMETRY_MANAGER_H
