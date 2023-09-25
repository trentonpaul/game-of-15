g++ -o ./out/main.exe Board.cpp Board.h utils.h utils.cpp main.cpp -pthread
@echo off
cd out
@echo on
.\main.exe