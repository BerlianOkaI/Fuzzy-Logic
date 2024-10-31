Author          : Berlian Oka Irvianto  (Indonesia)

First Modified   : December 2023

Last Modified    : October 2024


This is a library that consist tools and objects (`FuzzySet`, `FuzzyFrame`, `FuzzyRule`
and `FuzzySystem`) to implement Fuzzy Logic. This library was originally
created by the author for applying Fuzzy Logic as a control system in
embedded system (using avr microcontroller like ATmega328p etc). This
library also requires the user to play a lot with array declaration;
objects like `FuzzySet`, `FuzzyFrame` and `FuzzyRule` should be declared
as an array (for example, `FuzzySet mySet[3]`, `FuzzyRule myRule[27]`, etc).
For more details about how to use this library, please have a look on
program example that were provided by the author in this repository.

# HOW TO USE THE LIBRARY
## Declaring/Creating the Fuzzy System Objects
Is this library, setting up the Fuzzy System can be done by creating this library objects: `FuzzySet`, `FuzzyFrame`,
`FuzzyRule` and lastly `FuzzyFrame`. In general, all of the created objects (except for `FuzzyFrame`) are declared
as an array (Read the example below to setting up the fuzzy system properly). The pointer of the objects (such as pointer
to the `FuzzySet`, `FuzzyFrame`, and `FuzzyRule` object) then will be needed to set up the higher objects; For example,
the pointer to the `FuzzySet` object (as an array) must be passed as one of arguments to set up the FuzzyFrame object.
The Figure below explains the relationship between this library objects where in that figure, the system use 2 Input `FuzzyFrame` and 1 
Output `FuzzyFrame` with each of input `FuzzyFrame` consists of 3 `FuzzySet` and output `FuzzyFrame` consists of 2 `FuzzySet`. 

![Figure 1](https://github.com/BerlianOkaI/Fuzzy-Logic/blob/main/FuzzySystemDataStructure.drawio.png)

Here is the step for initializing our fuzzy system.
  
1.  **Declare** `FuzzySet` **Object as an array for both Input and Output**

      These `FuzzySet` (Mathematically denoted as $`\tilde{A}`$) are an object that represented the fuzzy subsets of certain universe of discourse $`X`$ where the certain variable $`x`$ belong to. The `FuzzySet` $`\tilde{A}`$ holds information about the degree of membership of variable $`x\in{X}`$ and that information is represented by membership function $`\mu_{\tilde{A}} (x)`$. Mathematically, the Fuzzy Set $`\tilde{A}`$ is defined as $`\tilde{A} = \{(x, \mu_{\tilde{A}}(x)) | x \in{X} \wedge \mu_{\tilde{A}}(x) \in [0, 1]\}`$. The example code below shows how to declare arrays of Fuzzy Set--subset to universe of discourse such as temperature, humidity, and heater output-- with each fuzzy set represents a set which a variable of universe of discourse belong to corresponding linguistic valuess (such as, for temperature, Cold, Cool, Hot). The membership function setting of each `FuzzySet` will be done after we declare all required objects (such as `FuzzySet`, `FuzzyFrame`, `FuzzyRule`, and `FuzzySystem`).
      ```
      /* Input or Antecedent part (Can be sensors in Instrumentation System) */
      FuzzySet Temperatures[3];        // for linguistic variable temperature, it has 3 linguistic values (3 fuzzy set for each linguistic values) such as Cold, Cool, Hot
      FuzzySet Humidity[3];            // for linguistic variable humidity, it has 3 linguistic values (3 fuzzy set for each linguistic values) such as Wet, Normal, Dry
      
      /* Output or Consequent part (Can be actuators in Instrumentation System) */
      FuzzySet Heater[2];              // for linguistic variable humidity, it has 2 linguistic values (2 fuzzy set for each linguistic values) such as Off and On
      ```
  
2.  **Declare** `FuzzyFrame` **Object as an array for both Input and Output**

      The `FuzzyFrame` is a frame of an variabel which hold a data such as linguistic values (such as Cold, Cool, Hot for temperature example above), linguistic variables, universe of discourse (such as set of Temperature, for example $`[0\degree C, 100\degree C]`$, which variable temperature belongs to), and membership function for each corresponding linguistic value/Fuzzy Set. The example below shows how to declare `FuzzyFrame` object. In this example, the term `Antecedent` refers to IF-part propotition of IF-THEN rule. In IF-THEN rule, there are other part besides the `Antecedent`, that is `Consequent` (the THEN-part). 
      ```
      FuzzyFrame Antecedent[2];        // there are 2 frame as input (antecedent) that will be evaluated in FuzzyRule. For example, it can be Temperature and Humidity
      FuzzyFrame Consequent[1];        // there is only 1 frame as output (consequent) that will be evaluated in FuzzyRule. It can be the output of our actuator in our
                                       // instrumentation system.
      ```

3.  **Declare** `FuzzyRule` **Object as an array and declare its antedent and consequent rules as 2D arrays of** `unsigned int`

      The `FuzzyRule` object is the most important object to create for creating Fuzzy Rule Base of our Fuzzy Logic System. It is represented in the form of "IF \<antecedent\> THEN \<consequent\>" where the \<antecedent\> and \<consequent\> can be a combination of atomic proposition with a connective in the form of conjunction (logical AND) or disjunction (logical OR). For example, we can create a Fuzzy Rule where the antecedent consists of 2 atomic proposition (therefore, two 'FuzzyFrame') and the consequent consists of 1 atomic proposition (therefore, one `FuzzyFrame`) such as "IF (*Temperature* is *Cold*) AND (*Humidity* is *Wet*) THEN (*Heater* is *On*)". This library only support logical connective "AND" or conjunction to form a Fuzzy Rule in Fuzzy Logic System. Therefore, to create a complete rules that map inputs to the output, we must create a number of `FuzzyRule` that depend on the number of Input Frames (Antecedent) and its corresponding linguistic values; for example, if the antedent consists of 2 atomic proposition (therefore, 2 Fuzzy Frame) with each Fuzzy Frame (therefore linguistic variable) has 3 linguistic value, then we have to define 3 x 3 Fuzzy Rules in our system. The example below shows how to declare `FuzzyRules` and its corresponding antecedent and consequent.
      ```
      FuzzyRule myRules[9];             // There are 9 rules. The number of rules depend on number of combination
                                        // of linguistic values of each linguistic variables in antecedent

      unsigned int input_rule[9][2];    // Of course there are 9 antecedent. Each antecedent consist of 2 linguistic values
                                        // of different linguistic variables to define specific "IF" part in IF-THEN rule

      unsigned int output_rule[9][1];   // Of course there are 9 consequent. Each consequent consist of 1 linguistic values
                                        // of 1 linguistic variables to define specific "THEN" part in IF-THEN rule
      ```
  
4.  **Declare** `FuzzySystem` **Object**

      `FuzzySystem` is the final object of the library that need to be declared. To declare or create `FuzzySystem` object, we have to pass the pointer to the array of `FuzzyRule` object that has been created and the number of rules that has been created (in this example, we have 3 x 3 rules). This `FuzzySystem` then will be used to compute the output of our fuzzy logic system based on the inputs and depends on our fuzzy rules and fuzzy knowledge base. The example below shows how to declare the `FuzzySystem` object.
      ```
      FuzzySystem mySystem(myRules, 9)// Declare a system that consist of 27 rule and use FuzzyRule that has been declared as argument
      ```

## Setting up the Fuzzy System Objects

After we create the `FuzzySets`, `FuzzyFrames`, and `FuzzyRules`, then we have to set up these object. This process consist
of determining the membership function of each `FuzzySet`s, Determining which `FuzzyFrame`s as
input frames (antecedent) and other one (consequent), determining IF-THEN rule for each `FuzzyRule`s
etc. For more details, please have a look on example program that were provided in this repository.

## Using It for Generating Output in Main Application Section

After we finished the initiation of fuzzy system, then we can use some method of `FuzzySystem` class to perform fuzzy operation. In general, the operation
intend to map the inputs (such as sensor datas like temperature, humidity, etc) into outputs (such as actuator output) based on the fuzzy rules and fuzzy knowledge
base in our system (Inference Mechanism). To perform the computation of the output, just pass pointer to the float array input as an argument to `FuzzySystem.Defuzzyfication(float* input, unsigned int output_id)`.

```
/* Create an input and output as float variables */
float inputs[2] = {
    27.5,        // This is dummy value for temperature input data in this example
    40.0         // This is dummy value for humidity input data in this example
};
float output;    // The variable that hold output data, in this case heater output, of our fuzzy logic system

/* Computing the output */
output = mySystem.Defuzzyfication(inputs, 0);    // First parameter is inputs pointer and second parameter is output index (if there are 2 or more output)
                                                 // For a single output, the index always be 0.
```
