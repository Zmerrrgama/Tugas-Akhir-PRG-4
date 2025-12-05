#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

struct person { // using struct
    string name;
    int age;
    char gender; 
};

float BMI(int height, float mass) {
    float h_m = height/100.0f; 
    return mass/(h_m*h_m);
}

// calculating body fat
float body_fat(float bmi, int age, char gender) {
    int gender_mult;
    if (gender == 'M' || gender == 'm'){
        gender_mult = 1;
    } 
    else{
        gender_mult = 0;
    }
    return ((1.20*bmi)+(0.23*age)-(10.8*gender_mult)-5.4);
}

float BMR(float mass, int height, int age, char gender) {
    if (gender == 'M' || gender == 'm') {
        return (10*mass)+(6.25*height)-(5*age)+5;
    } else {
        return (10*mass)+(6.25*height)-(5*age)-161;
    }
}

void create_profile() {
    system("clear");
    person newperson;
    string FILENAME = "tracker.txt"; // define .txt file

    cout << ">>>>> NEW PROFILE <<<<<" << endl;
    cin.ignore(); 
    cout << "Enter Name (use_underscore): ";
    cin >> newperson.name;
    cout << "Enter Age: ";
    cin >> newperson.age;

    while (true) {
        cout << "Enter Gender (M/F): ";
        cin >> newperson.gender;
        if (newperson.gender == 'M' || newperson.gender == 'm' || newperson.gender == 'F' || newperson.gender == 'f') {
            break;
        }
        cout << "Invalid input. Please enter M or F." << endl;
    }

    ofstream fileOutput(FILENAME, ios::app); // append data to .txt file
    if (!fileOutput.is_open()) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    fileOutput << newperson.name << " " << newperson.age << " " << newperson.gender << endl;
    
    fileOutput.close();
    cout << "\nProfile Saved! Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void delete_profile() {
    system("clear");
    ifstream fileInput("tracker.txt");
    vector<person> users; // define what to do
    person temp;

    if (fileInput.is_open()) {
        while (fileInput >> temp.name >> temp.age >> temp.gender) {
            users.push_back(temp);
        }
        fileInput.close();
    }

    if (users.empty()) {
        cout << "No profiles to delete." << endl;
        cout << "Press Enter to return...";
        cin.ignore(); 
        cin.get();
        return;
    }

    cout << ">>>>> DELETE PROFILE <<<<<" << endl;
    for (size_t i = 0; i < users.size(); i++) {
        cout << i + 1 << ". " << users[i].name << " (" << users[i].age << ")" << endl;
    }
    cout << "0. Cancel" << endl;
    cout << "Select number to delete: ";

    int choice;
    if (!(cin >> choice)) {
        cin.clear(); 
        cin.ignore();
        return;
    }

    if (choice == 0) return;

    if (choice > 0 && choice <= users.size()) { // make sure it exist
        string deletedName = users[choice - 1].name; 
        users.erase(users.begin() + (choice - 1)); // erasing the name

        ofstream fileOutput("tracker.txt", ios::trunc); // delete all of the data before recovering the data except the one that being deleted
        for (const auto& p : users) { 
            fileOutput << p.name << " " << p.age << " " << p.gender << endl;
        }
        fileOutput.close();

        cout << "\nProfile '" << deletedName << "' deleted successfully!" << endl;
    } else {
        cout << "Invalid selection." << endl;
    }

    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get();
}

void calorie_tracker(float bmr) {
    float total_intake = 0;
    float input_cal;
    int activity_level;
    float tdee; // energy expenditure

    system("clear");
    cout << "--- CALORIE & WEIGHT CALCULATOR ---" << endl;
    
    cout << "Select your Activity Level:" << endl;
    cout << "1. Sedentary (Office job, little exercise)" << endl;
    cout << "2. Lightly Active (Exercise 1-3 days/week)" << endl;
    cout << "3. Moderately Active (Exercise 3-5 days/week)" << endl;
    cout << "4. Very Active (Hard exercise 6-7 days/week)" << endl;
    cout << "Choice: ";
    cin >> activity_level;

    float activity_multiplier;
    switch(activity_level) { // from harris-benedict
        case 1: 
            activity_multiplier = 1.2; 
            break;
        case 2: 
            activity_multiplier = 1.375; 
            break;
        case 3: 
            activity_multiplier = 1.55; 
            break;
        case 4: 
            activity_multiplier = 1.725; 
            break;
        default: 
            activity_multiplier = 1.2; 
            break;
    }

    tdee = bmr*activity_multiplier;

    cout << "\n--- MEALS ---" << endl;
    cout << "Enter calories for each meal (Type 0 when finished):" << endl;
    
    int count = 1;
    while(true) {
        cout << "Meal " << count << " (kcal): ";
        cin >> input_cal;
        if(input_cal <= 0) break;
        total_intake += input_cal;
        count++;
    }

    float net_calories = total_intake - tdee;
    float weight_change_kg = net_calories/7700; 

    cout << fixed << setprecision(2);

    cout << "\n--- DAILY REPORT ---" << endl;
    cout << "Total Consumed:   " << total_intake << " kcal" << endl;
    cout << "Est. Burned " << tdee << " kcal" << endl;
    cout << "Net Difference:   " << net_calories << " kcal" << endl;
    cout << "---------------------------" << endl;

    if (net_calories > 0) {
        cout << "Surplus Prediction: You will GAIN approx " << weight_change_kg << " kg" << endl;
        cout << "(If you eat like this every day)" << endl;
    } else if (net_calories < 0) {
        cout << "Deficit Prediction: You will LOSE approx " << (weight_change_kg * -1) << " kg" << endl;
        cout << "(If you eat like this every day)" << endl;
    } else {
        cout << "You are maintaining your weight perfectly." << endl;
    }

    cout << "\nPress Enter to return...";
    cin.ignore(); 
    cin.get();
}

void calculator(person p) {
    float weight;
    int height;
    
    system("clear");
    cout << "Welcome, " << p.name << "!" << endl;
    cout << "Profile: " << p.age << " yrs, " << p.gender << endl;
    cout << "---------------------------" << endl;
    cout << "Please enter your current weight (kg): ";
    cin >> weight;
    cout << "Please enter your current height (cm): ";
    cin >> height;

    while(true) {
        system("clear");
        float bmi = BMI(height, weight);
        float bfp = body_fat(bmi, p.age, p.gender);
        float bmr = BMR(weight, height, p.age, p.gender);

        cout << fixed << setprecision(2);

        cout << "\n--- RESULTS ---" << endl;
        cout << "BMI: " << bmi << " -> ";
        
        if(bmi < 18.5){
            cout << "Underweight" << endl;
            cout << "Increase calorie intake with nutrient dense foods";
        }
        else if(bmi < 25){
            cout << "Normal Weight" << endl;
            cout << "Maintain a balanced diet and regular exercise";
        }
        else if(bmi < 30){
            cout << "Overweight" << endl;
            cout << "Increase physical activity (walk 30 minutes) and reduce sugar";
        }
        else if (bmi < 35){
            cout << "Obesity Type 1" << endl;
            cout << "Reduce your intake by 500 kcal/day. Focus on lean protein.";
        }
        else if (bmi < 40){
            cout << "Obesity Type 2" << endl;
            cout << "Reduce your intake by 500 kcal/day. Focus on lean protein.";
        }
        else{
            cout << "Obesity Type 3" << endl;
            cout << "Reduce your intake by 500 kcal/day. Focus on lean protein.";
        }
        cout << endl;

        cout << "Body Fat Percentage: " << bfp << "%" << endl;
        cout << "BMR (Calories/Day): " << bmr << " kcal" << endl;
        
        cout << "\n--- MENU ---" << endl;
        cout << "1. Update Weight/Height" << endl;
        cout << "2. Calorie & Weight Projection" << endl; 
        cout << "3. Log Out" << endl;
        cout << "Select: ";
        
        int choice;
        if(!(cin >> choice)) {
            cin.clear(); cin.ignore();
            continue;
        }

        if(choice == 1) {
            cout << "New Weight (kg): ";
            cin >> weight;
            cout << "New Height (cm): ";
            cin >> height;
        }
        else if(choice == 2) {
            calorie_tracker(bmr);
        }
        else if(choice == 3) {
            break;
        }
    }
}

void login() {
    system("clear");
    ifstream fileInput("tracker.txt"); // opening .txt file
    if (!fileInput.is_open()) {
        cout << "No profiles found. Please create one first." << endl;
        cout << "Press Enter...";
        cin.ignore(); 
        cin.get();
        return;
    }

    vector<person> users;
    person temp;
    
    while (fileInput >> temp.name >> temp.age  >> temp.gender) {
        users.push_back(temp); 
    }
    fileInput.close();

    if(users.empty()) {
        cout << "File is empty." << endl;
        cin.ignore(); cin.get();
        return;
    }

    cout << ">>>>> SELECT PROFILE <<<<<" << endl;
    for (size_t i = 0; i < users.size(); i++) {
        cout << i + 1 << ". " << users[i].name << endl;
    }
    cout << "0. Back" << endl;
    cout << "Choose number: ";
    
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= users.size()) {
        calculator(users[choice - 1]);
    }
}

int main() {
    int choice = -1;
    while (choice != 0) {
        system("clear");
        cout << "--------------------" << endl;
        cout << "--- HEALTH TRACKER ---" << endl;
        cout << "--------------------" << endl;
        cout << "1. Login Profile" << endl;
        cout << "2. Create New Profile" << endl;
        cout << "3. Delete Profile" << endl;
        cout << "0. Exit" << endl;
        cout << "Select: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                create_profile();
                break;
            case 3:
                delete_profile();
                break;
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option." << endl;
        }
    }
    return 0;
}