#include "CxAODTools/TruthDecorator.h"

template <>
TruthDecorator::MapIntDec ObjectDecorator<TruthIntProps, TruthFloatProps>::m_intDecs = {};

template <>
TruthDecorator::MapIntAcc ObjectDecorator<TruthIntProps, TruthFloatProps>::m_intAccs = {};

template <>
TruthDecorator::MapFloatDec ObjectDecorator<TruthIntProps, TruthFloatProps>::m_floatDecs = {};

template <>
TruthDecorator::MapFloatAcc ObjectDecorator<TruthIntProps, TruthFloatProps>::m_floatAccs = {};

TruthDecorator::TruthDecorator() {
  m_intPropNames = {
    {TruthIntProps::none, "none"},
  };

  m_floatPropNames = {
    {TruthFloatProps::zPV, "zPV"}
  };
}

