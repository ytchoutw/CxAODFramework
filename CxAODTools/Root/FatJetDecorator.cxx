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
	{FatJetFloatProps::Tau32, "Tau32"},
	{FatJetFloatProps::Tau21, "Tau21_wta"},
    {FatJetFloatProps::Tau32, "Tau32_wta"},
	{FatJetFloatProps::D2, "D2"},
	{FatJetFloatProps::C1, "C1"},
	{FatJetFloatProps::C2, "C2"},
    {FatJetFloatProps::D2_Beta2, "D2_Beta2"},
	{FatJetFloatProps::C1_Beta2, "C1_Beta2"},
	{FatJetFloatProps::C2_Beta2, "C2_Beta2"}
 
  };

}
