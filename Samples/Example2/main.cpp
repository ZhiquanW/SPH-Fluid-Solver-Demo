
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Particle.h"
#include "FluidDatabase.h"

using namespace std;

// "Particle-Based Fluid Simulation for Interactive Applications"

// particle data structure
// stores position, velocity, and force for integration
// stores density (rho) and pressure values for SPH
struct Particle1 {
    Particle1(float _x, float _y, float _z) : x(_x, _y, _z), v(0.f, 0.f, 0), f(0.f, 0.f, 0), rho(0), p(0.f) {}

    Vector3 x, v, f;
    float rho, p;
};

// solver parameters
const static Vector3 G(0.f, 12000 * -9.8f, 0); // external (gravitational) forces
const static float REST_DENS = 1000.f;        // rest density
const static float GAS_CONST = 2000.f;        // const for equation of state
const static float H = 16.f;                // kernel radius
const static float HSQ = H * H;                // radius^2 for optimization
const static float MASS = 65.f;                // assume all particles have the same mass
const static float VISC = 250.f;            // viscosity constant
const static float DT = 0.001f;            // integration timestep

// smoothing kernels defined in Müller and their gradients
const static float POLY6 = 315.f / (65.f * M_PI * pow(H, 9.f));
const static float SPIKY_GRAD = -45.f / (M_PI * pow(H, 6.f));
const static float VISC_LAP = 45.f / (M_PI * pow(H, 6.f));

// simulation parameters
const static float BOUND_DAMPING = -0.5f;
size_t frame_num = 2000;
// solver data
static vector<Particle1> particles;
FluidDatabase tmp_database("test1", particles.size(), frame_num, DT);

// interaction
const static int MAX_PARTICLES = 2500;
const static int DAM_PARTICLES = 1000;
const static int BLOCK_PARTICLES = 250;

// rendering projection parameters
const static int WINDOW_WIDTH = 400;
const static int WINDOW_HEIGHT = 400;
const static int WINDOW_LENGTH = 0;


void InitSPH(void) {
    cout << "initializing dam break with " << DAM_PARTICLES << " particles" << endl;

        for (float x = WINDOW_WIDTH / 4; x <= WINDOW_WIDTH / 2; x += H)
            for (float z = WINDOW_LENGTH / 4; z <= WINDOW_LENGTH / 2; z += H)
                for (float y = 100; y < WINDOW_HEIGHT; y += H)
                if (particles.size() < DAM_PARTICLES) {
                    float x_offset = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    float z_offset = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    particles.push_back(Particle1(x , y, z ));
                }
        particles[0].x[0]+=0.5;
    tmp_database.set_particle_num(particles.size());
}

void Integrate(int i) {
    vector<Particle> tmp_list;
    size_t counter = 0;
    for (auto &p : particles) {
        // forward Euler integration
        p.v += DT * p.f / p.rho;
        p.x += DT * p.v;

        // enforce boundary conditions
        if (p.x[0] < 0.0f) {
            p.v[0] *= BOUND_DAMPING;
            p.x[0] = 0;
        }
        if (p.x[0] > WINDOW_WIDTH) {
            p.v[0] *= BOUND_DAMPING;
            p.x[0] = WINDOW_WIDTH;
        }
        if (p.x[1] < 0.0f) {
            p.v[1] *= BOUND_DAMPING;
            p.x[1] = 0;
        }
        if (p.x[1] > WINDOW_HEIGHT) {
            p.v[1] *= BOUND_DAMPING;
            p.x[1] = WINDOW_HEIGHT;
        }
        if(p.x[2] < 0){
            p.v[2] *= BOUND_DAMPING;
            p.x[2] = 0;
        }
        if(p.x[2] > WINDOW_LENGTH){
            p.v[2] *= BOUND_DAMPING;
            p.x[2] = WINDOW_LENGTH;
        }
        Particle tmp_p(counter++);
        tmp_p.set_position(Vector3(p.x[0], p.x[1], p.x[2]));
        tmp_list.push_back(tmp_p);
    }
    tmp_database.append_particle_list(i, tmp_list);
}

void ComputeDensityPressure(void) {
    for (auto &pi : particles) {
        pi.rho = 0.f;
        for (auto &pj : particles) {
            Vector3 rij = pj.x - pi.x;
            double_t r2 = rij.squared_distance();

            if (r2 < HSQ) {
                // this computation is symmetric
                pi.rho += MASS * POLY6 * pow(HSQ - r2, 3.f);
            }
        }
        pi.p = GAS_CONST * (pi.rho - REST_DENS);
//        cout << pi.rho <<" : " << pi.p << endl;
    }
}

void ComputeForces(void) {
    for (auto &pi : particles) {
        Vector3 fpress(0.f, 0.f, 0);
        Vector3 fvisc(0.f, 0.f, 0);
        for (auto &pj : particles) {
            if (&pi == &pj)
                continue;

            Vector3 rij = pi.x - pj.x;
            float r = rij.distance();

            if (r < H) {
                // compute pressure force contribution
                fpress += rij.normalize() * MASS * (pi.p + pj.p) / (2.f * pj.rho) * SPIKY_GRAD * pow(H - r, 2.f);
                // compute viscosity force contribution
                fvisc += VISC * MASS * (pj.v - pi.v) / pj.rho * VISC_LAP * (H - r);
            }
        }
        Vector3 fgrav = G * pi.rho;
        cout << pi.rho <<" : " << pi.p << " : " << pi.x << endl;
        cout << fpress/pi.rho << endl;
        pi.f = fpress + fvisc + fgrav;
    }
}

void Update(int i) {
    ComputeDensityPressure();
    ComputeForces();
    Integrate(i);
}

int main(int argc, char **argv) {

    InitSPH();
    for (int i = 0; i < frame_num; ++i) {
        Update(i);
    }
    tmp_database.export_database();
    return 0;
}