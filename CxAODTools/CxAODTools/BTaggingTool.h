#ifndef CxAODTools_BTaggingTool_H
#define CxAODTools_BTaggingTool_H


/**
 * Usage:
 * ====== 
 *
 * - declare tool in header:
 *   BTaggingTool m_btagtool;
 *
 * - initialize it somewhere before the event loop, e.g.:
 *   m_btagtool.initialize("MV1","0_8119","AntiKt4TopoEMJVF","testCDI.root");
 *
 * - in event loop, pass xAOD::Jets to the tool and get efficiency / scale factor through e.g.
 *   float btag_eff = btagtool.getEfficiency( *jet );
 *   float btag_sf  = btagtool.getScaleFactor( *jet );
 *   
 *   ==> returns -1 in both cases if the result shouldn't be used in further analysis
 *
 * - you can also pass a jet container and a JetDecorator to get the scale factors for all jets in it
 *   m_btagtool.getScaleFactor( jets, deco ); // "jets" is an xAOD:::JetContainer, "deco" is a JetDecorator
 *
 * - Get list of systematic variations
 *   CP::SystematicsSet syst = m_btagtool.affectingSystematics(); 
 *
 * - Apply systematic variations
 *   m_btagtool.applySystematicVariation(const CP::SystematicSet & sysSet);
 * 
 *
 * - final comment: This header should not be included in places visible to CINT. In some cases,
 *   it may therefore be better to declare a pointer to the tool and simply make a forward 
 *   declaration in order to hide this header from CINT.
 */


// Infra structure includes
// - have to include the header (instead of forward declaration of xAOD::Jet)
//   since xOAD::Jet is a typedef, i.e. not a class, hence cannot forward declare...
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"

// External tool (having only a forward declaration here makes linking fail on the grid, apparently)
#include "xAODBTaggingEfficiency/BTaggingEfficiencyTool.h"

// Forward declarations
class SystematicSet;
class JetDecorator;


class BTaggingTool {

 public:

  // constructor
  BTaggingTool();

  // destructor
  ~BTaggingTool();

  // initialize external tool
  bool initialize(const char * TaggerName, const char * OperatingPoint, const char * JetAuthor, const char * ScaleFactorFileName);

  // get efficiency and scale factors for single jet
  float getEfficiency(const xAOD::Jet & jet) const;
  void  getEfficiency(const xAOD::Jet & jet, float & eff) const { eff = getEfficiency( jet ); }
  float getScaleFactor(const xAOD::Jet & jet) const;
  void  getScaleFactor(const xAOD::Jet & jet, float & sf) const { sf = getScaleFactor( jet ); }
  
  // get scale factors for a vector of jets
  // - attaches the scale factor as a decoration to each jet
  void getScaleFactor(const xAOD::JetContainer & jets, JetDecorator & decorator) const;

  // get list of systematic variations
  CP::SystematicSet affectingSystematics() const;

  // apply systematic variation
  bool applySystematicVariation(const CP::SystematicSet & sysSet);

  // set nominal (switch off systematics)
  bool applyNominal();


 private:

  // external tool
  BTaggingEfficiencyTool * m_tool;

};

#endif
