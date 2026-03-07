#include <iostream>
#include <string>
#include <exception>
#include <cmath>
#include "SehriLab.hpp"
using namespace std;

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

bool testResult = true;

int main()
{
    float marks = 0.0;
    cout << BLUE << "Running Tests for Sehri Food Management System..." << RESET << endl;

    auto approxEqual = [](float a, float b, float epsilon = 0.001f)
    {
        return fabs(a - b) < epsilon;
    };

    // Test 1: Basic SehriItem Creation (5 Marks)
    try
    {
        cout << BLUE << "Test 1: Basic SehriItem Creation (5 Marks)" << RESET << endl;
        SehriItem basicItem(1, "Basic Item", 10.0);
        basicItem.displayDetails();
        cout << GREEN << "Basic SehriItem creation passed." << RESET << endl;
        marks += 5;
    }
    catch (exception &e)
    {
        cout << RED << "Test 1 failed with exception: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 2: Paratha Functionality and Discount Calculation (10 Marks)
    try
    {
        cout << BLUE << "Test 2: Paratha Functionality (10 Marks)" << RESET << endl;
        Paratha paratha(2, "Aloo", 3.5, 8, 0.5);
        paratha.displayDetails();
        float discountPrice = paratha.calculateDiscount();
        if (!approxEqual(discountPrice, 3.15f))
        {
            throw runtime_error("Discount calculation error for Paratha. Expected 3.15, got " + to_string(discountPrice));
        }
        cout << GREEN << "Paratha functionality passed." << RESET << endl;
        marks += 10;
    }
    catch (exception &e)
    {
        cout << RED << "Test 2 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 3: Chai Functionality and Discount Calculation (10 Marks)
    try
    {
        cout << BLUE << "Test 3: Chai Functionality (10 Marks)" << RESET << endl;
        Chai chai(3, 2.2, 20, "Ilaichi");
        chai.displayDetails();
        float discountPrice = chai.calculateDiscount();
        if (!approxEqual(discountPrice, 2.09f))
        {
            throw runtime_error("Discount calculation error for Chai. Expected 2.09, got " + to_string(discountPrice));
        }
        cout << GREEN << "Chai functionality passed." << RESET << endl;
        marks += 10;
    }
    catch (exception &e)
    {
        cout << RED << "Test 3 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 4: SehriFoodCounter - Adding and Displaying Items (15 Marks)
    try
    {
        cout << BLUE << "Test 4: SehriFoodCounter Adding and Displaying Items (15 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addParatha(1, "Aloo", 3.5, 7, 0.5);
        counter.addParatha(2, "Chicken", 4.0, 9, 0.6);
        counter.addParatha(3, "Mixed Veg", 3.8, 7, 0.55);
        counter.addParatha(4, "Lentil", 3.6, 6, 0.5);
        counter.addParatha(5, "Paneer", 4.2, 8, 0.65);
        counter.addChai(6, 2.0, 3, "Masala");
        counter.addChai(7, 2.2, 2, "Ilaichi");
        counter.addChai(8, 2.5, 4, "Masala");
        counter.addChai(9, 2.1, 2, "Masala");
        counter.addChai(10, 2.3, 3, "Ilaichi");

        Paratha *actualParathas[10];
        int parathaCount = 0;
        counter.getParathas(actualParathas, parathaCount);
        if (parathaCount != 5)
            throw runtime_error("Paratha count mismatch.");
        int expectedSpiceLevels[5] = {7, 9, 7, 6, 8};
        float expectedBaseCosts[5] = {3.5, 4.0, 3.8, 3.6, 4.2};
        for (int i = 0; i < parathaCount; i++)
        {
            if (actualParathas[i]->getSpiceLevel() != expectedSpiceLevels[i])
            {
                throw runtime_error("Paratha spice level mismatch at index " + to_string(i));
            }
            if (!approxEqual(actualParathas[i]->getBaseCost(), expectedBaseCosts[i]))
            {
                throw runtime_error("Paratha base cost mismatch at index " + to_string(i));
            }
            if (actualParathas[i]->getName() != "Paratha")
            {
                throw runtime_error("Paratha name mismatch at index " + to_string(i));
            }
        }
        Chai *actualChais[10];
        int chaiCount = 0;
        counter.getChais(actualChais, chaiCount);
        if (chaiCount != 5)
            throw runtime_error("Chai count mismatch.");
        int expectedSugarAmounts[5] = {3, 2, 4, 2, 3};
        float expectedChaiBaseCosts[5] = {2.0, 2.2, 2.5, 2.1, 2.3};
        for (int i = 0; i < chaiCount; i++)
        {
            if (actualChais[i]->getSugarAmount() != expectedSugarAmounts[i])
            {
                throw runtime_error("Chai sugar amount mismatch at index " + to_string(i));
            }
            if (!approxEqual(actualChais[i]->getBaseCost(), expectedChaiBaseCosts[i]))
            {
                throw runtime_error("Chai base cost mismatch at index " + to_string(i));
            }
            if (actualChais[i]->getName() != "Chai")
            {
                throw runtime_error("Chai name mismatch at index " + to_string(i));
            }
        }
        cout << GREEN << "SehriFoodCounter addition and display tests passed." << RESET << endl;
        marks += 15;
    }
    catch (exception &e)
    {
        cout << RED << "Test 4 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 6: Most Sugary Chai (10 Marks)
    try
    {
        cout << BLUE << "Test 6: Most Sugary Chai (10 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addChai(13, 2.3, 4, "Masala");
        counter.addChai(14, 2.1, 2, "Masala");
        counter.addChai(15, 2.5, 4, "Ilaichi");
        int count = 0;
        Chai **maxChais = counter.getMostSugaryChai(count);
        if (count != 2)
        {
            throw runtime_error("Expected 2 Chai objects with maximum sugar (4 tsp), got " + to_string(count));
        }
        for (int i = 0; i < count; i++)
        {
            if (maxChais[i]->getSugarAmount() != 4)
            {
                throw runtime_error("Chai maximum sugar amount mismatch at index " + to_string(i));
            }
        }
        for (int i = 0; i < count; i++)
        {
            delete maxChais[i];
        }
        delete[] maxChais;
        cout << GREEN << "Most Sugary Chai test passed." << RESET << endl;
        marks += 10;
    }
    catch (exception &e)
    {
        cout << RED << "Test 6 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 7: Finding the Spiciest Paratha (8 Marks)
    try
    {
        cout << BLUE << "Test 7: Finding the Spiciest Paratha (8 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addParatha(15, "Aloo", 3.5, 5, 0.5);
        counter.addParatha(16, "Chicken", 4.0, 8, 0.6);
        counter.addParatha(17, "Mixed Veg", 3.8, 7, 0.55);
        counter.addParatha(18, "Lentil", 3.6, 6, 0.5);
        counter.addParatha(19, "Paneer", 4.2, 9, 0.65);
        Paratha *spiciest = counter.findSpiciestParatha();
        if (spiciest == nullptr)
        {
            throw runtime_error("findSpiciestParatha returned nullptr.");
        }
        if (spiciest->getSpiceLevel() != 9)
        {
            throw runtime_error("findSpiciestParatha did not return the paratha with highest spice level.");
        }
        cout << GREEN << "findSpiciestParatha test passed." << RESET << endl;
        marks += 8;
    }
    catch (exception &e)
    {
        cout << RED << "Test 7 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 8: Additional Spiciest Paratha Test (8 Marks)
    try
    {
        cout << BLUE << "Test 8: Additional Spiciest Paratha Test (8 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addParatha(20, "Spinach", 3.0, 4, 0.4);
        counter.addParatha(21, "Corn", 3.2, 6, 0.45);
        counter.addParatha(22, "Mushroom", 3.4, 10, 0.5);
        counter.addParatha(23, "Cheese", 3.6, 8, 0.55);
        Paratha *spiciest = counter.findSpiciestParatha();
        if (spiciest == nullptr)
        {
            throw runtime_error("Additional spiciest paratha test: function returned nullptr.");
        }
        if (spiciest->getSpiceLevel() != 10)
        {
            throw runtime_error("Additional spiciest paratha test: expected spice level 10, got " + to_string(spiciest->getSpiceLevel()));
        }
        cout << GREEN << "Additional spiciest paratha test passed." << RESET << endl;
        marks += 8;
    }
    catch (exception &e)
    {
        cout << RED << "Test 8 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 9: Additional Most Sugary Chai Test (8 Marks)
    try
    {
        cout << BLUE << "Test 9: Additional Most Sugary Chai Test (8 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addChai(24, 2.4, 5, "Masala");
        counter.addChai(25, 2.0, 3, "Masala");
        counter.addChai(26, 2.6, 5, "Ilaichi");
        counter.addChai(27, 2.3, 4, "Masala");
        int count = 0;
        Chai **maxChais = counter.getMostSugaryChai(count);
        if (count != 2)
        {
            throw runtime_error("Additional test: Expected 2 Chai objects with maximum sugar (5 tsp), got " + to_string(count));
        }
        for (int i = 0; i < count; i++)
        {
            if (maxChais[i]->getSugarAmount() != 5)
            {
                throw runtime_error("Additional test: Chai maximum sugar amount mismatch at index " + to_string(i));
            }
        }
        for (int i = 0; i < count; i++)
        {
            delete maxChais[i];
        }
        delete[] maxChais;
        cout << GREEN << "Additional most sugary Chai test passed." << RESET << endl;
        marks += 8;
    }
    catch (exception &e)
    {
        cout << RED << "Test 9 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 10: Most Ordered Paratha and Maximum Oil (8 Marks)
    try
    {
        cout << BLUE << "Test 10: Most Ordered Paratha and Maximum Oil (8 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addParatha(1, "Aloo", 3.5, 7, 0.5);
        counter.addParatha(2, "Chicken", 4.0, 9, 0.6);
        counter.addParatha(3, "Aloo", 3.8, 7, 0.55);
        counter.addParatha(4, "Lentil", 3.6, 6, 0.5);
        counter.addParatha(5, "Aloo", 4.2, 8, 0.65);
        string mostOrdered = counter.getMostOrderedParathaType();
        if (mostOrdered != "Aloo")
        {
            throw runtime_error("Expected most ordered paratha type to be Aloo, got " + mostOrdered);
        }
        Paratha *maxOilParatha = counter.getParathaWithMaxOil();
        if (maxOilParatha == nullptr || maxOilParatha->getOil() != 0.65f)
        {
            throw runtime_error("Expected paratha with max oil to have 0.65 oil.");
        }
        cout << GREEN << "Test 10 passed." << RESET << endl;
        marks += 8;
    }
    catch (exception &e)
    {
        cout << RED << "Test 10 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 11: Most Ordered Chai Type (8 Marks)
    try
    {
        cout << BLUE << "Test 11: Most Ordered Chai Type (8 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addChai(6, 2.0, 3, "Masala");
        counter.addChai(7, 2.2, 2, "Ilaichi");
        counter.addChai(8, 2.5, 4, "Ilaichi");
        string mostOrderedChai = counter.getMostOrderedChaiType();
        if (mostOrderedChai != "Ilaichi")
        {
            throw runtime_error("Expected most ordered chai type to be Ilaichi, got " + mostOrderedChai);
        }
        cout << GREEN << "Test 11 passed." << RESET << endl;
        marks += 8;
    }
    catch (exception &e)
    {
        cout << RED << "Test 11 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    // Test 12: Total Bill Calculation (10 Marks)
    try
    {
        cout << BLUE << "Test 12: Total Bill Calculation (10 Marks)" << RESET << endl;
        SehriFoodCounter counter;
        counter.addParatha(1, "Aloo", 3.5, 7, 0.5);
        counter.addParatha(2, "Chicken", 4.0, 9, 0.6);
        counter.addChai(3, 2.2, 20, "Ilaichi");
        counter.addChai(4, 2.0, 10, "Masala");
        float totalBill = counter.calculateTotalBill();
        float expectedBill = 3.15f + 4.0f + 2.09f + 2.0f;
        if (!approxEqual(totalBill, expectedBill))
        {
            throw runtime_error("Expected total bill " + to_string(expectedBill) + ", got " + to_string(totalBill));
        }
        cout << GREEN << "Test 12 passed." << RESET << endl;
        marks += 10;
    }
    catch (exception &e)
    {
        cout << RED << "Test 12 failed: " << e.what() << RESET << endl;
        testResult = false;
    }
    cout << endl;

    cout << BLUE << "TOTAL MARKS: " << marks << "/100" << RESET << endl;
    return 0;
}
