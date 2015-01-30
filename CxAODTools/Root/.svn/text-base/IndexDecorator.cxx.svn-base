#include "CxAODTools/IndexDecorator.h"

template <>
IndexDecorator::MapIntDec ObjectDecorator<IndexIntProps, IndexFloatProps>::m_intDecs = {};

template <>
IndexDecorator::MapIntAcc ObjectDecorator<IndexIntProps, IndexFloatProps>::m_intAccs = {};

template <>
IndexDecorator::MapFloatDec ObjectDecorator<IndexIntProps, IndexFloatProps>::m_floatDecs = {};

template <>
IndexDecorator::MapFloatAcc ObjectDecorator<IndexIntProps, IndexFloatProps>::m_floatAccs = {};

IndexDecorator::IndexDecorator() {
  m_intPropNames = {
    {IndexIntProps::partIndex, "partIndex"},
  };

  m_floatPropNames = {
    {IndexFloatProps::None, "None"}
  };
}

