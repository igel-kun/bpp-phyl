//
// File: GY94.h
// Created by: Laurent Gueguen
// Created on: July 2009
//

/*
Copyright or � or Copr. CNRS, (November 16, 2004)

This software is a computer program whose purpose is to provide classes
for phylogenetic data analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef _GY94_H_
#define _GY94_H_

#include "CodonAsynonymousFrequenciesReversibleSubstitutionModel.h"
#include <Seq/GranthamAAChemicalDistance.h>

namespace bpp
{

/**
 * @brief The Goldman  and Yang (1994) substitution model for codons.
 * @author Laurent Gu�guen
 *
 * This model has one rate of transitions and one rate of
 * transversion. It also allows distinct equilibrium frequencies
 * between codons. A multiplicative factor accounts for the selective
 * restraints at the amino acid level. This factor applies on the the
 * distance @f$d@f$ between amino acids given by Grantham (1974).
 * 
 * For codons @f$i=i_1i_2i_3@f$ and @f$j=j_1j_2j_3@f$, the generator term @f$Q_{ij} (i \neq j)@f$ is:
 * 0 if 2 or 3 of the pair @f$(i_1,j_1) (i_2,j_2) (i_3,j_3) @f$ are different.
 * @f$\mu \pi_j \exp(-d_{aa_i,aa_j}/V)@f$  if exactly 1 of the pairs
 @f$(i_1,j_1) (i_2,j_2) (i_3,j_3) @f$ is different, and that
 difference is a transversion.
 * @f$\mu \kappa \pi_j \exp(-d_{aa_i,aa_j}/V)@f$  if exactly 1 of the
 pairs @f$(i_1,j_1) (i_2,j_2) (i_3,j_3) @f$ is different, and that
 difference is a transition.
 *
 * @f$\mu@f$ is a normalization factor.
 *
 * This model includes 2 parameters (@f$\kappa@f$ and @f$V@f$). The codon
 frequencies are observed.
 *
 * Reference:
 * - Goldman N. and Yang Z. (1994), _Molecular Biology And Evolution_ 11(5) 725--736. 
 */

  
class GY94:
  public AbstractSubstitutionModel
{
private:

  GranthamAAChemicalDistance _gacd;
  
  FixedFrequenciesSet _ffs;
  CodonAsynonymousFrequenciesReversibleSubstitutionModel _pmodel;

public:
  GY94(const GeneticCode*);
       
  ~GY94();

#ifndef NO_VIRTUAL_COV
    GY94*
#else
    Clonable*
#endif
    clone() const { return new GY94(*this); }

public:

  string getName() const;
	
  inline void updateMatrices();

  const Vdouble& getFrequencies() const { return _pmodel.getFrequencies(); }
       
  const Matrix<double>& getGenerator() const { return _pmodel.getGenerator(); }
    
  const Vdouble & getEigenValues() const { return _pmodel.getEigenValues(); }
    
  const Matrix<double>& getRowLeftEigenVectors() const { return _pmodel.getRowLeftEigenVectors(); }
  
  const Matrix<double>& getColumnRightEigenVectors() const { return _pmodel.getColumnRightEigenVectors(); }
    
  double freq(unsigned int i) const { return _pmodel.freq(i); }
    
  double Qij(unsigned int i, unsigned int j) const { return _pmodel.Qij(i,j); }
    
  double Pij_t    (unsigned int i, unsigned int j, double t) const { return _pmodel.Pij_t(i, j, t); }
  double dPij_dt  (unsigned int i, unsigned int j, double t) const { return _pmodel.dPij_dt(i, j, t); }
  double d2Pij_dt2(unsigned int i, unsigned int j, double t) const { return _pmodel.d2Pij_dt2(i, j, t); }

  const Matrix<double> & getPij_t    (double d) const  {    return _pmodel.getPij_t(d);  }

  const Matrix<double> & getdPij_dt  (double d) const  {    return _pmodel.getdPij_dt(d);  }

  const Matrix<double> & getd2Pij_dt2(double d) const  {    return _pmodel.getd2Pij_dt2(d);  }

  void setFreq(map<int, double>& m)  {    _pmodel.setFreq(m);  }

  unsigned int getNumberOfStates() const  {    return _pmodel.getNumberOfStates();  }

  double getInitValue(unsigned int i, int state) const throw (BadIntException) { return _pmodel.getInitValue(i,state); }

  void enableEigenDecomposition(bool yn) { eigenDecompose_ = 1; }

  bool enableEigenDecomposition() { return _pmodel.enableEigenDecomposition(); }

};

} //end of namespace bpp.

#endif	//_GY94_H_
