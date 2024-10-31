Author          : Berlian Oka Irvianto  (Indonesia)

Last Modified   : Friday, December 15th 2023


This is a library that consist a tool (`FuzzySet`, `FuzzyFrame`, `FuzzyRule`
and `FuzzySystem`) to implement Fuzzy Logic. This library was originally
created by the author for applying Fuzzy Logic as a control system in
embedded system (using avr microcontroller like ATmega328p etc). This
library also requires the user to play a lot with array declaration;
objects like `FuzzySet`, `FuzzyFrame` and `FuzzyRule` should be declared
as an array (for example, `FuzzySet mySet[3]`, `FuzzyRule myRule[27]`, etc).
For more details about how to use this library, please have a look on
program example that were provided by the author in this repository.

## HOW TO USE IN GENERAL
  
1. Declaration of Linguistic Values of each Linguistic Variables as array of class <FuzzySet>
   // Example:
   ```
   FuzzySet Temperatures[3]         // for linguistic variable temperature, it has 3 linguistic values (Cold, Cool, Hot)
   ```
  
2. Declaration of Linguistic Variables as array of class <FuzzyFrame>
   // Example:
  ```
  FuzzyFrame Antecedent[2]         // there are 2 frame as input (antecedent) that will be evaluated in FuzzyRule
  ```

3. Declaration of Fuzzy Rule as array of class <FuzzyRule> and declaration of antecedent and consequent
   as 2D unsigned int array
   // Example:
   ```
   FuzzyRule myRules[27]            // There are 27 rules. The number of rules depend on number of combination
                                    // of linguistic values of each linguistic variables in antecedent

   unsigned int input_rule[27][2]   // Of course there are 27 antecedent. Each antecedent consist of 2 linguistic values
                                    // of different linguistic variables to define specific "IF" part in IF-THEN rule

   unsigned int output_rule[27][1]  // Of course there are 27 consequent. Each consequent consist of 1 linguistic values
                                    // of 1 linguistic variables to define specific "THEN" part in IF-THEN rule
   ```
  
4. Declaration of FuzzySystem
   // Example:
   ```
   FuzzySystem mySystem(myRules, 27)// Declare a system that consist of 27 rule and use FuzzyRule that has been declared as argument

5. Setting up the FuzzySets, FuzzyFrames, and FuzzyRules that has been declared. This consist
   of determining the membership function of each FuzzySet(s), Determining wich FuzzyFrames as
   input frames (antecedent) and other one (consequent), Determining IF-THEN rule for each rule
   etc. For more details, please have a look on example program that were provided in this repository

6. Use the FuzzySystem to produce output (crisp) given by inputs
