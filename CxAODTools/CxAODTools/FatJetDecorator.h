#ifndef CxAODTools_FatJetDecorator_H
#define CxAODTools_FatJetDecorator_H

#include "ObjectDecorator.h"

enum class FatJetIntProps {
    partIndex,
    isFatJet
};
enum class FatJetFloatProps {
	JVF,
	Tau21,
	Tau32,
	Tau21_wta,
	Tau32_wta,
	D2,
	C1,
	C2,
	D2_Beta2,
	C1_Beta2,
	C2_Beta2
};

class FatJetDecorator : public ObjectDecorator<FatJetIntProps, FatJetFloatProps>
{

public:
  FatJetDecorator();
  ~FatJetDecorator() = default;

};

#endif
