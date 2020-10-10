/**
 * Generate test patient data.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#ifndef DATA_PATIENTS_H_
#define DATA_PATIENTS_H_

#include <vector>
#include <map>

enum PatientKind {
  INPATIENT, OUTPATIENT
};

enum ProcedureKind {
  ANGIOPLASTY, BOTOX, CHECKUP, EKG, ENDOSCOPY, STENT, ULTRASOUND
};

struct PatientInfo {
  int patientId;
  bool hasInsurance;
  PatientKind kind;
  std::vector<ProcedureKind> procedures;
};

struct Procedure {
  double cost;
  bool covered;
  double copay;
};

extern std::map<PatientKind, std::map<ProcedureKind, Procedure>> PROCEDURES;

std::vector<PatientInfo> patientInfos(int);

#endif  // DATA_PATIENTS_H_
