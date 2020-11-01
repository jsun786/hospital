/**
 * Implementation of Hospital class.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "org/hospital.h"

// Return by reference a patient generated according to patientInfo
Patient& Hospital::addPatient(const PatientInfo& patientInfo) {
  if (patientInfo.kind == INPATIENT) {
    return *(new InPatient(patientInfo.patientId, patientInfo.kind,
                     patientInfo.hasInsurance));
  } else {
    return *(new OutPatient(patientInfo.patientId, patientInfo.kind,
                      patientInfo.hasInsurance));
  }
}