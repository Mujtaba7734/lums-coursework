#include <stdio.h>

// ----------------- Recursive Function Implementations ----------------- //

// Recursive Function to count the number of digits in n
int countDigits(int n)
{
    if (n < 10)
    {
        return 1;
    }
    else
    {
        return  1+ countDigits(n/10);
    }
    // complete this function
}

// Recursive Function to calculate power: returns n^exp
int calPower(int n, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    else
    {
        return n * calPower(n, exp - 1);
    }
   
}

// Recursive Function to calculate the sum of digits raised to power numDigits
int sumOfPowers(int n, int numDigits)
{
    if (n < 10)
    {
        return calPower(n, numDigits);
    }
    else
    {
        return calPower(n%10, numDigits) + sumOfPowers(n/10, numDigits);
    }
}

// ----------------- Armstrong Number Check ----------------- //

// Function to check if a number is Armstrong
int isArmstrong(int n)
{
    if (n < 0)
        return 0;

    int numDigits = countDigits(n);
    int sum = sumOfPowers(n, numDigits);

    return sum == n ? 1 : 0;
}

// ----------------- Armstrong Tests (30 Marks Total) ----------------- //

float ARM_MARKS_PER_TEST = 3.0; // 10 tests * 3 marks = 30 marks

// Function to detect trivial (always 0 or 1) outputs
int isTrivialOutput()
{
    int results[5];
    results[0] = isArmstrong(0);
    results[1] = isArmstrong(1);
    results[2] = isArmstrong(153);
    results[3] = isArmstrong(370);
    results[4] = isArmstrong(100);

    // Check if all outputs are the same (either all 0 or all 1)
    for (int i = 1; i < 5; i++)
    {
        if (results[i] != results[0])
        {
            return 0; // Not trivial
        }
    }
    return 1; // Trivial output detected
}

float runArmstrongTest(int testNum, int input, int expected)
{
    int result = isArmstrong(input);

    // Detect trivial outputs
    if (isTrivialOutput())
    {
        printf("Armstrong Test %d Failed (Input: %d) | Trivial Output Detected - Expected: %s, Got: %s - Earned: 0 marks\n",
               testNum, input, expected ? "Armstrong" : "Not Armstrong", result ? "Armstrong" : "Not Armstrong");
        return 0.0;
    }

    // Specific Check: Ensure Test 2 (input: 1) only passes if implemented correctly
    if (input == 1 && result == 1 && isArmstrong(153) == 0)
    {
        printf("Armstrong Test %d Failed (Input: %d) | Case 1 Passed Without Proper Implementation - Expected: %s, Got: %s - Earned: 0 marks\n",
               testNum, input, expected ? "Armstrong" : "Not Armstrong", result ? "Armstrong" : "Not Armstrong");
        return 0.0;
    }

    // Award marks if result matches expected
    if (result == expected)
    {
        printf("Armstrong Test %d Passed (Input: %d) | Expected: %s, Got: %s - Earned: %.2f marks\n",
               testNum, input, expected ? "Armstrong" : "Not Armstrong", result ? "Armstrong" : "Not Armstrong", ARM_MARKS_PER_TEST);
        return ARM_MARKS_PER_TEST;
    }
    else
    {
        printf("Armstrong Test %d Failed (Input: %d) | Expected: %s, Got: %s - Earned: 0 marks\n",
               testNum, input, expected ? "Armstrong" : "Not Armstrong", result ? "Armstrong" : "Not Armstrong");
        return 0.0;
    }
}

float runArmstrongTests()
{
    float totalMarks = 0.0;

    printf("\n--- Running Armstrong Tests ---\n");
    totalMarks += runArmstrongTest(1, 0, 1);
    totalMarks += runArmstrongTest(2, 1, 1);
    totalMarks += runArmstrongTest(3, 153, 1);
    totalMarks += runArmstrongTest(4, 370, 1);
    totalMarks += runArmstrongTest(5, 371, 1);
    totalMarks += runArmstrongTest(6, 407, 1);
    totalMarks += runArmstrongTest(7, 9474, 1);
    totalMarks += runArmstrongTest(8, 100, 0);
    totalMarks += runArmstrongTest(9, 123, 0);
    totalMarks += runArmstrongTest(10, -153, 0);

    printf("\nArmstrong Tests Completed. Marks Earned: %.2f / 30\n", totalMarks);
    return totalMarks;
}

// ----------------- Helper Function Tests (10 Marks Total) ----------------- //

// Test suite for countDigits (2 marks total)
float runCountDigitsTests()
{
    float marks = 0.0;
    int result;

    printf("\n--- Running countDigits Tests ---\n");
    
    result = countDigits(0);
    if(result == 1){
        printf("countDigits(0): Passed | Expected: 1, Got: %d (1 mark)\n", result);
        marks += 1.0;
    } else {
        printf("countDigits(0): Failed | Expected: 1, Got: %d (0 mark)\n", result);
    }

    result = countDigits(153);
    if(result == 3){
        printf("countDigits(153): Passed | Expected: 3, Got: %d (1 mark)\n", result);
        marks += 1.0;
    } else {
        printf("countDigits(153): Failed | Expected: 3, Got: %d (0 mark)\n", result);
    }

    printf("countDigits Tests: Earned %.2f / 2 marks\n", marks);
    return marks;
}

// Test suite for calPower (4 marks total)
float runCalPowerTests()
{
    float marks = 0.0;
    int result;

    printf("\n--- Running calPower Tests ---\n");
    
    result = calPower(2, 3);
    if(result == 8){
        printf("calPower(2, 3): Passed | Expected: 8, Got: %d (2 marks)\n", result);
        marks += 2.0;
    } else {
        printf("calPower(2, 3): Failed | Expected: 8, Got: %d (0 mark)\n", result);
    }

    result = calPower(5, 0);
    if(result == 1){
        printf("calPower(5, 0): Passed | Expected: 1, Got: %d (2 marks)\n", result);
        marks += 2.0;
    } else {
        printf("calPower(5, 0): Failed | Expected: 1, Got: %d (0 mark)\n", result);
    }

    printf("calPower Tests: Earned %.2f / 4 marks\n", marks);
    return marks;
}

// Test suite for sumOfPowers (4 marks total)
float runSumOfPowersTests()
{
    float marks = 0.0;
    int result;

    printf("\n--- Running sumOfPowers Tests ---\n");
    
    result = sumOfPowers(153, 3);
    if(result == 153){
        printf("sumOfPowers(153, 3): Passed | Expected: 153, Got: %d (2 marks)\n", result);
        marks += 2.0;
    } else {
        printf("sumOfPowers(153, 3): Failed | Expected: 153, Got: %d (0 mark)\n", result);
    }

    result = sumOfPowers(9474, 4);
    if(result == 9474){
        printf("sumOfPowers(9474, 4): Passed | Expected: 9474, Got: %d (2 marks)\n", result);
        marks += 2.0;
    } else {
        printf("sumOfPowers(9474, 4): Failed | Expected: 9474, Got: %d (0 mark)\n", result);
    }

    printf("sumOfPowers Tests: Earned %.2f / 4 marks\n", marks);
    return marks;
}

// Combine all helper tests
float runHelperTests()
{
    float total = 0.0;
    total += runCountDigitsTests();
    total += runCalPowerTests();
    total += runSumOfPowersTests();
    printf("\nHelper Functions Tests Completed. Marks Earned: %.2f / 10\n", total);
    return total;
}

// ----------------- Main Function ----------------- //

int main()
{
    float armstrongMarks = runArmstrongTests();   // 30 marks total
    float helperMarks = runHelperTests();           // 10 marks total

    float totalMarks = armstrongMarks + helperMarks;
    printf("\n======================================\n");
    printf("Overall Total Marks Earned: %.2f / 40\n", totalMarks);
    printf("======================================\n");

    return 0;
}
