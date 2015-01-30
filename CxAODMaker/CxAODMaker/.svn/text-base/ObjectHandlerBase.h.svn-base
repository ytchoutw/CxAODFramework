// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_ObjectHandlerBase_H
#define CxAODMaker_ObjectHandlerBase_H

#include <vector>
#include <TString.h>

// infrastucture includes
#include "EventLoop/StatusCode.h"
#include "PATInterfaces/SystematicRegistry.h"


class ObjectHandlerBase {

public:

  /**
   * @brief Destructor.
   */
  virtual ~ObjectHandlerBase() {;}

  /**
   * @brief Retrieve physics objects from event.
   * @return Status code.
   */
  virtual EL::StatusCode setObjects() = 0;

  /**
   * @brief Calibration/selection/... tools are initialized.
   * @return Status code.
   */
  virtual EL::StatusCode initializeTools() = 0;

  /**
   * @brief Add systematic variations.
   * @return Status code.
   */
  virtual EL::StatusCode addCPVariations(const std::vector<TString> &variations) = 0;

  /**
   * @brief Get the CP variations that affect this handler.
   * @return The list of CP systematics
   */
  virtual const std::vector<CP::SystematicSet>& getCPVariations() const = 0;

  /**
   * @brief Calibrate physics objects.
   * @return Status code.
   */
  virtual EL::StatusCode calibrate() = 0;

  /**
   * @brief Run selection on physics objects.
   * @return Status code.
   */
  virtual EL::StatusCode select() = 0;

  /**
   * @brief Copy selected physics objects to output container.
   * @return Status code.
   */
  virtual EL::StatusCode fillOutputContainer() = 0;

  /**
   * @brief Delete any owned objects created during the event.
   * @return Status code.
   */
  virtual EL::StatusCode clearEvent() = 0;

  /**
   * @brief validate physics objects.
   * @return Status code.
   */
  virtual EL::StatusCode counter(int mode=0) = 0;

};

#endif
