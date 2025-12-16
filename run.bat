@echo off
gcc "%~1.c" "entities/character.c" "items/armours.c" "items/weapons.c" "maps/location.c" "core/battle.c" -o "%~1.exe"
"%~1.exe"