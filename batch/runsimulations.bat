g++ -o ./out/sims.exe Board.cpp Board.h Simulator.h Simulator.cpp utils.h utils.cpp simulations.cpp -pthread
@echo off
cd out
@echo on
.\sims.exe