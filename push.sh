#!/bin/bash
echo "\n---------------------- [GID ADD + Fast COMMIT + PUSH] ---------------------- \n"
make clean

git status
git add .
git status
git commit -m "[CoreWar]: Day 49 -  vmakahon (auto-push)"
git status
git push origin master
git status