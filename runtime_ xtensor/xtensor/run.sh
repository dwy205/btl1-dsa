#!/bin/bash

g++ -fsanitize=address -o main -Iinclude -Isrc -std=c++17 main.cpp 