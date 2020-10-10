#include <gtest/gtest.h>
#include "org/hospital.h"
#include "data/patients.h"

TEST(Patient, addProcedure) {
  PatientInfo patientInfo = {
    386654, true, OUTPATIENT
  };
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Adding "bad" procedures should return false and fail.

  // Adding "good" procedures should return true and succeed.
}

TEST(Patient, billing1) {
  PatientInfo patientInfo = {
    443211, true, INPATIENT, {ANGIOPLASTY, BOTOX, CHECKUP, ULTRASOUND}
  };
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Check billing amount (20% off, $100 off for Botox).
}

TEST(Patient, billing2) {
  PatientInfo patientInfo = {
    773222, false, OUTPATIENT, {BOTOX, CHECKUP, ULTRASOUND}
  };
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Check billing amount (no 20% off).
}

TEST(Patient, liability1) {
  PatientInfo patientInfo = {
    100743, true, INPATIENT, {ANGIOPLASTY, BOTOX, ENDOSCOPY, STENT, ULTRASOUND}
  };
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Check liability (50% off deductibles promo on angioplasty, stent only).
}

TEST(Patient, liability2) {
  PatientInfo patientInfo = {
    100743, true, OUTPATIENT, {ANGIOPLASTY, EKG, ENDOSCOPY, ULTRASOUND}
  };
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Check liability (30% all covered procedures).
}
