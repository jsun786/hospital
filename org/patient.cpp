/**
 * Implementation of Patient class.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "org/patient.h"

#include <map>
#include <utility>  // std::pair

namespace {
// Procedure-specific discounts provided by the hospital
std::map<ProcedureKind, double> HOSPITAL_DISCOUNT_LIST = {{BOTOX, 100}};
// Discount rate for multiple procedures
const double HOSPITAL_MULTI_DISCOUNT_RATE = .2;
// Minumum number of procedures required for multiple discount
const int HOSPITAL_MULTI_DISCOUNT_MIN = 3;

// Discount rates for some procedures if a designated procedure is taken
// together, provided by the insurance for inpatients
std::pair<ProcedureKind, std::map<ProcedureKind, double>>
    INSURANCE_CONDITIONAL_DISCOUNTS = {ULTRASOUND,
                                       {{ANGIOPLASTY, .5}, {STENT, .5}}};
// Discount rate on all procedures, provided by the insurance for outpatients
const double INSURANCE_DISCOUNT_RATE = .3;
}  // namespace

// Initialize a patient with patient id, patient kind, and insurance status
Patient::Patient(int id, PatientKind patientKind, bool isInsured)
    : patientId(id), kind(patientKind), hasInsurance(isInsured) {}

// Add procedure to this patient's record, return true if the procedure
// is available at the hospital and suits the patient kind, return
// false if the procedure is invalid
bool Patient::addProcedure(const ProcedureKind procedure) {
  if (PROCEDURES[kind].find(procedure) == PROCEDURES[kind].end()) {
    return false;
  } else {
    procedures.push_back(procedure);
    return true;
  }
}

// Return the total amount this patient is charged by the hospital after
// applying available discounts. Note that insurance is not considered
// and the output is not the actual amount this patient pays
double Patient::billing() {
  double result = 0;
  for (auto procedure : procedures) {
    double price = PROCEDURES[kind][procedure].cost;
    if (HOSPITAL_DISCOUNT_LIST.find(procedure) !=
        HOSPITAL_DISCOUNT_LIST.end()) {
      price -= HOSPITAL_DISCOUNT_LIST[procedure];
    }
    result += price;
  }
  if (procedures.size() >= HOSPITAL_MULTI_DISCOUNT_MIN) {
    result *= (1 - HOSPITAL_MULTI_DISCOUNT_RATE);
  }
  return result;
}

// Initalize an inpatient
InPatient::InPatient(int id, PatientKind patientKind, bool isInsured)
    : Patient(id, INPATIENT, isInsured) {}

// Return the liability of this inpatient
double InPatient::liability() {
  double noInsurancePayment = billing();
  if (hasInsurance) {
    double totalCopay = 0;
    double totalNonCopay = 0;
    double totalPayment = 0;
    bool conditionalDiscount =
        HAS(procedures, INSURANCE_CONDITIONAL_DISCOUNTS.first);
    for (auto procedure : procedures) {
      Procedure procedureInfo = PROCEDURES[kind][procedure];
      // Payment covered by insurance
      if (procedureInfo.covered) {
        double currentCopay = procedureInfo.copay;
        std::map<ProcedureKind, double> discountsList =
            INSURANCE_CONDITIONAL_DISCOUNTS.second;
        if (conditionalDiscount &&
            (discountsList.find(procedure) != discountsList.end())) {
          currentCopay *= (1 - discountsList[procedure]);
        }
        totalCopay += currentCopay;
      } else {
        // Payment not covered by insurance
        totalNonCopay += procedureInfo.cost;
        if (HOSPITAL_DISCOUNT_LIST.find(procedure) !=
            HOSPITAL_DISCOUNT_LIST.end()) {
          totalNonCopay -= HOSPITAL_DISCOUNT_LIST[procedure];
        }
      }
    }
    // Apply hospital's multi-procedure discount
    if (procedures.size() >= HOSPITAL_MULTI_DISCOUNT_MIN) {
      totalNonCopay *= (1 - HOSPITAL_MULTI_DISCOUNT_RATE);
    }
    totalPayment = totalCopay + totalNonCopay;
    return (totalPayment < noInsurancePayment ? totalPayment
                                              : noInsurancePayment);
  } else {
    return noInsurancePayment;
  }
}

// Initalize an outpatient
OutPatient::OutPatient(int id, PatientKind patientKind, bool isInsured)
    : Patient(id, OUTPATIENT, isInsured) {}

// Return the liability of this outpatient
double OutPatient::liability() {
  double noInsurancePayment = billing();
  if (hasInsurance) {
    double totalCopay = 0;
    double totalNonCopay = 0;
    double totalPayment = 0;
    for (auto procedure : procedures) {
      Procedure procedureInfo = PROCEDURES[kind][procedure];
      if (procedureInfo.covered) {
        totalCopay += procedureInfo.copay;
      } else {
        totalNonCopay += procedureInfo.cost;
        if (HOSPITAL_DISCOUNT_LIST.find(procedure) !=
            HOSPITAL_DISCOUNT_LIST.end()) {
          totalNonCopay -= HOSPITAL_DISCOUNT_LIST[procedure];
        }
      }
    }
    totalCopay *= (1 - INSURANCE_DISCOUNT_RATE);  // Apply insurance waiver
    // Apply hospital's multi-procedure discount
    if (procedures.size() >= HOSPITAL_MULTI_DISCOUNT_MIN) {
      totalNonCopay *= (1 - HOSPITAL_MULTI_DISCOUNT_RATE);
    }
    totalPayment = totalCopay + totalNonCopay;
    return (totalPayment < noInsurancePayment ? totalPayment
                                              : noInsurancePayment);
  } else {
    return noInsurancePayment;
  }
}