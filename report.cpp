/**
 * Integration test.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#include <cstdio>
#include <map>

#include "data/patients.h"
#include "org/hospital.h"
#include "org/patient.h"

int main() {
  Hospital hospital;
  std::vector<PatientInfo> infos = patientInfos(100);
  std::vector<Patient*> patients;

  // Add each patient (and their procdures) one/one, saving the patient list.
  for (auto info : infos) {
    Patient& patient = hospital.addPatient(info);
    for (auto procedure : info.procedures) {
      patient.addProcedure(procedure);
    }
    patients.push_back(&patient);
  }

  // Print report of id, insurance, kind, billing, and liability as table.
  printf(
      "------------------------------------------------------------------------"
      "-\n");
  printf(
      "Patient ID       Insured       Patient Kind       Billing       "
      "Liability\n");
  printf(
      "------------------------------------------------------------------------"
      "-\n");
  for (auto patientPtr : patients) {
    printf("%-17d%-14s%-19s$%-13.2lf$%.2lf\n", patientPtr->patientId,
           patientPtr->hasInsurance ? "Yes" : "No",
           patientPtr->kind == INPATIENT ? "Inpatient" : "Outpatient",
           patientPtr->billing(), patientPtr->liability());
  }
  printf(
      "------------------------------------------------------------------------"
      "-\n");

  // Release memory
  for (auto patientPtr : patients) {
    delete patientPtr;
  }
  patients.clear();
}
