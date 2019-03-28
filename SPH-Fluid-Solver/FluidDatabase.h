#include <utility>

#include <utility>

#include <utility>

//
// Created by zhiquan on 3/5/19.
//

#ifndef SPH_FLUID_SOLVER_FLUIDDATABASE_H
#define SPH_FLUID_SOLVER_FLUIDDATABASE_H

#include <vector>
#include <fstream>
#include <algorithm>
#include "Particle.h"

using namespace std;

class FluidDatabase {
private:
    string file_name;
    size_t particle_num{};
    size_t frame_num{};
    double_t frame_interval{};
    double_t animation_duration{};
    double_t computation_duration{};
    vector<vector<Particle>> particle_matrix;
public:

    FluidDatabase() = default;

    explicit FluidDatabase(string file_name, size_t particle_num, size_t frame_num, double_t frame_interval)
            : file_name(std::move(file_name)), particle_num(particle_num), frame_num(frame_num),
              frame_interval(frame_interval) {
        this->animation_duration = frame_num * frame_interval;

        particle_matrix.resize(frame_num);
        for (auto &list:this->particle_matrix) {
            list.resize(particle_num);
        }
    }

    void append_particle_list(size_t frame_index, vector<Particle> in_particle_list) {
        particle_matrix[frame_index] = std::move(in_particle_list);
    }

    void export_database() {
        cout << "Output File:" + file_name << endl;
        fstream fout;
        fout.open(this->file_name.c_str(), ios::out);
        fout << file_name << endl;
        fout << particle_num << " " << frame_num << " " << frame_interval << " "
             << animation_duration << endl;
        int counter = -1;
        for (const auto &list:this->particle_matrix) {
            fout << ++counter << endl;
            size_t p_num = 0;
            for (const auto &p:list) {
                fout << p_num++ << " " << p.get_position() << endl;
            }
        }
    }

    void export_viscosity() {
        fstream fout;
        fout.open(this->file_name + "viscosity", ios::out);
        fout << file_name << endl;
        fout << particle_num << " " << frame_num << " " << frame_interval << " " << frame_interval << " "
             << animation_duration << " " << computation_duration << endl;
        int counter = -1;
        for (const auto &list:this->particle_matrix) {
            fout << ++counter << endl;
            size_t p_num = 0;
            for (const auto &p:list) {
                fout << p_num++ << " " << p.get_viscosity_acceleration() << endl;
            }
        }
    }

    const string &get_file_name() const {
        return file_name;
    }

    void set_file_name(const string &file_name) {
        FluidDatabase::file_name = file_name;
    }

    size_t get_particle_num() const {
        return particle_num;
    }

    void set_particle_num(size_t particle_num) {
        FluidDatabase::particle_num = particle_num;
    }

    size_t get_frame_num() const {
        return frame_num;
    }

    void set_frame_num(size_t frame_num) {
        FluidDatabase::frame_num = frame_num;
    }

    double get_frame_interval() const {
        return frame_interval;
    }

    void set_frame_interval(size_t frame_interval) {
        FluidDatabase::frame_interval = frame_interval;
    }

    double_t get_animation_duration() const {
        return animation_duration;
    }

    void set_animation_duration(size_t animation_duration) {
        FluidDatabase::animation_duration = animation_duration;
    }

    const vector<vector<Particle>> &get_particle_matrix() const {
        return particle_matrix;
    }

    void set_particle_matrix(const vector<vector<Particle>> &particle_matrix) {
        FluidDatabase::particle_matrix = particle_matrix;
    }

    void set_computation_duration(double_t _duration) {
        FluidDatabase::computation_duration = _duration;
    }
};


#endif //SPH_FLUID_SOLVER_FLUIDDATABASE_H
