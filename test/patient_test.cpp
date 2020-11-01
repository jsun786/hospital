/**
 * Unit tests for patient.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include <gtest/gtest.h>

#include "data/patients.h"
#include "org/hospital.h"

TEST(Patient, addProcedure) {
  PatientInfo patientInfo = {386654, true, OUTPATIENT};
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Adding "bad" procedures should return false and fail.
  EXPECT_FALSE(patient.addProcedure(ANGIOPLASTY));

  // Adding "good" procedures should return true and succeed.
  EXPECT_TRUE(patient.addProcedure(CHECKUP));
  delete &patient;
}

TEST(Patient, billing1) {
  PatientInfo patientInfo = {
      443211, true, INPATIENT, {ANGIOPLASTY, BOTOX, CHECKUP, ULTRASOUND}};
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);
  for(auto procedure : patientInfo.procedures) {
    patient.addProcedure(procedure);
  }

  // Check billing amount (20% off, $100 off for Botox).
  // Note that Checkup is not available for an inpatient, so not included
  // billing: (8000 + (2000 - 100) + 2000) * (1 - 0.2) = 9520
  EXPECT_EQ(patient.billing(), 9520);
  delete &patient;
}

TEST(Patient, billing2) {
  PatientInfo patientInfo = {
      773222, false, OUTPATIENT, {BOTOX, CHECKUP, ULTRASOUND}};
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);
  for(auto procedure : patientInfo.procedures) {
    patient.addProcedure(procedure);
  }
  // Check billing amount (no 20% off).
  // Note that Botox is not available for an outpatient
  // billing: 200 + 1500 = 1700
  EXPECT_EQ(patient.billing(), 1700);
  delete &patient;
}

TEST(Patient, liability1) {
  PatientInfo patientInfo = {
      100743,
      true,
      INPATIENT,
      {ANGIOPLASTY, BOTOX, ENDOSCOPY, STENT, ULTRASOUND}};
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);
  for(auto procedure : patientInfo.procedures) {
    patient.addProcedure(procedure);
  }

  // Check liability (50% off deductibles promo on angioplasty, stent only).
  // non-copay: (2000 - 100) * (1 - 0.2) = 1520
  // copay: 1000 * (1 - 0.5) + 500 + 500 * (1 - 0.5) + 100 = 1350
  // total = 1520 + 1350 = 2870
  EXPECT_EQ(patient.liability(), 2870);
  delete &patient;
}

TEST(Patient, liability2) {
  PatientInfo patientInfo = {
      100743, true, OUTPATIENT, {ANGIOPLASTY, EKG, ENDOSCOPY, ULTRASOUND}};
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);
  for(auto procedure : patientInfo.procedures) {
    patient.addProcedure(procedure);
  }

  // Check liability (30% all covered procedures).
  // Note that Angioplasty is not available for an outpatient
  // non-copay: 500 * (1 - 0.2) = 400
  // copay: (500 + 100) * (1 - 0.3) = 420
  // total = 820
  EXPECT_EQ(patient.liability(), 820);
  delete &patient;
}
