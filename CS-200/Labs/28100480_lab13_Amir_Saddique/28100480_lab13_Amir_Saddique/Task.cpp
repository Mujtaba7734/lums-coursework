#include "Task.h"
#include <iostream>
#include <cmath>

// -------- Robot Implementation --------

Robot::Robot(std::string robot_id, double init_x, double init_y, double battery)
{
    this->id = robot_id;
    this->x = init_x;
    this->y = init_y;
    this->battery_level = battery;
}

bool Robot::move_to(double new_x, double new_y) 
{
    double dx = new_x - x;
    double dy = new_y - y;
    double distance = std::sqrt(dx * dx + dy * dy);
    double energy = distance * battery_level;
    if (energy < battery_level)
    {
        return false;
    }
    battery_level -= energy;
    x = new_x;
    y = new_y;
    return true;
    // To be implemented
}

double Robot::get_battery_level() const 
{
    return battery_level;
}

std::string Robot::get_id() const {
    // To be implemented
    return id;
}

double Robot::get_x() const {
    // To be implemented
    return x;
}

double Robot::get_y() const {
    // To be implemented
    return y;
}

// -------- PlanterBot Implementation --------

PlanterBot::PlanterBot(std::string id, std::string seed, int seeds, double init_x, double init_y): Robot (id, init_x, init_y)
{
    seed_type = seed;
    seed_count = seeds;
    for (int i =0; i < FIELD_SIZE; i++)
    {
        for (int j =0; j < FIELD_SIZE; j++)
        {
            soil_quality[i][j] = i * j + 2;
            is_planted[i][j] = false;
        }
    }
}

bool PlanterBot::plant_seed(int x, int y) 
{
    if (x > FIELD_SIZE || y > FIELD_SIZE)
    {
        return false;
    }
    if (is_planted[x][y] == true)
    {
        return false;
    }
    if (seed_count <= 0 || battery_level < 5 || soil_quality[x][y] > 2)
    {
        return false;
    }
    seed_count--;
    battery_level -= 5;
    is_planted[x][y] = true;

    // To be implemented
    return true;
}

double PlanterBot::estimate_yield(int x, int y, int seed_quality_factor) const 
{
    if (x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE || is_planted[x][y] == true)
    {
        return 0.0;
    }
    double yeild = seed_quality_factor * soil_quality[x][y];
    // To be implemented
    return yeild;
}

int PlanterBot::get_seed_count() const 
{
    // To be implemented
    return seed_count;
}

void PlanterBot::print_soil_quality() const 
{
    for (int i =0; i < FIELD_SIZE; i++)
    {
        for (int j =0; j < FIELD_SIZE; j++)
        {
            std::cout << soil_quality[i][j] << std::endl;
        }
    }
    // To be implemented
}

void PlanterBot::print_is_planted() const 
{
    for (int i =0; i < FIELD_SIZE; i++)
    {
        for (int j =0; j < FIELD_SIZE; j++)
        {
            std::cout << is_planted[i][j]  << " | ";
        }
        std::cout << std::endl;
    }
    // To be implemented
}

// -------- HarvesterBot Implementation --------

HarvesterBot::HarvesterBot(std::string id, std::string crop, double capacity, double init_x, double init_y): Robot(id, init_x, init_y)
{
    crop_type = crop;
    storage_capacity = capacity;
    current_load = 0;
    for (int i =0; i < FIELD_SIZE; i++)
    {
        for (int j =0; j < FIELD_SIZE; j++)
        {
            if (i % 2 == 0 || j % 2 == 0)
            {
                crop_ready[i][j] = true;
                continue;
            }
            crop_ready[i][j] = false;
        }
    }
}

bool HarvesterBot::harvest(int x, int y, double load) 
{
    if (x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE)
    {
        return false;
    }
    if (crop_ready[x][y] == false)
    {
        return false;
    }
    if ( battery_level < 5 || (current_load + load) > storage_capacity)
    {
        return false;
    }
    crop_ready[x][y] = false;
    current_load += load;
    battery_level -= 5;

    // To be implemented
    return false;
}

double HarvesterBot::get_efficiency() const {
    double percentage = (current_load/ storage_capacity) * 100;
    // To be implemented
    return percentage;
}

double HarvesterBot::get_current_load() const 
{
    return current_load;
    // To be implemented
}

void HarvesterBot::print_crop_ready() const 
{
    for (int i =0; i < FIELD_SIZE; i++)
    {
        for (int j =0; j < FIELD_SIZE; j++)
        {
            std::cout << crop_ready[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    // To be implemented
}

// -------- AgriBot Implementation --------

AgriBot::AgriBot(std::string id, std::string seed, int seeds,
                 std::string crop, double storage, double init_x, double init_y, std::string init_mode)
                 : Robot(id, init_x, init_y), PlanterBot(id, seed, seeds, init_x, init_y), HarvesterBot (id, crop, storage, init_x, init_y)
{
    mode = init_mode;
}

bool AgriBot::set_mode(const std::string& new_mode) 
{
    if (new_mode == "planting" || new_mode == "harvesting")
    {
        mode = new_mode;
        return true;
    }
    // To be implemented
    return false;
}

std::string AgriBot::get_mode() const {
    // To be implemented
    return mode;
}

bool AgriBot::perform_cycle(int x, int y, double load) 
{
    bool check = false;
    if (mode == "planting")
    {
        check = plant_seed(x,y);
        if (check == false)
        {
            return false;
        }
        return true;
    }
    if (mode == "harvesting")
    {
        check = harvest(x, y, load);
        if (check == false)
        {
            return false;
        }
        return true;
    }
    // To be implemented
    return true;
}

double AgriBot::get_yield(int x, int y, int seed_quality_factor) const 
{
    if (mode == "planting")
    {
        return estimate_yield(x,y, seed_quality_factor);
    }
    if (mode == "harvesting")
    {
        if (x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE)
        {
            return 0.0;
        }
        if (crop_ready[x][y] == false)
        {
            return 0.0;
        }
        return 5.0;
    }
    // To be implemented
    return 0.0;
}

bool AgriBot::is_operational() const 
{
    if (battery_level > 5)
    {
        if (mode == "planting")
        {
            if (seed_count > 0) 
            {
                return true;
            }
        }
        if (mode == "harvesting")
        {
            if (current_load < storage_capacity)
            {
                return true;
            }
        }
    }
    return false;
    // To be implemented
    return false;
}

// int main ()
// {
//     AgriBot Ag =  AgriBot("Crop1", "Wheat Seeds", 2, "Wheat", 20, 3, 4, "planting");
//     std::cout << Ag.get_yield(3, 4, 3) << std::endl;
//     Ag.set_mode("harvesting");
//     std::cout << Ag.get_yield(3,4,3) << std::endl;
//     Ag.print_crop_ready();
// }