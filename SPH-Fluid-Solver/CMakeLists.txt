cmake_minimum_required(VERSION 3.13)
project(SPH_Fluid_Solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPH_Fluid_Solver main.cpp Particle.h FluidDatabase.h FluidSolver.h RestrictionBox.h FluidParameter.h)