#!/bin/bash

echo "\n---------------------- [GID ADD + Fast COMMIT + PUSH] ---------------------- \n"

make fclean
rm -rf *.cor

git status
git add .
git commit -m "Day 10 [CoreWar] - vmakahon (auto-push)"
git push origin master