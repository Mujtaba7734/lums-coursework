#ifndef SEHRILAB_HPP
#define SEHRILAB_HPP

#include <string>
using namespace std;

// ------------------------------
// SehriItem (Base Class)
// ------------------------------
class SehriItem
{
protected:
    int id;
    string name;
    float baseCost;

public:
    SehriItem();
    SehriItem(int id, string name, float baseCost);
    SehriItem(const SehriItem &other);

    virtual void displayDetails();
    float getBaseCost();
    string getName();
    virtual float calculateDiscount(int quantity);
    virtual ~SehriItem() {}
};

// ------------------------------
// Paratha Class (Derived from SehriItem)
// ------------------------------
class Paratha : public SehriItem
{
private:
    string stuffingType;
    int spiceLevel;
    float oil;

public:
    Paratha();
    Paratha(int id, string stuffingType, float baseCost, int spiceLevel, float oil);
    Paratha(const Paratha &other);

    void displayDetails() override;
    float calculateDiscount();
    int getSpiceLevel();
    string getStuffingType();
    float getOil();
};

// ------------------------------
// Chai Class (Derived from SehriItem)
// ------------------------------
class Chai : protected SehriItem
{
private:
    int sugarAmount;
    string chaiType;

public:
    Chai();
    Chai(int id, float baseCost, int sugarAmount, string chaiType);
    Chai(const Chai &other);

    void displayDetails();
    float calculateDiscount();
    int getSugarAmount();
    string getChaiType();
    string getName();
    float getBaseCost();
};

// ------------------------------
// SehriFoodCounter (Management Class)
// ------------------------------
class SehriFoodCounter
{
private:
    Paratha *parathas[10];
    int parathaCount;
    Chai *chais[10];
    int chaiCount;

public:
    SehriFoodCounter();
    SehriFoodCounter(const SehriFoodCounter &other);

    void addParatha(int id, string stuffingType, float baseCost, int spiceLevel, float oil);
    void addChai(int id, float baseCost, int sugarAmount, string chaiType);
    void getParathas(Paratha *actualParathas[], int &count) const;
    void getChais(Chai *actualChais[], int &count) const;
    Paratha *findSpiciestParatha();
    string getMostOrderedParathaType();
    Paratha *getParathaWithMaxOil();
    string getMostOrderedChaiType();
    Chai **getMostSugaryChai(int &count);
    float calculateTotalBill();
    void displayParathas();
    void displayChais();
    ~SehriFoodCounter();
};

#endif
