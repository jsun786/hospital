/**
 * Generate test patient data.
 *
 * Copyright (c) 2019, Sekhar Ravinutala.
 */

#include <cstdlib>
#include "data/patients.h"

std::map<PatientKind, std::map<ProcedureKind, Procedure>> PROCEDURES = {
  {
    INPATIENT, {
      {ANGIOPLASTY, {8000, true, 1000}},
      {BOTOX, {2000, false}},
      {ENDOSCOPY, {5000, true, 500}},
      {STENT, {15000, true, 500}},
      {ULTRASOUND, {2000, true, 100}}
    }
  },
  {
    OUTPATIENT, {
      {CHECKUP, {200, true, 10}},
      {EKG, {500, false}},
      {ENDOSCOPY, {5000, true, 500}},
      {ULTRASOUND, {1500, true, 100}}
    }
  }
};

std::vector<PatientInfo> patientInfos(int count) {
  auto pv = std::vector<PatientInfo>();
  for (int i = 0; i < count; ++i) {
    PatientKind kind = random() % 10 > 7 ? INPATIENT : OUTPATIENT;
    pv.push_back({
      rand() % 900000 + 100000,
      rand() % 10 > 3,
      kind,
      [kind]() {
        auto procedures = std::vector<ProcedureKind>();
        for (auto p : PROCEDURES[kind]) {
          if (random() % 2 > 0) {
            procedures.push_back(p.first);
          }
        }

        return procedures;
      }()
    });
  }

  return pv;
}
