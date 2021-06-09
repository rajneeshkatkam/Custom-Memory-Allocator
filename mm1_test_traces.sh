#! /bin/bash


echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/binary-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/cp-decl-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/random-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/realloc-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/short1-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/short2-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
echo "" >> mm1_best_fit.txt
./mdriver1 -V -f traces/short3-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm1_best_fit.txt



