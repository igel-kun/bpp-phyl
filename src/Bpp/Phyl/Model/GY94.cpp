//
// File: GY94.cpp
// Created by:  Laurent Gueguen
// Created on: July 2009
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)
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

#include "GY94.h"
#include "FrequenciesSet.h"

using namespace bpp;

using namespace std;

/******************************************************************************/

GY94::GY94(const GeneticCode* gc, FrequenciesSet* codonFreqs) :
  AbstractReversibleSubstitutionModel(gc->getSourceAlphabet(), "GY94."),
  gacd_(),
  pmodel_(gc, codonFreqs, &gacd_)
{
  addParameter_(Parameter("GY94.kappa",1,&Parameter::R_PLUS_STAR));
  addParameter_(Parameter("GY94.V",10000,&Parameter::R_PLUS_STAR));
  pmodel_.setNamespace("GY94.");
  addParameters_(codonFreqs->getParameters());
  updateMatrices();
}

GY94::GY94(const GY94& gy94) :
  AbstractReversibleSubstitutionModel(gy94),
  gacd_(),
  pmodel_(gy94.pmodel_)
{}

GY94& GY94::operator=(const GY94& gy94)
{
  AbstractReversibleSubstitutionModel::operator=(gy94);
  pmodel_ = CodonAsynonymousFrequenciesReversibleSubstitutionModel(gy94.pmodel_.getGeneticCode(), gy94.pmodel_.getFreq().clone(), &gacd_);
  return *this;
}

void GY94::updateMatrices()
{
  ParameterList pl;
  pl.addParameter(Parameter("GY94.123_K80.kappa", getParameterValue("kappa")));
  pl.addParameter(Parameter("GY94.alpha", getParameterValue("V")));
  pmodel_.matchParametersValues(pl);
}

void GY94::setFreq(std::map<int, double>& m)
{
  pmodel_.setFreq(m);
  matchParametersValues(pmodel_.getParameters());
}