#include "CxAODTools/JetDecorator.h"

template <>
JetDecorator::MapIntDec ObjectDecorator<JetIntProps, JetFloatProps>::m_intDecs = {};

template <>
JetDecorator::MapIntAcc ObjectDecorator<JetIntProps, JetFloatProps>::m_intAccs = {};

template <>
JetDecorator::MapFloatDec ObjectDecorator<JetIntProps, JetFloatProps>::m_floatDecs = {};

template <>
JetDecorator::MapFloatAcc ObjectDecorator<JetIntProps, JetFloatProps>::m_floatAccs = {};

JetDecorator::JetDecorator() {
  m_intPropNames = {
    {JetIntProps::partIndex, "partIndex"},
    {JetIntProps::goodJet, "goodJet"},
    {JetIntProps::truthLabel, "TruthLabelID"},
    {JetIntProps::isVetoJet, "isVetoJet"},
    {JetIntProps::isSignalJet, "isSignalJet"},
    {JetIntProps::passOR, "passOR"},
    {JetIntProps::passORGlob, "passORGlob"}
  };

  m_floatPropNames = {
    //{JetFloatProps::None, "None"}
    {JetFloatProps::MV1, "MV1"},
    {JetFloatProps::SV1_IP3D,"SV1_IP3D"},
    {JetFloatProps::MV2c00,"MV2c00"},
    {JetFloatProps::MV2c10,"MV2c10"},
    {JetFloatProps::MV2c20,"MV2c20"},
    {JetFloatProps::MVb,"MVb"},
    {JetFloatProps::JVF,"jvf0"},
     {JetFloatProps::btagSF, "btagSF"}
  };
}

