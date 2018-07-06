#!/bin/bash

echo "\n---------------------- [GID ADD + Fast COMMIT + PUSH] ---------------------- \n"

make fclean
rm -rf *.cor

git status
git add .
git status
git commit -m "Day 31 [CoreWar-VM] - vmakahon (auto-push)"
git status
git push origin master
git status