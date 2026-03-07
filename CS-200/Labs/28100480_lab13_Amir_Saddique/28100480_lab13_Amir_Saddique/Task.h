#ifndef AGRIBOT_SYSTEM_H
#define AGRIBOT_SYSTEM_H

#include <string>

//DO NOT CHANGE FIELD_SIZE 
const int FIELD_SIZE = 5;

class Robot {
protected:
    std::string id;
    double x, y;
    double battery_level;

public:
    Robot(std::string robot_id, double init_x = 0, double init_y = 0, double battery = 100.0);

    bool move_to(double new_x, double new_y);
    double get_battery_level() const;
    std::string get_id() const;
    double get_x() const;
    double get_y() const;
};

class PlanterBot: virtual public Robot{ // figure out inheritance
protected:
    std::string seed_type;
    int seed_count;
    int soil_quality[FIELD_SIZE][FIELD_SIZE];
    bool is_planted[FIELD_SIZE][FIELD_SIZE];

public:
    PlanterBot(std::string id, std::string seed, int seeds, double init_x = 0, double init_y = 0);

    bool plant_seed(int x, int y);
    double estimate_yield(int x, int y, int seed_quality_factor) const;
    int get_seed_count() const;
    void print_soil_quality() const;
    void print_is_planted() const;
};

class HarvesterBot: virtual public Robot { // figure out inheritance
protected:
    std::string crop_type;
    double storage_capacity;
    double current_load;
    int crop_ready[FIELD_SIZE][FIELD_SIZE];

public:
    HarvesterBot(std::string id, std::string crop, double capacity, double init_x = 0, double init_y = 0);

    bool harvest(int x, int y, double load);
    double get_efficiency() const;
    double get_current_load() const;
    void print_crop_ready() const;
};

class AgriBot: public PlanterBot, public HarvesterBot { // figure out inheritance
private:
    std::string mode;

public:
    AgriBot(std::string id,
            std::string seed, int seeds,
            std::string crop, double storage,
            double init_x = 0, double init_y = 0, std::string init_mode = "planting");

    bool set_mode(const std::string& new_mode);
    std::string get_mode() const;
    bool perform_cycle(int x, int y, double load = 0.0);
    double get_yield(int x, int y, int seed_quality_factor = 1.0) const;
    bool is_operational() const;
};

#endif // AGRIBOT_SYSTEM_H