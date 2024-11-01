Author          : Berlian Oka Irvianto  (Indonesia)

First Modified   : December 2023

Last Modified    : November 2024


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
`FuzzyRule` and lastly `FuzzyFrame`. In general, all of the created objects (except for `FuzzyFrame`) are usually declared
as an array (Read the example below to setting up the fuzzy system properly). The pointer of the objects (such as pointer
to the `FuzzySet`, `FuzzyFrame`, and `FuzzyRule` object) then will be needed to set up the higher objects; For example,
the pointer to the `FuzzySet` object (as an array) must be passed as one of the arguments to set up the FuzzyFrame object.
The Figure below explains the relationship between this library objects where in that figure, the system use 2 Input `FuzzyFrame` and 1 
Output `FuzzyFrame` with each input `FuzzyFrame` consists of 3 `FuzzySet` and output `FuzzyFrame` consists of 2 `FuzzySet`. 

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
      FuzzySystem mySystem(myRules, 9)        // Declare a system that consist of 27 rule and use FuzzyRule that has been declared as argument
      ```

## Setting up the Fuzzy System Objects

After we create the `FuzzySets`, `FuzzyFrames`, and `FuzzyRules`, then we have to set up these object. This process consist
of determining the membership function of each `FuzzySet`s, Determining which `FuzzyFrame`s as
input frames (antecedent) and other one (consequent), determining IF-THEN rule for each `FuzzyRule`s
etc. For more details, please have a look on example program that were provided in this repository.

The following shows how to do setup for each of created objects properly.

1.  **Create macros to define the created object arrays indexes**

      As we can see before, the created object always be in the form of array. Creating macros to define those indexes will help us to make our code easier to read and understandable. Using the previous example as reference, The macros below shows how to define the indexes.

      ```
      /* This section define index number as linguistic values of each FuzzyFrames */
      // Linguistic value of Temperature (INPUT)
      #define  COLD    0
      #define  COOL    1
      #define  HOT     2

      // Linguistic value of Humidity (INPUT)
      #define  DRY     0
      #define  NORMAL  1
      #define  WET     2

      // Linguistic value of Heater (Output)
      #define  OFF     0
      #define  ON      1

      /* This section define index number of FuzzyFrame array as identifier of each frame in array */
      // Linguistic variables of INPUT
      #define  TEMP    0
      #define  HUM     1

      // Linguistic variables of OUTPUT
      #define  HEATER  0
      ```

2.  **Setting up the created** `FuzzyFrame` **Objects**

      Setting up the `FuzzyFrame` objects intends to assign the `FuzzySet`s to each of our `FuzzyFrame`s. This can be done by passing the pointer to `FuzzySet` (array) as one of the argument of `Frame_SetUp` method
      ```
      void FuzzyFrame::Frame_SetUp(FuzzySet* sets, u_int _ling_size, float x_left, float x_right, FrameType FF_type);
      ```
      The parameter `sets` is the pointer to the `FuzzySet` of corresponding FuzzyFrame (or Linguistic Variable). `_ling_size` is the size of array of the `FuzzySet`. `x_left` and `x_right` are universe of discourse close boundaries that is needed to define the proper universe of discourse--If we want to define the universe of discourse of *Temperature* $T$ as $`T = [0\degree C, 100\degree C] `$, then we have to pass (float type data) `0.00F` and `100.0F` to `x_left` and `x_right` parameter. The `FF_type` variable is used to identify whether the frame is an `INPUT` or `OUTPUT`. The example code below shows how to setting up the frame.
      ```
      /* Setup for INPUT frames such as Temperature and Humidity */
      Antecedent[TEMP].Frame_SetUp(Temperatures, 3, 0.0F, 100.0F, INPUT);      // Using 0.0 to 100.0 degree C as Univ. of Disc.
      Antecedent[HUM].Frame_SetUp(Humidity, 3, 0.0F, 100.0F, INPUT);           // Using 0.0 to 100.0 % as Univ. of Disc.

      /* Setup for OUTPUT frames */
      Consequent[HEATER].Frame_SetUp(Heater, 2, 0.0, 100.0F, OUTPUT);          // Using 0.0 to 100.0 % as Univ. of Disc.
      
      ```

3.  **Setting up each of Fuzzy Sets of each** `FuzzyFrame`

      Setting up the Fuzzy Sets such as the membership function that will be used to define Fuzzy Sets is important in Fuzzy Inference System. This library only supports five kind of function that can be used as membership function: Singleton, Triangular, Trapezoid Left, Trapezoid Center, and Trapezoid Right. Those functions is used in this library because they are simplier and can be computed fastly compared to other function such as Sigmoid, Gaussian, etc. We can set up the fuzzy sets by calling one of `FuzzyFrame` method
      ```
      /* Select one of the following overloaded method that is appropriate with used membership function */
      void FuzzyFrame::Set_SetUp(u_int indx, FS_type the_type, float thr_1);
      void FuzzyFrame::Set_SetUp(u_int indx, FS_type the_type, float thr_1, float thr_2);
      void FuzzyFrame::Set_SetUp(u_int indx, FS_type the_type, float thr_1, float thr_2, float thr_3);
      void FuzzyFrame::Set_SetUp(u_int indx, FS_type the_type, float thr_1, float thr_2, float thr_3, float thr_4);
      ```
      `indx` variable refers to which `FuzzySets` element of the `FuzzySets` array that has been assigned that will be set up. `the_type` is the type of membership function that will be used. The threshold variables (`thr_1`, `thr_2`, etc) is used to define the shape of the membership function. The code below shows how to set up the Fuzzy Set properly.

      ```
      /* For Input Frames */
      // Temperature
      Antecedent[TEMP].Set_SetUp(COLD, TRP_L, 10.0F, 30.0F);
      Antecedent[TEMP].Set_SetUp(COOL, TRP_C, 10.0F, 30.0F, 50.0F, 70.0F);
      Antecedent[TEMP].Set_SetUp(HOT, TRP_R, 50.0F, 70.0F);

      // Humidity
      Antecedent[HUM].Set_SetUp(DRY, TRP_L, 25.0F, 50.0F);
      Antecedent[HUM].Set_SetUp(NORMAL, TRI, 25.0F, 50.0F, 75.0F);
      Antecedent[HUM].Set_SetUp(WET, TRP_R, 50.0F, 75.0F);

      /* For Output Frames */
      Consequent[HEATER].Set_SetUp(OFF, SINGLE, 0.0F);
      Consequent[HEATER].Set_SetUp(ON, SINGLE, 100.0F);
      ```

      > Make sure that before setting up the Fuzzy Sets, the `FuzzyFrame` objects has been set up properly. Do not set up the Fuzzy Sets (this step) before setting up the Fuzzy Frames (Step 2).


4.  **Setting up every** `FuzzyRule` **Objects that has been created**

      This is perhaps the most troublesome set up step. That is because the number of the rules that is need to be set up is depend on the number of combination of possible antecedent proposition that were created by conjunction (logical AND) Connective; for $`(n_{1} \times n_{2} \times n_{3} \times ...)`$ possible antecedent (with $`n`$ denotes the number of linguistic values of corresponding linguistic variables), we have to define and properly set up $`(n_{1} \times n_{2} \times n_{3} \times ...)`$ Fuzzy Rules! For our examples, we need to define $3 \times 3$ Fuzzy Rules to create our Fuzzy Inference System.

      The setup can be done by calling method `Rule_SetUp` and configuring the corresponding `unsigned int` array of antecedent and consequent that has been created before.

      ```
      /* Method that has to be called to setup the rules */
      void FuzzyRule::Rule_SetUp(FuzzyFrame* input_frames, u_int* input_rules, u_int FR_input_size, FuzzyFrame* output_frames, u_int* output_rules, u_int FR_output_size);
      ```
      -  `input_frames` is pointer to the array of `FuzzyFrame` Inputs;
      -  `input_rules` is pointer to the array (1D, array for corresponding rules only) of antecedent rule;
      -  `FR_input_size` is the number of input linguistic variables (i.e. the number of Input Fuzzy Frame);
      -  `output_frames` is pointer to the array of `FuzzyFrame` Outputs;
      -  `output_rules` is pointer to the array (1D, array for corresponding rules only) of consequent rule;
      -  `FR_output_size` is the number of output linguistic variables (i.e. the number of Output Fuzzy Frame)
  
      The example code below shows how to defines each of `FuzzyRule`

      ```
      // Rule 0
      myRules[0].Rule_SetUp(Antecedent, input_rule[0], 2, Consequent, output_rule[0], 1);
      input_rule[0][TEMP] = COLD;    input_rule[0][HUM] = DRY;
      output_rule[0][HEATER] = ON;
      // Rule 1
      ...
      ...
      // Rule 8
      myRules[8].Rule_SetUp(Antecedent, input_rule[8], 2, Consequent, output_rule[8], 1);
      input_rule[8][TEMP] = COLD;    input_rule[8][HUM] = DRY;
      output_rule[8][HEATER] = OFF;
      ```
      
## Using It for Generating Output in Main Application Section

After we finished the initiation of fuzzy system, then we can use some method of `FuzzySystem` class to perform fuzzy operation. In general, the operation
intend to map the inputs (such as sensor datas like temperature, humidity, etc) into outputs (such as actuator output) based on the fuzzy rules and fuzzy knowledge
base in our system (Inference Mechanism). To perform the computation of the output, just pass pointer to the float array input as an argument to `void FuzzySystem::Defuzzyfication(float* input, unsigned int output_id)`.

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
