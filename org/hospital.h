/**
 * Hospital declarations.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#ifndef ORG_HOSPITAL_H_
#define ORG_HOSPITAL_H_

#include "data/patients.h"
#include "org/patient.h"

class Hospital {
 public:
  Patient &addPatient(const PatientInfo &);
};

#endif  // ORG_HOSPITAL_H_
