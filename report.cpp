/**
 * Integration test.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#include <cstdio>
#include <map>
#include "org/hospital.h"
#include "org/patient.h"
#include "data/patients.h"

int main() {
  Hospital hospital;
  std::vector<PatientInfo> infos = patientInfos(100);
  std::vector<Patient *> patients;

  // Add each patient (and their procdures) one/one, saving the patient list.

  // Print report of id, insurance, kind, billing, and liability as table.
}
