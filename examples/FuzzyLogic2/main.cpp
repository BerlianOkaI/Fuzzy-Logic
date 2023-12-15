#include <iostream>
#include "FuzzyLogic.h"
using namespace std;

/* It is recommended to use some define like this */
// Linguistic Value of Temperature
#define COLD        0
#define COOL        1
#define HOT         2

// Linguistic Value of Humidity
#define DRY         0
#define WET         1

// Linguistic Variables of Inputs
#define TEMP        0
#define HUM         1

// Linguistic Value of Output (it can be heater power or something else)
#define LOW         0
#define MED         1
#define HIGH        2

// Linguistic Variables of outputs
#define HEATER      0
// Note: Since the output in this example is only one, then we don't have to use
// HEATER definition in our program.


// Declaring FuzzySet(s) [Linguistic Values]
FuzzySet Temperature[3];
FuzzySet Humidity[2];
FuzzySet Heat[3];

// Declaring FuzzyFrame(s) [Linguistic Variables]
FuzzyFrame FramesInput[2];
FuzzyFrame FramesOutput[1];

// Declaring FuzzyRule(s)
FuzzyRule myRule[6];
u_int input_rules[6][2];              // 6 Rule with 2 premise
u_int output_rules[6][1];             // 6 Rule with 1 conclusion

// Declaring FuzzySystem
FuzzySystem mySystem(myRule, 6);      // Fuzzy System with 6 rule

void setup(void)
{
    // Setup for input frames
    FramesInput[TEMP].Frame_SetUp(Temperature, 3, 0.0, 100.0, INPUT);
    FramesInput[HUM].Frame_SetUp(Humidity, 2, 0.0, 100.0, INPUT);

    // Determining Linguistic Values characteristics of input frames via membership function shape
    FramesInput[TEMP].Set_SetUp(COLD, TRP_L, 10.0, 30.0);
    FramesInput[TEMP].Set_SetUp(COOL, TRP_C, 10.0, 30.0, 50.0, 70.0);
    FramesInput[TEMP].Set_SetUp(HOT, TRP_R, 50.0, 70.0);

    FramesInput[HUM].Set_SetUp(DRY, TRP_L, 30.0, 60.0);
    FramesInput[HUM].Set_SetUp(WET, TRP_R, 30.0, 60.0);

    // Setup for output frames
    FramesOutput[0].Frame_SetUp(Heat, 3, 0.0, 10.0, OUTPUT);

    // Determining Linguistic Values characteristics of output frames via membership function shape
    FramesOutput[0].Set_SetUp(LOW, TRP_L, 2.5, 5.0);
    FramesOutput[0].Set_SetUp(MED, TRI, 2.5, 5.0, 7.5);
    FramesOutput[0].Set_SetUp(HIGH, TRP_R, 5.0, 7.5);

    // Setup for rules
    myRule[0].Rule_SetUp(FramesInput, input_rules[0], 2, FramesOutput, output_rules[0], 1);
    input_rules[0][TEMP] = COLD;    input_rules[0][HUM] = DRY;
    output_rules[0][0] = MED;

    myRule[1].Rule_SetUp(FramesInput, input_rules[1], 2, FramesOutput, output_rules[1], 1);
    input_rules[1][TEMP] = COLD;    input_rules[1][HUM] = WET;
    output_rules[1][0] = HIGH;

    myRule[2].Rule_SetUp(FramesInput, input_rules[2], 2, FramesOutput, output_rules[2], 1);
    input_rules[2][TEMP] = COOL;    input_rules[2][HUM] = DRY;
    output_rules[2][0] = MED;

    myRule[3].Rule_SetUp(FramesInput, input_rules[3], 2, FramesOutput, output_rules[3], 1);
    input_rules[3][TEMP] = COOL;    input_rules[3][HUM] = WET;
    output_rules[3][0] = HIGH;

    myRule[4].Rule_SetUp(FramesInput, input_rules[4], 2, FramesOutput, output_rules[4], 1);
    input_rules[4][TEMP] = HOT;    input_rules[4][HUM] = DRY;
    output_rules[4][0] = LOW;

    myRule[5].Rule_SetUp(FramesInput, input_rules[5], 2, FramesOutput, output_rules[5], 1);
    input_rules[5][TEMP] = HOT;    input_rules[5][HUM] = WET;
    output_rules[5][0] = LOW;
}



int main()
{
    // Setups
    setup();

    // Initiate desired inputs
    float inputs[2];
    // Initiate calculated defuzzyficated output
    float output_crisp;

    // Inputs value
    inputs[TEMP] = 28;
    inputs[HUM] = 39.2;

    // Calculate the output
    output_crisp = mySystem.Defuzzyfication(inputs, 0);

    // Show the output
    cout << "Defuzzyfication of output: " << "\t" << output_crisp << endl;

    return 0;
}
