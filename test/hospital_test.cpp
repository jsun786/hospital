#include <gtest/gtest.h>
#include "org/hospital.h"
#include "data/patients.h"

TEST(Hospital, addPatient) {
  PatientInfo patientInfo = patientInfos(1)[0];
  Hospital hospital;
  Patient &patient = hospital.addPatient(patientInfo);

  // Should retain info (id, hasInsurance, kind).

  // Should NOT have any procedures at start.

  // Should be of matching class (InPatient or OutPatient).
}
