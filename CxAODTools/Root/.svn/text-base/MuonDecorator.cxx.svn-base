#include "CxAODTools/MuonDecorator.h"

template <>
MuonDecorator::MapIntDec ObjectDecorator<MuonIntProps, MuonFloatProps>::m_intDecs = {};

template <>
MuonDecorator::MapIntAcc ObjectDecorator<MuonIntProps, MuonFloatProps>::m_intAccs = {};

template <>
MuonDecorator::MapFloatDec ObjectDecorator<MuonIntProps, MuonFloatProps>::m_floatDecs = {};

template <>
MuonDecorator::MapFloatAcc ObjectDecorator<MuonIntProps, MuonFloatProps>::m_floatAccs = {};

MuonDecorator::MuonDecorator() {
  m_intPropNames = {
    {MuonIntProps::partIndex, "partIndex"},
    {MuonIntProps::passOR, "passOR"},
    {MuonIntProps::passORGlob, "passORGlob"},
    {MuonIntProps::passedIDCuts, "passedIDCuts"},
    {MuonIntProps::isVHLooseMuon, "isVHLooseMuon"},
    {MuonIntProps::isVHSignalMuon, "isVHSignalMuon"},
    {MuonIntProps::isZHSignalMuon, "isZHSignalMuon"},
    {MuonIntProps::isWHSignalMuon, "isWHSignalMuon"}
  };

  m_floatPropNames = {
    {MuonFloatProps::z0, "z0"},
    {MuonFloatProps::d0, "d0"},
    {MuonFloatProps::effSF, "effSF"}
  };
}

