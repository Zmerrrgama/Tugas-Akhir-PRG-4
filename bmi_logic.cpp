#include <emscripten/emscripten.h>
#include <string>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    float calculateBMI(float weight, float height) {
        float h_m = height/100;
        return weight/(h_m*h_m);
    }

    EMSCRIPTEN_KEEPALIVE
    float calculateBodyFat(float bmi, int age, int gender) {
        // 1 = male, 0 = female
        return (1.20*bmi)+(0.23*age)-(10.8*gender)-5.4;
    }

    EMSCRIPTEN_KEEPALIVE
    float calculateBMR(float weight, float height, int age, int gender) {
        if (gender == 1) { 
            return (10*weight)+(6.25*height)-(5*age)+5;
        } else { 
            return (10*weight)+(6.25*height)-(5*age)-161;
        }
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getDisplayTitle(float bmi) {
        if (bmi < 18.5){
            return "UNDERWEIGHT";
        }
        else if (bmi < 25){
            return "HEALTHY WEIGHT";
        }
        else if (bmi < 30){
            return "OVERWEIGHT";
        }
        else {
            return"OBESITAS";
        }
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getTitleColor(float bmi) {
        if (bmi < 18.5){
            return "#444b57"; // Blueish
        }
        else if (bmi < 25){
            return "#3b4b34"; // Greenish
        }
        else if (bmi < 30){
            return "#d68c1c"; // Orange
        }
        else{
            return "#a04028"; // Red
        }
    }

    EMSCRIPTEN_KEEPALIVE
    const char* getRecommendation(float bmi) {
        if (bmi < 18.5){
            return "Tingkatkan asupan kalori dengan makanan padat nutrisi.";
        }
        else if (bmi < 25){
            return "Pertahankan pola makan seimbang dan olahraga rutin.";
        }
        else if (bmi < 30){
            return "Tingkatkan aktivitas fisik (jalan 30 menit) dan kurangi gula.";
        }
        else{
            return "Kurangi 500 kkal/hari. Fokus pada protein tanpa lemak.";
        }
    }

    EMSCRIPTEN_KEEPALIVE
    int hasHealthRisks(float bmi) {
        int c;
        if (bmi >=30){
            return 1;
        }
        else {
            return 0;
        }
    }

    EMSCRIPTEN_KEEPALIVE
    float getIdealMin(float height) {
        float h_m = height/100;
        return 18.5*(h_m*h_m);
    }

    EMSCRIPTEN_KEEPALIVE
    float getIdealMax(float height) {
        float h_m = height/100;
        return 24.9*(h_m*h_m);
    }
    
    EMSCRIPTEN_KEEPALIVE
    const char* getClassification(float bmi) {
        if (bmi < 18.5){
            return "Underweight";
        }
        else if (bmi < 25){
            return "Normal Weight";
        }
        else if (bmi < 30){
            return "Overweight";
        }
        else if (bmi < 35){
            return "Obesitas Kelas 1";
        }
        else if (bmi < 40){
            return "Obesitas Kelas 2";
        }
        else{
            return "Obesitas Kelas 3";
        }
    }

    EMSCRIPTEN_KEEPALIVE
    float calculateTDEE(float bmr, int activity_level) {
        float multiplier;
        switch(activity_level) {
            case 1: multiplier = 1.2f; break;
            case 2: multiplier = 1.375f; break;
            case 3: multiplier = 1.55f; break;
            case 4: multiplier = 1.725f; break;
            default: multiplier = 1.2f; break;
        }
        return bmr * multiplier;
    }

    EMSCRIPTEN_KEEPALIVE
    float predictWeightChange(float total_intake, float tdee) {
        float net = total_intake-tdee;
        return net/7700.0f; 
    }
}