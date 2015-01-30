#ifndef CxAODTools_MuonDecorator_H
#define CxAODTools_MuonDecorator_H

#include "ObjectDecorator.h"

enum class MuonIntProps {
  partIndex,
  passOR,
  passORGlob,
  passedIDCuts,
  isVHLooseMuon,
  isVHSignalMuon,
  isZHSignalMuon,
  isWHSignalMuon
};
enum class MuonFloatProps {
  z0,
  d0,
  effSF
};

class MuonDecorator : public ObjectDecorator<MuonIntProps, MuonFloatProps>
{

public:
  MuonDecorator();
  ~MuonDecorator() = default;

};

#endif
