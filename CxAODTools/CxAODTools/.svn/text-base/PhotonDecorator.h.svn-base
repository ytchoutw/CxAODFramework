#ifndef CxAODTools_PhotonDecorator_H
#define CxAODTools_PhotonDecorator_H

#include "ObjectDecorator.h"

enum class PhotIntProps {
  // common stuff
  partIndex,
    passOR,
    passORGlob,
  // e-gamma ID
  //TODO: check these for photons
  //isVeryLooseLH,
  //isVeryTightLH,
  //isTightPP,
    isTightIso,
  // analysis quality assignment
    isVBFALoosePhoton,
    isVBFASignalPhoton,
};

enum class PhotFloatProps { IDEff, IDEffSys };

class PhotonDecorator : public ObjectDecorator<PhotIntProps, PhotFloatProps>
{

public:
  PhotonDecorator();
  ~PhotonDecorator() = default;

};

#endif
