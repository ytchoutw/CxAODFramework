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
    Tau32
};

class FatJetDecorator : public ObjectDecorator<FatJetIntProps, FatJetFloatProps>
{

public:
  FatJetDecorator();
  ~FatJetDecorator() = default;

};

#endif
