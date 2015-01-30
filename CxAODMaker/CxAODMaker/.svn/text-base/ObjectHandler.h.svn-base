// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_ObjectHandler_H
#define CxAODMaker_ObjectHandler_H

// Analysis includes
#include "CxAODMaker/ObjectHandlerBase.h"
#include "CxAODTools/ConfigStore.h"
#include "CxAODTools/IndexDecorator.h"
#include "CxAODMaker/EventInfoHandler.h"

// ROOT includes
#include "TString.h"

// infrastructure includes
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/ISystematicsTool.h"
#include "EventLoop/StatusCode.h"
// (and those which rootcint doesn't like)


#ifndef __MAKECINT__

#ifndef XAODMUON_ELECTRONCONTAINER_H
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronAuxContainer.h"
#endif

#ifndef XAODMUON_JETCONTAINER_H
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#endif

#ifndef XAODMUON_MUONCONTAINER_H
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonAuxContainer.h"
#endif

#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/ShallowCopy.h"
#include "xAODBase/IParticleHelpers.h"

namespace ObjectHandler_Helper {
  xAOD::TStore createTStore();
}

#endif // not __MAKECINT__


template <class partType, class partContainer>
class ObjectHandler : public ObjectHandlerBase {

protected:

  /// Name of the handler
  std::string m_handlerName;

  // steering file
  ConfigStore & m_config;

  // event info
  EventInfoHandler & m_eventInfoHandler;//!

  // xAOD event
  xAOD::TEvent * m_event;

  // xAOD event info
  #ifndef __MAKECINT__
  xAOD::TStore m_TStore;
  #endif // not __MAKECINT__

  //
  std::string m_containerName;

  // decorator
  IndexDecorator m_indexDecorator;

  // flag to create element links
  bool m_createElementLinks;

  // flag to store original (non-calibrated) objects
  bool m_storeOrig;
  // flag to store whether this particular Handler is used for OR
  bool m_usedInOR;

  // maps of < variation name, xAOD container >
  // shallow copies of input xAOD objects for calibration
  std::map<TString, partContainer *> m_inContainer;
  // selected objects for output xAOD and event processing
  std::map<TString, partContainer *> m_outContainer;

  // list of CP tool, which are affected by systematics
  std::vector<CP::ISystematicsTool *> m_sysToolList;

  // list of CP systematics
  std::vector<CP::SystematicSet> m_sysList;

  // counters
  std::map<TString, int> m_countCont;

  /**
   * @brief Set 4-vector
   * @param input particle.
   * @param output particle.
   *
   * For unkown reasons, this is not a member of xAOD::IParticle (?!),
   * so we make an interface for it!
   */
  virtual void setP4(const partType * inPart, partType * outPart) = 0;

  /**
   * @brief Print 4-vector information of object particle to screen.
   * @param particle.
   */
  void printParticle(partType * particle);

  /**
   * @brief decorate object
   * @param particles Physics object
   * @return Status code.
   */
  virtual EL::StatusCode decorate(partType * particle) = 0;

  /**
   * @calibrate Calibrate physics objects.
   * @param particles Physics objects
   * @param sysSet Systematic variation(s).
   * @return Status code.
   */
  virtual EL::StatusCode calibrateCopies(partContainer * particles, const CP::SystematicSet & sysSet) = 0;

  /**
   * @brief Select one physics object for any systematic variation.
   * @param partContList All objects for all systematic variations.
   * @param index Index of object for selection.
   * @param passFunction Pointer to static selection function.
   * @return Decision.
   *
   * An iteration on all object containers is performed. For each
   * container the passFunction is called for the object at index.
   */
  bool passAny(std::map<TString, partContainer *> partContList,
	       int index,
	       bool (*passFunction)(partType *));
  /**
   * @brief Copy input objects to output container.
   * @param partContList All objects for all systematic variations.
   * @param outPartCont Output container for systematic variations sysName.
   * @param sysName Systematic variation.
   * @param checkSel Pointer to static selection function.
   *
   * The physics object container for variation sysName
   * is retrieved from partContList and copied to outPartCont.
   *
   * For the nominal objects a new container outPartCont is created.
   * All objects from partContList, that passed
   * for any of the variations the selection, are added.
   * The objects are decorated with non-standard variables.
   *
   * For systematic variations shallow copies are created
   * on the nominal outPartCont container.
   * Variation dependent object variables are overwritten.
   */
  void copyContainer(std::map<TString, partContainer *> partContList,
		     partContainer * outPartCont,
		     TString sysName,
		     bool (*checkSel)(partType *));

  /**
   * @brief Sets the variables that are written to the output container.
   * @param inPart Object from which the variables are read.
   * @param outPart Object that is written to output container, for which variables are set.
   * @param isSysVar Bool setting if the values are systematically varied.
   * @return StatusCode.
   *
   * This function is called in copyContainer and needs to be implemented
   * in the derived classes.
   *
   * For a nominal object the variables that should be written to the output are defined
   * and set.
   * Variation dependent object variables are overwritten.
   */
  virtual EL::StatusCode setVariables(partType * inPart, partType * outPart, bool isSysVar) = 0;

  /**
   * @brief Copy selected physics objects to output container.
   * @return Status code.
   *
   * Selected objects from m_inContainer are copied to m_outContainer.
   * A loop over all variations is done and the copying
   * is performed by @c copyContainer().
   *
   * A preceding call @c select() is required.
   */
  EL::StatusCode fillOutputContainerCheck(bool (*checkSel)(partType *));

  /**
   * @brief Get physics objects from given container.
   * @return Map of all objects for the requested variation.
   *
   * If the variation is not found, "Nominal" is returned.
   * If "Nominal" doesn't exist either, nullptr is returned.
   *
   * The objects are calibrated if @c calibrate() was called.
   * They are decorated with selection flags if select() was called.
   *
   * A preceding call @c setObjects() is required.
   */
  partContainer* getParticleVariation(
          std::map<TString, partContainer *> &container,
          const TString &variation);

public:

  /**
   * @brief Constructor.
   * @param config Steering configuration.
   * @param event For retrieving xAOD objects.
   */
  ObjectHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                EventInfoHandler & eventInfoHandler);

  /**
   * @brief Destructor.
   */
  virtual ~ObjectHandler();

  /**
   * @brief Retrieve physics objects from event.
   * @return Status code.
   *
   * m_inMouns and m_outContainer are cleared.
   *
   * A shallow copy for each variation (nominal + systematics)
   * is created and stored in m_inContainer.
   *
   * A call preceding @c addCPVariations() is required for
   * systematics, the "Nominal" collections exists always.
   */
    EL::StatusCode setObjects();

  /**
   * @brief Calibration/selection/... tools are initialized.
   * @return Status code.
   *
   * Calibration tools are initialized and their list
   * of systematics is retrieved.
   */
  virtual EL::StatusCode initializeTools() = 0;

  /**
   * @brief Add systematic variations.
   * @return Status code.
   *
   * Those systematic variations that affect the registered CP tools
   * are added to the internal list.
   *
   * A preceding call @c initializeTools() is required.
   */
  EL::StatusCode addCPVariations(const std::vector<TString> &variations);

  /**
   * @brief Get the CP variations that affect this handler.
   * @return The list of CP systematics
   */
  const std::vector<CP::SystematicSet>& getCPVariations() const { return m_sysList; }

  /**
   * @brief Calibrate physics objects.
   * @return Status code.
   *
   * The shallow copies in m_inContainer are calibrated for
   * each variation.
   *
   * A preceding call @c setObjects() is required.
   */
  EL::StatusCode calibrate();

  /**
   * @brief Run selection on physics objects.
   * @return Status code.
   *
   * A selection is performed on for each physics object and
   * all variations in m_inContainer.
   * The result is stored as decorators for each object.
   *
   * A preceding call @c setObjects() is required.
   */
  virtual EL::StatusCode select() = 0;

  /**
   * @brief Get input physics objects.
   * @return Map of all objects for all variations.
   *
   * The objects are calibrated if @c calibrate() was called.
   * They are decorated with selection flags if select() was called.
   *
   * A preceding call @c setObjects() is required.
   */
  std::map<TString, partContainer*>* getInParticles() {
    return &m_inContainer;
  }

  /**
   * @brief Get output physics objects.
   * @return Map of selected objects for all variations.
   *
   * The objects are calibrated if @c calibrate() was called.
   * They are decorated with selection flags.
   *
   * A preceding call @c fillOutputContainer() is required.
   */
  std::map<TString, partContainer*>* getOutParticles() { return &m_outContainer; }

  /**
   * @brief Get input physics objects.
   * @return All objects for the requested variation.
   *
   * See getParticleVariation() for behaviour.
   */
  partContainer* getInParticleVariation(const TString &variation) {
    return getParticleVariation(m_inContainer, variation);
  }

  /**
   * @brief Copy selected physics objects to output container.
   * @return Status code.
   *
   * Selected objects from m_inContainer are copied to m_outContainer.
   * Please see @c fillOutputContainerCheck() for details.
   *
   * A preceding call @c select() is required.
   */
  virtual EL::StatusCode fillOutputContainer() = 0;

  /**
   * @brief Delete any owned objects created during the event.
   * @return Status code.
   */
  virtual EL::StatusCode clearEvent() = 0;


  /**
   * @brief count size of physics objects.
   * @return Status code.
   *
   * count the size of the input/output containers
   *
   * mode =0/1 fill/print
   */
  EL::StatusCode counter(int mode=0);

  /**
   * @brief Declare that this handler is used for OR
   *
   * The flag can be used to make decision on what objects should be written
   * in the output
   *
   * @param use	Whether the handler is used or not
   * @return Status code
   */
  EL::StatusCode useForOR(bool use) {
    m_usedInOR = use;
    return EL::StatusCode::SUCCESS;
  }


};


 //=============================================================================
 // Define the implementation of the methods here in the header file.
 // This is done since we are dealing with a templated base class!
 //=============================================================================

#include "CxAODMaker/ObjectHandler.icc"

#endif
