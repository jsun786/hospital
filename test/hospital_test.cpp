/**
 * Unit tests for hospital.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "org/hospital.h"

#include <gtest/gtest.h>

#include <typeinfo>

#include "data/patients.h"

TEST(Hospital, addPatient) {
  PatientInfo patientInfo = patientInfos(1)[0];
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Should retain info (id, hasInsurance, kind).
  EXPECT_EQ(patientInfo.patientId, patient.patientId);
  EXPECT_EQ(patientInfo.hasInsurance, patient.hasInsurance);
  EXPECT_EQ(patientInfo.kind, patient.kind);

  // Should NOT have any procedures at start.
  EXPECT_TRUE(patient.procedures.empty());

  // Should be of matching class (InPatient or OutPatient).
  if (patientInfo.kind == INPATIENT) {
    EXPECT_TRUE(typeid(patient) == typeid(InPatient));
  } else {
    if (patientInfo.kind == OUTPATIENT) {
      EXPECT_TRUE(typeid(patient) == typeid(OutPatient));
    }
  }
  delete &patient;
}
