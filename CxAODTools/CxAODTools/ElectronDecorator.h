#ifndef CxAODTools_ElectronDecorator_H
#define CxAODTools_ElectronDecorator_H

#include "ObjectDecorator.h"

enum class ElecIntProps {
  // common stuff
  partIndex,
  passOR,
  passORGlob,
  // e-gamma ID
  isVeryLooseLH,
  isVeryTightLH,
  isTightPP,
  // analysis quality assignment
  isVHLooseElectron,
  isVHSignalElectron,
  isZHSignalElectron,
  isWHSignalElectron
};

enum class ElecFloatProps { IDEff, IDEffSys };

class ElectronDecorator : public ObjectDecorator<ElecIntProps, ElecFloatProps>
{

public:
  ElectronDecorator();
  ~ElectronDecorator() = default;

};

#endif
