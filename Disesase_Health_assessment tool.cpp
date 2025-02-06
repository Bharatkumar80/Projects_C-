#include <iostream>
#include <iomanip>
#include <string>
#include <cmath> // Include cmath for power function

using namespace std;

int main() {
    // Declaring all the variables for the health assessment
    double heightInInches, weightInPounds, ageInYears, bodyTempInFahrenheit, riskScore = 0, bmiIndex;
    int shortnessOfBreath, chestPain;
    string difficultyLevel, chestLevel, tempStatus, ageCategory;
    char continueAssessment;

    do {
        // Collecting user data for the assessment
        cout << "Please Enter Height of Person in Inches: ";   
        cin >> heightInInches;

        // Validating user input for height
        while (heightInInches < 50) {
            cout << "The height you entered (" << heightInInches << " inches) is too short. It should be at least 50 inches." << endl;
            cout << "Please enter a valid height: ";
            cin >> heightInInches;
        }

        cout << "Please Enter Weight of Person in Pounds: "; 
        cin >> weightInPounds;

        // Validating user input for weight
        while (weightInPounds <= 70) {
            cout << "The weight you entered (" << weightInPounds << " lbs) is too low. Weight should be above 70 pounds." << endl;
            cout << "Please enter a valid weight: ";
            cin >> weightInPounds;
        }

        cout << "Please Enter Age of Person in Years: "; 
        cin >> ageInYears;

        // Validating user input for age
        while (ageInYears < 16) {
            cout << "The age you entered (" << ageInYears << " years) is too young. Age should be at least 16 years." << endl;
            cout << "Please enter a valid age: ";
            cin >> ageInYears;
        }

        cout << "Please Enter Body Temperature of Person in Fahrenheit: "; 
        cin >> bodyTempInFahrenheit;

        // Validating user input for body temperature
        while (bodyTempInFahrenheit < 96) {
            cout << "The temperature you entered (" << bodyTempInFahrenheit << "°F) is too low. It should be at least 96°F." << endl;
            cout << "Please enter a valid body temperature: ";
            cin >> bodyTempInFahrenheit;
        }

        // Asking for the severity of symptoms on a scale of 0 to 10
        cout << "Please provide the severity of these symptoms on a scale from 0 to 10 (0 being none, 10 being the worst)." << endl;
        cout << "Do you have shortness of breath? ";
        cin >> shortnessOfBreath;

        // Validating user input for shortness of breath severity
        while (shortnessOfBreath < 0 || shortnessOfBreath > 10) {
            cout << "The value you entered for shortness of breath (" << shortnessOfBreath << ") is out of range! Please enter a value between 0 and 10: ";
            cin >> shortnessOfBreath;
        }

        cout << "Are you experiencing chest pain? ";
        cin >> chestPain;

        // Validating user input for chest pain severity
        while (chestPain < 0 || chestPain > 10) {
            cout << "The value you entered for chest pain (" << chestPain << ") is out of range! Please enter a value between 0 and 10: ";
            cin >> chestPain;
        }

        // Calculating the BMI value
        bmiIndex = (weightInPounds * 703) / pow(heightInInches, 2);

        // Outputting the initial report
        cout << "\nHealth Assessment Report:" << endl;
        cout << setprecision(1) << fixed;
        cout << "Weight: " << weightInPounds << " lbs; Height: " << heightInInches << " inches." << endl;
        cout << "Body Mass Index (BMI): " << setprecision(2) << bmiIndex;
        cout << setprecision(1) << fixed;

        // Providing BMI classification
        if (bmiIndex < 18.5) {
            cout << ", You are considered Underweight." << endl;
        } else if (bmiIndex >= 18.5 && bmiIndex < 25) {
            cout << ", You are considered Normal weight." << endl;
        } else if (bmiIndex >= 25 && bmiIndex < 30) {
            cout << ", You are considered Overweight." << endl;
        } else {
            cout << ", You are considered Obese." << endl;
        }

        cout << "You are " << ageInYears << " years old.";

        // Providing age category
        if (ageInYears >= 65) {
            ageCategory = ", You are categorized as Senior.";
            cout << ageCategory;
        }
        cout << endl;

        // Providing temperature status
        cout << "You reported a body temperature of " << bodyTempInFahrenheit;
        if (bodyTempInFahrenheit > 100.4 && bodyTempInFahrenheit <= 102) {
            tempStatus = ", You are having a Mild Fever.";
            cout << tempStatus;
        }
        else if (bodyTempInFahrenheit > 102) {
            tempStatus = ", You are having a High Fever.";
            cout << tempStatus;
        }

        cout << endl;

        // Calculating health risk score
        if (bmiIndex >= 25 && bmiIndex < 30) {
            riskScore += 7;
        } else if (bmiIndex >= 30 && bmiIndex < 40) {
            riskScore += 18;
        } else if (bmiIndex >= 40) {
            riskScore += 30;
        }

        if (ageInYears >= 65) {
            riskScore += 22;
        } else if (ageInYears >= 60 && ageInYears <= 64) {
            riskScore += 12;
        } else if (ageInYears >= 45 && ageInYears <= 59) {
            riskScore += 7;
        }

        if (bodyTempInFahrenheit > 102.0) {
            riskScore += 45;
        } else if (bodyTempInFahrenheit > 100.4 && bodyTempInFahrenheit <= 102.0) {
            riskScore += 28;
        }

        if (shortnessOfBreath >= 1 && shortnessOfBreath <= 3) {
            riskScore += 12; // Mild
            difficultyLevel = "Mild";
        } else if (shortnessOfBreath >= 4 && shortnessOfBreath <= 6) {
            riskScore += 24; // Moderate
            difficultyLevel = "Moderate";
        } else if (shortnessOfBreath >= 7 && shortnessOfBreath <= 10) {
            riskScore += 50; // Severe
            difficultyLevel = "Severe";
        }

        cout << "You reported " << difficultyLevel << " difficulty with breathing." << endl;

        if (chestPain >= 1 && chestPain <= 3) {
            riskScore += 12; // Mild
            chestLevel = "Mild";
        } else if (chestPain >= 4 && chestPain <= 6) {
            riskScore += 30; // Moderate
            chestLevel = "Moderate";
        } else if (chestPain >= 7 && chestPain <= 10) {
            riskScore += 55; // Severe
            chestLevel = "Severe";
        }

        cout << "You reported " << chestLevel << " chest pain." << endl;

        cout << "\nYour Health Risk Score is " << riskScore << ". Recommendations:" << endl;

        // Providing recommendations based on the health risk score
        if (riskScore < 25) {
            cout << "Get plenty of rest and stay hydrated." << endl;
        } else if (riskScore >= 25 && riskScore < 60) {
            cout << "Consider taking over-the-counter pain relievers and testing for XYZ21." << endl;
        } else if (riskScore >= 60 && riskScore < 120) {
            cout << "You should undergo a PCR test for XYZ21." << endl;
        } else {
            cout << "Immediate medical attention is required." << endl;
        }

        if (chestPain >= 7 && chestPain <= 10) {
            cout << "Severe chest pain is serious. Seek medical help immediately." << endl;
        }

        if (shortnessOfBreath >= 7 && shortnessOfBreath <= 10) {
            cout << "Severe shortness of breath is critical. Seek immediate medical help." << endl;
        }

        // Asking if the user wants to continue
        cout << "Would you like to assess another person? (Y/N): ";
        cin >> continueAssessment;

    } 
    // Repeat if user inputs Y
    while (continueAssessment == 'Y' || continueAssessment == 'y');

    cout << "Thank you for using the health assessment tool." << endl;
    return 0;
}
