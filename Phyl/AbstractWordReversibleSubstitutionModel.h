 //
// File: AbstractWordReversibleSubstitutionModel.h
// Created by: Laurent Gueguen
// Created on: Jan 2009
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

#ifndef _ABSTRACTWORDREVERSIBLESUBSTITUTIONMODEL_H_
#define _ABSTRACTWORDREVERSIBLESUBSTITUTIONMODEL_H_

#include "AbstractSubstitutionModel.h"

// From Utils
#include <Utils/BppVector.h>

namespace bpp
{

/**
 * @brief Abstract Basal class for words of reversible substitution models.
 *
 * Objects of this class are built from several reversible
 * substitution models. Each model corresponds to a position in the
 * word. No model is directly accessible. </p>
 *
 * Only substitutions with one letter changed are accepted. </p>
 *
 * There is one substitution per word per unit of time
 * on the equilibrium frequency, and each position has its specific rate.
 * For example, if there are $n$ models and $\rho_i$ is the rate of
 * model i ($\Sum_{i=0}^{n-1} \rho_i = 1$):
 * @f[
 * Q_{abc \rightarrow abd} = \rho_2 Q^{(2)}_{c \rightarrow d}
 * Q_{abc \rightarrow aed} = 0
 * Q_{abc \rightarrow abc} = \rho_0 Q^{(0)}_{a \rightarrow a} + \rho_1 Q^{(1)}_{b \rightarrow b} + \rho_2 Q^{(2)}_{c \rightarrow c})
 * @f]
 *
 * The parameters of this word model are the same as the ones of the
 * models used. Their names have a new suffix, "_phi" where i stands
 * for the position (i.e. the phase) in the word.
 *
 */
  
class AbstractWordReversibleSubstitutionModel :
  public AbstractReversibleSubstitutionModel
{
private:

  /**
   *@ brief boolean flag to check if a specific WordAlphabet has been built
   */
  
  bool new_alphabet_;
  
protected:

  Vector<SubstitutionModel*> _VAbsRevMod;
  Vector<string> _VnestedPrefix;
  
  double *_rate;
  mutable RowMatrix<double> _p;
  
protected:
  void Build();

  static Alphabet* extract_alph(const Vector<SubstitutionModel*>&);

protected:

  virtual void updateMatrices();

  /**
   *@brief Called by updateMatrices to handle specific modifications
   *for inheriting classes
   */
  virtual void completeMatrices() = 0;

public:

  /**
   *@brief Build a new AbstractWordReversibleSubstitutionModel object from a
   *Vector of pointers to SubstitutionModels.
   *
   *@param modelVector the Vector of substitution models to use, in
   *   the order of the positions in the words from left to right. All
   *   the models must be different objects to avoid parameters
   *   redondancy, otherwise only the first model is used.
   */
  
  AbstractWordReversibleSubstitutionModel(const Vector<SubstitutionModel*>& modelVector,
                                          const std::string&);

  /**
   *@brief Build a new AbstractWordReversibleSubstitutionModel object from a
   *pointer to an SubstitutionModel and a number of
   *desired models.
   *
   *@param A pointer to the substitution model to use in all the positions.
   *@param The number of models involved.
   */

  AbstractWordReversibleSubstitutionModel( SubstitutionModel*, unsigned int, const std::string&);

  AbstractWordReversibleSubstitutionModel(const AbstractWordReversibleSubstitutionModel&);

  virtual ~AbstractWordReversibleSubstitutionModel();

  virtual void fireParameterChanged(const ParameterList&);

  void setNamespace(const string&);
  
protected:

  /**
   *@brief Constructor for the derived classes only
   */

  AbstractWordReversibleSubstitutionModel(const Alphabet* alph, const std::string&);
  
public:
  virtual unsigned int getNumberOfStates() const;

  virtual void setFreq(map<int, double>&);

};

} //end of namespace bpp.

#endif	//_ABSTRACTWORDREVERSIBLESUBSTITUTIONMODEL
