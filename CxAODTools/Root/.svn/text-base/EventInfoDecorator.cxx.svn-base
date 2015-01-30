#include "CxAODTools/EventInfoDecorator.h"

template <>
EventInfoDecorator::MapIntDec ObjectDecorator<EventInfoIntProps, EventInfoFloatProps>::m_intDecs = {};

template <>
EventInfoDecorator::MapIntAcc ObjectDecorator<EventInfoIntProps, EventInfoFloatProps>::m_intAccs = {};

template <>
EventInfoDecorator::MapFloatDec ObjectDecorator<EventInfoIntProps, EventInfoFloatProps>::m_floatDecs = {};

template <>
EventInfoDecorator::MapFloatAcc ObjectDecorator<EventInfoIntProps, EventInfoFloatProps>::m_floatAccs = {};

EventInfoDecorator::EventInfoDecorator() {
  m_intPropNames = {
    {EventInfoIntProps::isMC, "isMC"},
    {EventInfoIntProps::NVtx3Trks, "NVtx3Trks"},
    {EventInfoIntProps::hasPV, "hasPV"},
    {EventInfoIntProps::passGRL, "passGRL"},
    {EventInfoIntProps::isCleanEvent, "isCleanEvent"}
  };

  m_floatPropNames = {
    {EventInfoFloatProps::MCEventWeight, "MCEventWeight"},
    {EventInfoFloatProps::ZPV, "zPV"}
  };
}

