//
// Created by zhiquan on 3/11/19.
//

#ifndef SPH_FLUID_SOLVER_FLUIDPARAMETER_H
#define SPH_FLUID_SOLVER_FLUIDPARAMETER_H

#include <cmath>
#include <string>

class FluidParameter {
private:
    size_t particle_num{};
    double_t particle_mass{};
    double_t core_radius{};
    double_t rest_density{};
    double_t viscosity_coefficient{};
    double_t gas_constant{};
    double_t tension_coefficient{};
    double_t gravity_acceleration_coefficient{};
//    double_t bound_damping_coefficient{};
public:
    FluidParameter() = default;

    FluidParameter(const size_t _particle_num, const double_t &_particle_mass,
                   const double_t &_core_radius, const double_t &_rest_density,
                   const double_t &_viscosity_coefficient, const double_t &_gas_constant,
                   const double_t &_tension_coefficient, const double_t &_gravity_acceleration_coefficient) :
            particle_num(_particle_num), particle_mass(_particle_mass),
            core_radius(_core_radius), rest_density(_rest_density),
            viscosity_coefficient(_viscosity_coefficient), gas_constant(_gas_constant),
            tension_coefficient(_tension_coefficient),
            gravity_acceleration_coefficient(_gravity_acceleration_coefficient){

    }


public:

    void show_parameters() const {
        std::cout << "Particle_Num:" << particle_num << std::endl
                  << "Particle_Mass:" << particle_mass << std::endl
                  << "Core_Radius:" << core_radius << std::endl
                  << "Viscosity_Coefficient:" << viscosity_coefficient << std::endl
                  << "Gas_Constant:" << gas_constant << std::endl
                  << "Gravity_Acceleration_Coefficient" << gravity_acceleration_coefficient << std::endl;
    }

    const size_t &get_particle_num() const {
        return particle_num;
    }

    void set_particle_num(const size_t &particle_num) {
        FluidParameter::particle_num = particle_num;
    }

    double_t get_particle_mass() const {
        return particle_mass;
    }

    void set_particle_mass(double_t particle_mass) {
        FluidParameter::particle_mass = particle_mass;
    }

    double_t get_core_radius() const {
        return core_radius;
    }

    void set_core_radius(double_t core_radius) {
        FluidParameter::core_radius = core_radius;
    }

    double_t get_rest_density() const {
        return rest_density;
    }

    void set_rest_density(double_t rest_density) {
        FluidParameter::rest_density = rest_density;
    }

    double_t get_viscosity_coefficient() const {
        return viscosity_coefficient;
    }

    void set_viscosity_coefficient(double_t viscosity_coefficient) {
        FluidParameter::viscosity_coefficient = viscosity_coefficient;
    }

    double_t get_gas_constant() const {
        return gas_constant;
    }

    void set_gas_constant(double_t gas_constant) {
        FluidParameter::gas_constant = gas_constant;
    }

    double_t get_gravity_acceleration_coefficient() const {
        return gravity_acceleration_coefficient;
    }

    void set_gravity_acceleration_coefficient(double_t gravity_acceleration_coefficient) {
        FluidParameter::gravity_acceleration_coefficient = gravity_acceleration_coefficient;
    }

    double_t get_tension_coefficient() const {
        return tension_coefficient;
    }

    void set_tension_coefficient(double_t tension_coefficient) {
        FluidParameter::tension_coefficient = tension_coefficient;
    }

//    double_t get_bound_damping_coefficient() const {
//        return bound_damping_coefficient;
//    }
//
//    void set_bound_damping_coefficient(double_t tension_coefficient) {
//        FluidParameter::bound_damping_coefficient = bound_damping_coefficient;
//    }

};


#endif //SPH_FLUID_SOLVER_FLUIDPARAMETER_H
