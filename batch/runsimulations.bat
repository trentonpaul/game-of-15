g++ -o ./out/sims.exe Board.cpp Board.h Simulator.h Simulator.cpp utils.h utils.cpp simulations.cpp -march=native -mtune=native -O3 -pthread
@echo off
cd out
@echo on
.\sims.exe