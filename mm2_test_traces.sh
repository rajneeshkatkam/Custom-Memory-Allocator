#! /bin/bash

#rm mm2_first_fit.txt
echo "---------------------------------New Trace Results-------------------------" >> mm2_first_fit.txt

echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/binary-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/binary-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/binary-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/cp-decl-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/cp-decl-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/cp-decl-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/random-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/random-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/random-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/realloc-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/realloc-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/realloc-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short1-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short1-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short1-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short2-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short2-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short2-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short3-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short3-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
./mdriver2 -V -f traces/short3-bal.rep | grep -E 'Reading|Perf|trace| 0|Total' >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
echo "-------------------------------------------------------------------------" >> mm2_first_fit.txt
echo "" >> mm2_first_fit.txt
