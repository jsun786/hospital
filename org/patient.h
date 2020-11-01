/**
 * Patient declarations.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#ifndef ORG_PATIENT_H_
#define ORG_PATIENT_H_

#include <algorithm>
#include <vector>

#include "data/patients.h"

#define HAS(v, i) (std::find(v.begin(), v.end(), i) != v.end())

class Patient {
 public:
  const int patientId;
  const PatientKind kind;
  const bool hasInsurance;
  std::vector<ProcedureKind> procedures;
  Patient(int, PatientKind, bool);
  bool addProcedure(const ProcedureKind procedure);
  double billing();
  virtual double liability() = 0;
  virtual ~Patient() = default;  // Added to address the warning when deleting
};

class InPatient : public Patient {
 public:
  InPatient(int, PatientKind, bool);
  double liability();
};

class OutPatient : public Patient {
 public:
  OutPatient(int, PatientKind, bool);
  double liability();
};

#endif  // ORG_PATIENT_H_
