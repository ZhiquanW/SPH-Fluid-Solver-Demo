#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <thread>
#include <iomanip>
#include "FluidSolver.h"

using namespace std;
#define vec3 Vector3


void test_class_RestrictionBox_Particle();

void test_RestrictionBox();

void test_fluid_solver();

void test_iterator();

void test_initialize_particles();

void test_compute_functions();

int main() {
    std::cout << "Hello, World!" << std::endl;
    test_compute_functions();
    return 0;
}

//r - 0.03
void test_compute_functions() {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%F %T");
    string tmp_s = ss.str();
    long tmp_index = tmp_s.find(' ');
    tmp_s[tmp_index] = '-';
    cout << "File Name : " + tmp_s << endl;
    const vec3 left_bottom_front = vec3();
    const vec3 right_top_back = vec3(300, 400, 300);
    const size_t particle_num = 2000;
    const double_t rest_density = -1000;
    const double_t gas_constant = 2000;
    const double_t viscosity = 250;
    const double_t kernel_radius = 16;
    const double_t mass = 65;
    const double_t bound_damping = 0.5;
    const double_t gravity = 12000 * 9.8;
    const size_t frame_num = 400;
    const double_t time_interval = 0.001;
    const FluidParameter tmp_paras(particle_num, mass, kernel_radius, rest_density, viscosity, gas_constant, 1000,
                                   gravity);
    const RestrictionBox tmp_box(left_bottom_front, right_top_back, bound_damping);
    FluidDatabase tmp_database(tmp_s, tmp_paras.get_particle_num(), frame_num, time_interval);
    FluidSolver tmp_solver(tmp_paras, tmp_box, tmp_database);
    tmp_solver.initialize_particles(vec3(0,0, 0), vec3(200, 400, 200), 16);
    tmp_solver.simulate_particles();
    tmp_solver.output_data();
    cout << "End" << endl;
}

