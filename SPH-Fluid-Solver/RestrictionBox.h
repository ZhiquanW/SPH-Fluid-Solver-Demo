//
// Created by zhiquan on 3/6/19.
//

#ifndef SPH_FLUID_SOLVER_RESTRICTIONBOX_H
#define SPH_FLUID_SOLVER_RESTRICTIONBOX_H

#include <cmath>
#include "Vector3.h"
#include "Particle.h"

#define vec3 Vector3

class RestrictionBox {
private:
    double left_right_detection[2]{};
    double front_back_detection[2]{};
    double bottom_top_detection[2]{};
    double_t bound_damping_coefficient{};
public:
    RestrictionBox() = default;

    RestrictionBox(const vec3 &vertex0, const vec3 &vertex1, double_t _bound_damping_coefficient) :
            bound_damping_coefficient(_bound_damping_coefficient) {
//        cout << vertex0 << " " << vertex1 << endl;
        left_right_detection[0] = vertex0.x();
        left_right_detection[1] = vertex1.x();
        bottom_top_detection[0] = vertex0.y();
        bottom_top_detection[1] = vertex1.y();
        front_back_detection[0] = vertex0.z();
        front_back_detection[1] = vertex1.z();
    }

    void restrict_particle(Particle &in_particle) {
        vec3 tmp_pos = in_particle.get_position();
        const vec3 &tmp_vel = in_particle.get_velocity();
        vec3 new_vel = tmp_vel;
        if (tmp_pos.x() < left_right_detection[0]) {
            new_vel.set_x(-bound_damping_coefficient * tmp_vel.x());
            tmp_pos.set_x(left_right_detection[0]);
            //-= 2 * dot(normal_arr[0], tmp_vel) * normal_arr[0];
        }
        if (tmp_pos.x() > left_right_detection[1]) {
            new_vel.set_x(-bound_damping_coefficient * tmp_vel.x());
            tmp_pos.set_x(left_right_detection[1]);
            // new_vel -= 2 * dot(normal_arr[1], tmp_vel) * normal_arr[1];
        }
        if (tmp_pos.y() < bottom_top_detection[0]) {
            new_vel.set_y(-bound_damping_coefficient * tmp_vel.y());
            tmp_pos.set_y(bottom_top_detection[0]);
            //new_vel -= 2 * dot(normal_arr[2], tmp_vel) * normal_arr[2];
        }
        if (tmp_pos.y() > bottom_top_detection[1]) {
            new_vel.set_y(-bound_damping_coefficient * tmp_vel.y());
            tmp_pos.set_y(bottom_top_detection[1]);
            //new_vel -= 2 * dot(normal_arr[3], tmp_vel) * normal_arr[3];
        }
        if (tmp_pos.z() < front_back_detection[0]) {
            new_vel.set_z(-bound_damping_coefficient * tmp_vel.z());
            tmp_pos.set_z(front_back_detection[0]);
            //new_vel -= 2 * dot(normal_arr[4], tmp_vel) * normal_arr[4];
        }
        if (tmp_pos.z() > front_back_detection[1]) {
            new_vel.set_z(-bound_damping_coefficient * tmp_vel.z());
            tmp_pos.set_z(front_back_detection[1]);
            //new_vel -= 2 * dot(normal_arr[5], tmp_vel) * normal_arr[5];
        }
        in_particle.set_velocity(new_vel);
        in_particle.set_position(tmp_pos);
    }
};


#endif //SPH_FLUID_SOLVER_RESTRICTIONBOX_H
