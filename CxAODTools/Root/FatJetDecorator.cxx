#include "CxAODTools/FatJetDecorator.h"

template <>
FatJetDecorator::MapIntDec ObjectDecorator<FatJetIntProps, FatJetFloatProps>::m_intDecs = {};

template <>
FatJetDecorator::MapIntAcc ObjectDecorator<FatJetIntProps, FatJetFloatProps>::m_intAccs = {};

template <>
FatJetDecorator::MapFloatDec ObjectDecorator<FatJetIntProps, FatJetFloatProps>::m_floatDecs = {};

template <>
FatJetDecorator::MapFloatAcc ObjectDecorator<FatJetIntProps, FatJetFloatProps>::m_floatAccs = {};

FatJetDecorator::FatJetDecorator() {
  m_intPropNames = {
    {FatJetIntProps::partIndex, "partIndex"},
    {FatJetIntProps::isFatJet, "isFatJet"}
  };

  m_floatPropNames = {
    {FatJetFloatProps::JVF, "jvf0"},
    {FatJetFloatProps::Tau21, "Tau21"},
    {FatJetFloatProps::Tau32, "Tau32"}
  };

}
