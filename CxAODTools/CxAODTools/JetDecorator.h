#ifndef CxAODTools_JetDecorator_H
#define CxAODTools_JetDecorator_H

#include "ObjectDecorator.h"

enum class JetIntProps {
  partIndex,
  goodJet,
  truthLabel,
  isVetoJet,
  isSignalJet,
  passOR,
    passORGlob
};

enum class JetFloatProps { 
  MV1,
    SV1_IP3D,
    MV2c00,
    MV2c10,
    MV2c20,
    MVb,
    JVF,
    btagSF
 };


class JetDecorator : public ObjectDecorator<JetIntProps, JetFloatProps>
{

public:
  JetDecorator();
  ~JetDecorator() = default;

};

#endif
