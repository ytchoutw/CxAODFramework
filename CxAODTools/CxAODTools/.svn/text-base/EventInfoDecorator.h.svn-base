#ifndef CxAODTools_EventInfoDecorator_H
#define CxAODTools_EventInfoDecorator_H

#include "ObjectDecorator.h"

enum class EventInfoIntProps {
  isMC,
  NVtx3Trks,
  hasPV,
  passGRL,
  isCleanEvent
};
enum class EventInfoFloatProps {
  MCEventWeight,
  ZPV
};

class EventInfoDecorator : public ObjectDecorator<EventInfoIntProps, EventInfoFloatProps>
{

public:
  EventInfoDecorator();
  ~EventInfoDecorator() = default;

};

#endif
