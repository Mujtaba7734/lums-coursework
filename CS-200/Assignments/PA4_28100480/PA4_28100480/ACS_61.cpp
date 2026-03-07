#include "ACS_61.h"

/* 
Implement all class methods here.
i.e.
string Aeroplane::get_name() {
    return this->name;
}
*/


// Aircraft methods
Aircraft::Aircraft()
{
    identifier = "";
    fuel_level = 100;
    health = 100;
    current_status = AircraftStatus::OnGround;
}

Aircraft::Aircraft(string identifier, int fuel_level, int health, AircraftStatus current_status)
{
    this->identifier = identifier;
    this->fuel_level = fuel_level;
    this->health = health;
    this->current_status = current_status;

    if (this->fuel_level <= 0)
    {
        this->fuel_level = 0;
    }
    if (this->fuel_level > 100)
    {
        this->fuel_level = 100;
    }
    if (this->health < 0)
    {   
        cout << "Check" << endl;

        this->health = 0;
    } 
    
    if (this->health > 100)
    {
        this->health = 100;
    }

    if (this->current_status == AircraftStatus::Airborne)
    {
        if (this->fuel_level == 0 || this->health == 0)
        {
            this->current_status = AircraftStatus::Crashed;
            this->health = 0;
        }
    }

    if (this->health == 0)
    {
        this->current_status = AircraftStatus::Crashed;
    }
    
}


Aircraft::Aircraft(const Aircraft &other)
{
    this->identifier = other.identifier;
    if (other.fuel_level <= 0)
    {
        this->fuel_level = 0;
    }
    else
    {
        this->fuel_level = other.fuel_level;
    }
    this->health = other.health;
    this->current_status = other.current_status;
    
    if (this->fuel_level <= 0)
    {
        this->fuel_level = 0;
    }
    if (this->fuel_level > 100)
    {
        this->fuel_level = 100;
    }
    if (this->health < 0)
    {
        this->health = 0;
    } 
    if (this->health > 100)
    {
        this->health = 100;
    }

    if (this->health == 0)
    {
        this->current_status = AircraftStatus::Crashed;
    }

    if (this->current_status == AircraftStatus::Airborne)
    {
        if (this->fuel_level == 0 || this->health == 0)
        {
            this->current_status = AircraftStatus::Crashed;
            this->health = 0;
        }
    }
    
}

string Aircraft::getIdentifier() const
{
    return identifier;
}

int Aircraft::getFuelLevel() const
{
    return fuel_level;
}

int Aircraft::getHealth() const
{
    return health;
}

AircraftStatus Aircraft::getCurrentStatus() const
{
    return current_status;
}

void Aircraft::setFuelLevel(int fuel)
{
    this->fuel_level += fuel;
    if (this->fuel_level <= 0)
    {
        this->fuel_level = 0;
    }
    if (this->fuel_level > 100)
    {
        this->fuel_level = 100;
    }
}

void Aircraft::setHealth(int health)
{
    this->health += health;
    if (this->health < 0)
    {
        this->health = 0;
    }
    if (this->health > 100)
    {
        this->health = 100;
    }
}

void Aircraft::setCurrentStatus(AircraftStatus status)
{
    this->current_status = status;
}

void Aircraft::takeOff()
{
    if (fuel_level >= 30 && current_status == AircraftStatus::OnGround)
    {
        current_status = AircraftStatus::Airborne;
    }
}

void Aircraft::land()
{
    if (current_status == AircraftStatus::Airborne)
    {
        current_status = AircraftStatus::OnGround;
    }
}


Aircraft& Aircraft::operator+=(const int number)
{
    if (current_status == AircraftStatus::OnGround)
    {
        fuel_level+= number;
        if (fuel_level > 100)
        {
            fuel_level = 100;
        }
    }
    return *this;
}

Aircraft& Aircraft::operator-=(const int number)
{
    
    if (current_status == AircraftStatus::OnGround)
    {
        cout << "if condition" << endl;
        fuel_level-= number;
        if (fuel_level < 0)
        {
            fuel_level = 0;
        }
    }
    return *this;
}

bool Aircraft::operator==(const Aircraft&other) const
{
    if (this->identifier == other.identifier && this->health == other.health && this->fuel_level == other.fuel_level && this->current_status == other.current_status ) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Aircraft::print(ostream& os)
{
    os << "Identifier: " << identifier << endl;
    os << "Fuel Level: " << fuel_level << "%" << endl;
    os << "Health: " << health << "%"  << endl;
    os << "Current Status: " << current_status << endl;
}

ostream& operator<<(ostream& os, Aircraft& aircraft)
{
    // os << "Identifier: " << aircraft.identifier << endl;
    // os << "Fuel Level: " << aircraft.fuel_level << "%" << endl;
    // os << "Health: " << aircraft.health << "%"  << endl;
    // os << "Current Status: " << aircraft.current_status << endl;
    aircraft.print(os);
    return os;
}

istream& operator>>(istream& in, Aircraft& aircraft) 
{
    int status;
    cout << "Enter Identifier: ";
    in >> aircraft.identifier;
    cout << "Enter fuel level: ";
    in >> aircraft.fuel_level;
    cout << "Enter health: ";
    in >> aircraft.health;
    cout << "Enter Status (0: OnGround, 1: Airborne, 2: Crashed): ";
    in >> status;
    if (status == 0)
    {
        aircraft.current_status = AircraftStatus::OnGround;
    }
    if (status == 1)
    {
        aircraft.current_status = AircraftStatus::Airborne;
    }
    if (status == 2)
    {
        aircraft.current_status = AircraftStatus::Crashed;
    } 
    return in;
}


// CombatAircraft methods

CombatAircraft::CombatAircraft(): Aircraft()
{
    weapon_type = "";
    weapon_count = 0;
    weapon_strength = 0;
}

CombatAircraft::CombatAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, string weapon_type, int weapon_count, int weapon_strength)
                                : Aircraft(identifier, fuel_level, health, current_status)
{
    this->weapon_type = weapon_type;
    this->weapon_count = weapon_count;
    this->weapon_strength = weapon_strength;
    if (this->weapon_count < 0)
    {
        this->weapon_count = 0;
    }
    if (this->weapon_strength < 0)
    {
        this->weapon_strength = 0;
    }
    if (this->weapon_strength > 100)
    {
        this->weapon_strength = 100;
    }
}

CombatAircraft::CombatAircraft(const CombatAircraft &other) : Aircraft(other)
{   
    this->weapon_type = other.weapon_type;
    this->weapon_count = other.weapon_count;
    this->weapon_strength = other.weapon_strength;
    if (this->weapon_count < 0)
    {
        this->weapon_count = 0;
    }
    if (this->weapon_strength < 0)
    {
        this->weapon_strength = 0;
    }
    if (this->weapon_strength > 100)
    {
        this->weapon_strength = 100;
    }
}

string CombatAircraft::getWeaponType() const
{
    return weapon_type;
}

int CombatAircraft::getWeaponCount() const
{
    return weapon_count;
}

int CombatAircraft::getWeaponStrength() const
{
    return weapon_strength;
}

void CombatAircraft::setWeaponCount(int count)
{
    weapon_count+= count;
}

CombatAircraft CombatAircraft::operator++(int)
{
    CombatAircraft temp = *this; 
    if (getCurrentStatus() == AircraftStatus::OnGround)
    {
        weapon_count++;
    }
    return temp;
}

CombatAircraft CombatAircraft::operator--()
{
    if (getCurrentStatus() == AircraftStatus::OnGround && weapon_count > 0)
    {
        weapon_count--;
    }
    return *this;
}

void CombatAircraft::print(ostream& os)
{
    Aircraft::print(os);
    os << "Weapon Type: " << weapon_type << endl;
    os << "Weapon Count: " << weapon_count << endl;
    os << "Weapon Strength: " << weapon_strength << endl;
}

// StealthAircraft methods

StealthAircraft::StealthAircraft(): Aircraft()
{
    cloak_status = false;
}

StealthAircraft::StealthAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, bool cloak_status)
                                : Aircraft(identifier, fuel_level, health, current_status)
{
    if (getCurrentStatus() == AircraftStatus::Airborne)
    {
        this->cloak_status = cloak_status;
    }
    else
    {
        this->cloak_status = false;
    }
}

StealthAircraft::StealthAircraft(const StealthAircraft &other) : Aircraft(other)
{   
    if (this->getCurrentStatus() == AircraftStatus::Airborne)
    {
        this->cloak_status = other.cloak_status;
    }
    else
    {
        this->cloak_status = false;
    }

}

bool StealthAircraft::getCloakStatus() const
{
    return cloak_status;
}

void StealthAircraft::activateCloak()
{
    if (cloak_status == false && getCurrentStatus() == AircraftStatus::Airborne)  
    {
        setHealth(-10);
        if (getHealth() == 0)
        {
            setCurrentStatus(AircraftStatus::Crashed);
            return;
        }
        setFuelLevel(-15);
        if (getFuelLevel() == 0)
        {
            setCurrentStatus(AircraftStatus::Crashed);
            setHealth(-100);
            return;
        }
        cloak_status = true;
        
    }
}

void StealthAircraft::deactivateCloak()
{
    cloak_status = false;   
}

void StealthAircraft::takeOff() 
{
    deactivateCloak();
    Aircraft::takeOff();
}

void StealthAircraft::land()
{
    deactivateCloak();
    Aircraft::land();
}

StealthAircraft& StealthAircraft::operator!()
{
    if (cloak_status == true)
    {
        deactivateCloak();
    }
    if (cloak_status == false)
    {
        activateCloak();
    }

    return *this;
}

void StealthAircraft::print(ostream& os)
{
    Aircraft::print(os);
    if (cloak_status == true)
    {
        os << "Cloak Status: On"  << endl;
    }
    else
    {
        os << "Cloak Status: Off" << endl;
    }   
}


// AbductorCraft methods

AbductorCraft::AbductorCraft():Aircraft(), StealthAircraft()
{
    abductee_count = 0;
    abductee_capacity = 0;
}

AbductorCraft::AbductorCraft(string identifier, int fuel_level, int health, AircraftStatus current_status, bool cloak_status, int abductee_count, int abductee_capacity):
    Aircraft(identifier, fuel_level, health, current_status), 
    StealthAircraft(identifier, fuel_level, health, current_status, cloak_status)
{
    this->abductee_count = abductee_count;
    this->abductee_capacity = abductee_capacity;
    if (this->abductee_count < 0)
    {
        this->abductee_count = 0;
    }
    if (this->abductee_capacity < 0)
    {
        this->abductee_capacity = abductee_count;
    }
    if (this->abductee_count > this->abductee_capacity)
    {
        this->abductee_count = this->abductee_capacity;
    }
}

AbductorCraft::AbductorCraft(const AbductorCraft &other) : Aircraft(other), StealthAircraft(other)
{   
    this->abductee_count = other.abductee_count;
    this->abductee_capacity = other.abductee_capacity;
    if (this->abductee_count < 0)
    {
        this->abductee_count = 0;
    }
    if (this->abductee_capacity < 0)
    {
        this->abductee_capacity = abductee_count;
    }
    if (this->abductee_count > this->abductee_capacity)
    {
        this->abductee_count = this->abductee_capacity;
    }
}

int AbductorCraft::getAbducteeCount() const
{
    return abductee_count;
}

int AbductorCraft::getAbducteeCapacity() const
{
    return abductee_capacity;
}

void AbductorCraft::setAbducteeCount(int count)
{
    abductee_count+=count;
}



bool AbductorCraft::operator>(const AbductorCraft &other)
{
    if ((float)abductee_count/abductee_capacity > (float)other.abductee_count/other.abductee_capacity)
    {
        return true;
    }
    return false;
}

AbductorCraft& AbductorCraft::operator+=(const int count)
{
    Aircraft::operator+=(count);
    
    if (getCurrentStatus() == AircraftStatus::Airborne)
    {
        abductee_count += count;
        if (abductee_count > abductee_capacity)
        {
            abductee_count = abductee_capacity;
        }
    }
    return *this;
}

AbductorCraft& AbductorCraft::operator-=(const int count)
{
    Aircraft::operator-=(count);
    
    if (getCurrentStatus() == AircraftStatus::Airborne)
    {
        abductee_count -= count;
        if (abductee_count < 0)
        {
            abductee_count = 0;
        }
    }
    return *this;
}

AbductorCraft& AbductorCraft::operator&(AbductorCraft &other)
{
    if (getCurrentStatus() == AircraftStatus::Airborne && other.getCurrentStatus() == AircraftStatus::Airborne)
    {
        AbductorCraft *l;
        AbductorCraft *s;

        if (abductee_capacity > other.abductee_capacity)
        {
            l = this;
            s = &other;
        }
        else
        {
            l = &other;
            s = this;
        }
        
        if ((l->getHealth() + s->getHealth()) > 100)
        {
            l->setHealth(100);
        }
        else
        {
            l->setHealth(s->getHealth());
        }


        if ((l->getFuelLevel() + s->getFuelLevel()) > 100)
        {
            l->setFuelLevel(100);
        }
        else
        {
            l->setFuelLevel(s->getFuelLevel());
        }

        l->abductee_capacity += s->abductee_capacity;

        if ((l->abductee_count + s->abductee_count) > l->abductee_capacity)
        {
            l->abductee_count = l->abductee_capacity;
        }
        else
        {
            l->abductee_count += s->abductee_count;
        }

        s->setFuelLevel(-100);
        s->setHealth(-100);
        s->abductee_count = 0;
        s->abductee_capacity = 0;
        s->deactivateCloak();
        s->setCurrentStatus(AircraftStatus::Crashed);

        return *l;
    }

    return *this;
}

void AbductorCraft::print(ostream& os)
{
    StealthAircraft::print(os);
    os << "Abductee Count: " << abductee_count << endl;
    os << "Abductee Capacity: " << abductee_capacity << endl;
}

// GuardianCraft methods


GuardianCraft::GuardianCraft(): Aircraft(), CombatAircraft(), StealthAircraft()
{
    kill_count =0;
}

GuardianCraft::GuardianCraft(string identifier, int fuel_level, int health, AircraftStatus status, string weapon_type, int weapon_count, int weapon_strength, bool cloak_status, int kill_count):
    Aircraft(identifier, fuel_level, health, status), 
    CombatAircraft(identifier, fuel_level, health, status, weapon_type, weapon_count, weapon_strength), 
    StealthAircraft(identifier, fuel_level, health, status, cloak_status)
{
    this->kill_count = kill_count;
    if (this->kill_count < 0)
    {
        this->kill_count = 0;
    }
}

GuardianCraft::GuardianCraft(const GuardianCraft &other) : Aircraft(other), CombatAircraft(other), StealthAircraft(other)
{   
    this->kill_count = other.kill_count;
    if (this->kill_count < 0)
    {
        this->kill_count = 0;
    }
}

int GuardianCraft::getKillCount() const
{
    return kill_count;
}

ostream& operator<<(ostream& os, const AircraftStatus& status) 
{
    switch (status) 
    {
        case AircraftStatus::OnGround: os << "On Ground"; break;
        case AircraftStatus::Airborne: os << "Airborne"; break;
        case AircraftStatus::Crashed: os << "Crashed"; break;
    }
    return os;
}

GuardianCraft GuardianCraft::operator++(int)
{
    GuardianCraft temp = *this; 
    if (getCurrentStatus() == AircraftStatus::OnGround)
    {
        setWeaponCount(1);
    }
    return temp;
}

GuardianCraft GuardianCraft::operator--()
{
    if (getCurrentStatus() == AircraftStatus::OnGround && getWeaponCount() > 0)
    {
        setWeaponCount(-1);
    }
    return *this;
}

bool GuardianCraft::operator*=(const AbductorCraft &other)
{
    if (getCurrentStatus() == AircraftStatus::Airborne && other.getCurrentStatus() == AircraftStatus::Airborne)
    {
        if (getWeaponCount() > 0)
        {
            if(other.getCloakStatus() == false && other.getAbducteeCount() == 0)
            {
                return true;
            }
        }
    }
    return false;
}

GuardianCraft& GuardianCraft::operator*(AbductorCraft &other)
{
    if ((*this) *= other)
    {
        if (other.getHealth() - getWeaponStrength() <= 0)
        {
            other.setHealth(-100);
            kill_count++;
            other.setCurrentStatus(AircraftStatus::Crashed);
            setWeaponCount(-1);
        }
        else
        {
            other.setHealth(- getWeaponStrength());
            setWeaponCount(-1);
        }
    }
    return *this;
}

void GuardianCraft::print(ostream& os)
{
    Aircraft::print(os);
    os << "Weapon Type: " << CombatAircraft::getWeaponType() << endl;
    os << "Weapon Count: " << CombatAircraft::getWeaponCount() << endl;
    os << "Weapon Strength: " << CombatAircraft::getWeaponStrength() << endl;
    if (getCloakStatus())
    {
        os << "Cloak Status: On" << endl;
    }
    else
    {
        os << "Cloak Status: Off" << endl;
    }
    
    os << "Kill Count: " << kill_count << endl;

}