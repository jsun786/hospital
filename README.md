# Hospital

The Pasadena Community Hospital is updating their patient management system and hired you to write the initial version of the software (*org/* folder). Below are the requirements they want you to follow:

* The hospital has a 100 bed facility and a clinic and accepts both inpatients and outpatients, each with their own set of procedures and pricing structures. Most procedures, but not all, are covered by insurance.
* If a procedure is covered by insurance and the patient has insurance, he is liable for the deductible part of the cost (less any discounts); otherwise, he has to pay the full amount (less discounts).
* When a patient visits the hospital, he is first added to the hospital system with his patient id and insurance info, as an inpatient or outpatient.
* As the patient goes through different procedures, each procedure is added to the patient record.
* Occasionally however, an invalid procedure (one that is not available in the hospital or for the patient kind of inpatient or outpatient) gets entered, and such events should be indicated by returning *false*.
* To help patients control costs, the hospital offers a 20% discount if the patient undergoes 3 or more procedures. Also, the clinic currently has a $100-off promotion for Botox procedures.
* Insurance companies are offering their own promotion waiving 50% of the deductibles for angioplasty and stent procedures for inpatients if they have also had an ultrasound. They are also waiving 30% of the deductibles on all procedures for outpatients.
* Periodically, the billing department needs to generate patient summary reports showing the patient id, insurance info (Yes/No), inpatient/outpatient kind, total billing, and the patient liability.

Much of the supporting files have already been created for you. Your job is to complete:

1. The patient implementation (*org/patient.cpp*).
1. Unit tests for the hospital (*test/hospital_test.cpp*) and patient (*test/patient_test.cpp*).
1. Integration test (*report.cpp*) that adds 100 test patients and their procedures and then generates a patient report. You can get the test data by calling patientInfos(100).
