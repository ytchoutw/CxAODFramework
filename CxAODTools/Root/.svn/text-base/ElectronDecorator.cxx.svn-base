
#include "CxAODTools/ElectronDecorator.h"

template <>
ElectronDecorator::MapIntDec ObjectDecorator<ElecIntProps, ElecFloatProps>::m_intDecs = {};

template <>
ElectronDecorator::MapIntAcc ObjectDecorator<ElecIntProps, ElecFloatProps>::m_intAccs = {};

template <>
ElectronDecorator::MapFloatDec ObjectDecorator<ElecIntProps, ElecFloatProps>::m_floatDecs = {};

template <>
ElectronDecorator::MapFloatAcc ObjectDecorator<ElecIntProps, ElecFloatProps>::m_floatAccs = {};

ElectronDecorator::ElectronDecorator() {
  m_intPropNames = {
    {ElecIntProps::partIndex, "partIndex"},
    {ElecIntProps::passOR, "passOR"},
    {ElecIntProps::passORGlob, "passORGlob"},
    {ElecIntProps::isVeryLooseLH, "isVeryLooseLH"}, {ElecIntProps::isVeryTightLH, "isVeryTightLH"},
    {ElecIntProps::isTightPP, "isTightPP"},
    {ElecIntProps::isVHLooseElectron, "isVHLooseElectron"},     {ElecIntProps::isVHSignalElectron, "isVHSignalElectron"},
    {ElecIntProps::isZHSignalElectron, "isZHSignalElectron"}, {ElecIntProps::isWHSignalElectron, "isWHSignalElectron"}
  };

  m_floatPropNames = {
    {ElecFloatProps::IDEff, "IDEff"}, {ElecFloatProps::IDEffSys, "IDEffSys"}
  };
}

