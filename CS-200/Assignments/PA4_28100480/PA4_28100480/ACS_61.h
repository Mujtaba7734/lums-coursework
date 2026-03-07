#ifndef ACS_61_H
#define ACS_61_H

#include <iostream>
#include <string>
using namespace std;
/* 
Include only ATTRIBUTES and FUNCTION SIGNATURES for each class in this file. 
Code for each method must be in ACS_61.cpp 
i.e.
class Aeroplane {
    private:
        string name;
    public:
        string get_name();
};
*/

enum class AircraftStatus {
    OnGround,
    Airborne,
    Crashed
};

ostream& operator<<(ostream& os, const AircraftStatus& status);

// BASE CLASS
class Aircraft {
    private:
        string identifier;
        int fuel_level;
        int health;
        AircraftStatus current_status;

    public:
    Aircraft();
    Aircraft(string identifier, int fuel_level, int health, AircraftStatus current_status);
    Aircraft(const Aircraft &other);
    string getIdentifier() const;
    int getFuelLevel() const;
    int getHealth() const;
    AircraftStatus getCurrentStatus() const;

    void setFuelLevel(int fuel);
    void setHealth(int health);
    void setCurrentStatus(AircraftStatus status);

    virtual void takeOff();
    virtual void land();

    Aircraft& operator+=(const int number);
    Aircraft& operator-=(const int number);

    bool operator==(const Aircraft& other) const;
    friend ostream& operator<<(ostream& os, Aircraft& aircraft);
    virtual void print(ostream& os);
    friend istream& operator>>(istream& in, Aircraft& aircraft);

};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft: virtual public Aircraft{
    private:
        string weapon_type;
        int weapon_count;
        int weapon_strength;
    //

    public:
        CombatAircraft();
        CombatAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, string weapon_type, int weapon_count, int weapon_strength);
        CombatAircraft(const CombatAircraft &other);
        string getWeaponType() const;

        int getWeaponCount() const;
        int getWeaponStrength() const;
        void setWeaponCount(int count);
        
        CombatAircraft operator++(int);
        CombatAircraft operator--();
        void print(ostream &os) override;
};

class StealthAircraft: virtual public Aircraft 
{
    private:
        bool cloak_status;
    //
    public:
        StealthAircraft();
        StealthAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, bool cloak_status);
        StealthAircraft(const StealthAircraft &other);
        bool getCloakStatus() const;
        void activateCloak();
        void deactivateCloak();
        void takeOff() override;  
        void land() override;   
        
        StealthAircraft& operator!();
        void print(ostream &os) override;
};

class AbductorCraft: public StealthAircraft {
    private:
        int abductee_count;
        int abductee_capacity;    
    //

    public:
        AbductorCraft();
        AbductorCraft(string identifier, int fuel_level, int health, AircraftStatus current_status, bool cloak_status, int abductee_count, int abductee_capacity);
        AbductorCraft(const AbductorCraft &other);
        int getAbducteeCount() const;
        int getAbducteeCapacity() const;
        void setAbducteeCount(int count);

        bool operator>(const AbductorCraft &other);
        AbductorCraft& operator+=(const int count);
        AbductorCraft& operator-=(const int count);
        AbductorCraft& operator&(AbductorCraft &other);
        void print(ostream &os) override;
};

class GuardianCraft: public CombatAircraft, public StealthAircraft 
{
    private:
        int kill_count;
    //
    public:
        GuardianCraft();
        GuardianCraft(string identifier, int fuel_level, int health, AircraftStatus current_status, string weapon_type, int weapon_count, int weapon_strength, bool cloak_status, int kill_count);
        GuardianCraft(const GuardianCraft &other);
        int getKillCount() const;

        GuardianCraft operator++(int dummy);
        GuardianCraft operator--();

        bool operator*=(const AbductorCraft &other);
        GuardianCraft& operator*(AbductorCraft &other);
        void print(ostream &os) override;
};

#endif