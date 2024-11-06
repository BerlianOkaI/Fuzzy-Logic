#include <iostream>
#include <stdio.h>
#include "FuzzyLogic.h"

using namespace std;

// FUZZY LOGIC FOR CONTROLLING ESC
// Fuzzy Logic: Antecedent part declaration
#define		X_LEFT		0
#define		X_MID		1
#define		X_RIGHT		2
#define		Y_BOT		0
#define		Y_MID		1
#define		Y_TOP		2
#define		JOY_X		0
#define		JOY_Y		1

FuzzySet	XAxisVar[3];
FuzzySet	YAxisVar[3];
FuzzyFrame	joystickInput[2];

// Fuzzy Logic: Consequent part declaration
#define		PROP_STOP	0
#define		PROP_RUN	1
#define		PROP_LEFT	0
#define		PROP_RIGHT	1

FuzzySet	propOutL[2];
FuzzySet	propOutR[2];
FuzzyFrame	proppelerOutput[2];

// Fuzzy Logic: Rules Declaration
FuzzyRule		PropRules[9];
unsigned int	JS_Antecedent[9][2];
unsigned int	prop_Consequent[9][2];

// Fuzzy Logic: Fuzzy System
FuzzySystem		propFuzzyControl(PropRules, 9);

static void FuzzySetup(void)
{
	// Input Frames
	joystickInput[JOY_X].Frame_SetUp(XAxisVar, 3, 0.0F, 255.0F, INPUT);
	joystickInput[JOY_Y].Frame_SetUp(YAxisVar, 3, 0.0F, 255.0F, INPUT);

	joystickInput[JOY_X].Set_SetUp(X_LEFT, TRP_L, 0.0F, 112.0F);
	joystickInput[JOY_X].Set_SetUp(X_MID, TRP_C, 0.0F, 112.0F, 144.0F, 255.0F);
	joystickInput[JOY_X].Set_SetUp(X_RIGHT, TRP_R, 144.0F, 255.0F);

	joystickInput[JOY_Y].Set_SetUp(Y_BOT, TRP_L, 0.0F, 112.0F);
	joystickInput[JOY_Y].Set_SetUp(Y_MID, TRP_C, 0.0F, 112.0F, 144.0F, 255.0F);
	joystickInput[JOY_Y].Set_SetUp(Y_TOP, TRP_R, 144.0F, 255.0F);

	// Output Frames
	proppelerOutput[PROP_LEFT].Frame_SetUp(propOutL, 2, 0.0F, 10.0F, OUTPUT);
	proppelerOutput[PROP_LEFT].domainSetUp(0.0F, 10.0F, 10.0F);
	proppelerOutput[PROP_RIGHT].Frame_SetUp(propOutR, 2, 0.0F, 10.0F, OUTPUT);
	proppelerOutput[PROP_RIGHT].domainSetUp(0.0F, 10.0F, 10.0F);

	proppelerOutput[PROP_LEFT].Set_SetUp(PROP_STOP, SINGLE, 0.0F);
	proppelerOutput[PROP_LEFT].Set_SetUp(PROP_RUN, SINGLE, 10.0F);

	proppelerOutput[PROP_RIGHT].Set_SetUp(PROP_STOP, SINGLE, 0.0F);
	proppelerOutput[PROP_RIGHT].Set_SetUp(PROP_RUN, SINGLE, 10.0F);

	// Setting Fuzy Rules (This section will make you get headache, LMAO)
	PropRules[0].Rule_SetUp(joystickInput, JS_Antecedent[0], 2, proppelerOutput, prop_Consequent[0], 2);
	JS_Antecedent[0][JOY_X] = X_LEFT;
	JS_Antecedent[0][JOY_Y] = Y_BOT;
	prop_Consequent[0][PROP_LEFT] = PROP_STOP;
	prop_Consequent[0][PROP_RIGHT] = PROP_STOP;

	PropRules[1].Rule_SetUp(joystickInput, JS_Antecedent[1], 2, proppelerOutput, prop_Consequent[1], 2);
	JS_Antecedent[1][JOY_X] = X_MID;
	JS_Antecedent[1][JOY_Y] = Y_BOT;
	prop_Consequent[1][PROP_LEFT] = PROP_STOP;
	prop_Consequent[1][PROP_RIGHT] = PROP_STOP;

	PropRules[2].Rule_SetUp(joystickInput, JS_Antecedent[2], 2, proppelerOutput, prop_Consequent[2], 2);
	JS_Antecedent[2][JOY_X] = X_RIGHT;
	JS_Antecedent[2][JOY_Y] = Y_BOT;
	prop_Consequent[2][PROP_LEFT] = PROP_STOP;
	prop_Consequent[2][PROP_RIGHT] = PROP_STOP;

	// *
	PropRules[3].Rule_SetUp(joystickInput, JS_Antecedent[3], 2, proppelerOutput, prop_Consequent[3], 2);
	JS_Antecedent[3][JOY_X] = X_LEFT;
	JS_Antecedent[3][JOY_Y] = Y_MID;
	prop_Consequent[3][PROP_LEFT] = PROP_STOP;
	prop_Consequent[3][PROP_RIGHT] = PROP_RUN;

	PropRules[4].Rule_SetUp(joystickInput, JS_Antecedent[4], 2, proppelerOutput, prop_Consequent[4], 2);
	JS_Antecedent[4][JOY_X] = X_MID;
	JS_Antecedent[4][JOY_Y] = Y_MID;
	prop_Consequent[4][PROP_LEFT] = PROP_STOP;
	prop_Consequent[4][PROP_RIGHT] = PROP_STOP;

	PropRules[5].Rule_SetUp(joystickInput, JS_Antecedent[5], 2, proppelerOutput, prop_Consequent[5], 2);
	JS_Antecedent[5][JOY_X] = X_RIGHT;
	JS_Antecedent[5][JOY_Y] = Y_MID;
	prop_Consequent[5][PROP_LEFT] = PROP_RUN;
	prop_Consequent[5][PROP_RIGHT] = PROP_STOP;

	// *
	PropRules[6].Rule_SetUp(joystickInput, JS_Antecedent[6], 2, proppelerOutput, prop_Consequent[6], 2);
	JS_Antecedent[6][JOY_X] = X_LEFT;
	JS_Antecedent[6][JOY_Y] = Y_TOP;
	prop_Consequent[6][PROP_LEFT] = PROP_STOP;
	prop_Consequent[6][PROP_RIGHT] = PROP_RUN;

	PropRules[7].Rule_SetUp(joystickInput, JS_Antecedent[7], 2, proppelerOutput, prop_Consequent[7], 2);
	JS_Antecedent[7][JOY_X] = X_MID;
	JS_Antecedent[7][JOY_Y] = Y_TOP;
	prop_Consequent[7][PROP_LEFT] = PROP_RUN;
	prop_Consequent[7][PROP_RIGHT] = PROP_RUN;

	PropRules[8].Rule_SetUp(joystickInput, JS_Antecedent[8], 2, proppelerOutput, prop_Consequent[8], 2);
	JS_Antecedent[8][JOY_X] = X_RIGHT;
	JS_Antecedent[8][JOY_Y] = Y_TOP;
	prop_Consequent[8][PROP_LEFT] = PROP_RUN;
	prop_Consequent[8][PROP_RIGHT] = PROP_STOP;
}

float u_left[33][33];
float u_right[33][33];
float u_com[33][33];
float u_dif[33][33];

int main(void)
{
	FuzzySetup();
	float joy_x_value, joy_y_value;
	float prop_left, prop_right;

	while (1)
	{
		/* Begin the simulation after user input is given by user */
		// The input can be any key that is pressed
		unsigned char dummy;
		cout << "Begining simmulation. Press any key to continue" << endl;
		cin >> dummy;

		/* 
		 * + In this section, the crisp output--defuzzyfication of
		 *   fuzzy output--of u_left and u_right for all
		 *   combination of joystick inputs will be computed.
		 * + After that, the output vector (u_left, u_right) will be
		 *   transformed into (u_com, u_dif).
		 */
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 33; j++)
			{
				joy_x_value = ((float)i) * 8.0F;
				joy_y_value = ((float)j) * 8.0F;
				
				// Compute the crisp output of u_left and u_right
				u_left[i][j] = propFuzzyControl.Defuzzyfication(new float[2] {joy_x_value, joy_y_value}, PROP_LEFT);
				u_right[i][j] = propFuzzyControl.Defuzzyfication(new float[2] {joy_x_value, joy_y_value}, PROP_RIGHT);

				// Transform the output into u_com and u_dif
				u_com[i][j] = (u_left[i][j] + u_right[i][j]) / 2.0F;
				u_dif[i][j] = (u_left[i][j] - u_right[i][j]) / 2.0F;
			}
		}

		/* In this part, we have compute the transformed output data */
		// Print all of it into console
		cout << "Here is the result for common propeller" << endl;
		cout << "[" << '\n';
		for (int i = 0; i < 33; i++)
		{
			cout << '\t' << "[";
			for (int j = 0; j < 33; j++)
			{
				cout << u_com[j][i];
				if (j < 32) {
					cout << ", ";
				}
			}
			cout << "]";
			if (i < 32) {
				cout << ", " << endl;
			}
			else {
				cout << endl;
			}
		}
		cout << "]" << endl << endl;

		cout << "Here is the result for differential propeller" << endl;
		cout << "[" << '\n';
		for (int i = 0; i < 33; i++)
		{
			cout << '\t' << "[";
			for (int j = 0; j < 33; j++)
			{
				cout << u_dif[j][i];
				if (j < 32) {
					cout << ", ";
				}
			}
			cout << "]";
			if (i < 32) {
				cout << ", " << endl;
			}
			else {
				cout << endl;
			}
		}
		cout << "]" << endl;
	}
	
	return 0;
}