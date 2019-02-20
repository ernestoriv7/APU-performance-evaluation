sed -i '/user/d' ./totalresults.txt
sed -i '/sys/d' ./totalresults.txt
sed -i '/image/d' ./totalresults.txt
sed -i 'N;s/\n/ /' ./totalresults.txt
sed -r "s/^([^ ]+)( [^ ]+)(.*)/\3\2/g" totalresults.txt > trprocessed.txt
sed -i 's/[^_]*_//' ./trprocessed.txt
sed -i 's/1000/Ob1000 /' ./trprocessed.txt
sed -i 's/4000/Ob4000 /' ./trprocessed.txt
sed -i 's/16000/Ob16000 /' ./trprocessed.txt
sed -i 's/65000/Ob65000 /' ./trprocessed.txt
sed -i 's/260000/Ob260000 /' ./trprocessed.txt
sed -i 's/CPU/CPU Ef/' ./trprocessed.txt
sed -i 's/GPU/GPU Ef/' ./trprocessed.txt
sed -i 's/APU/APU Ef/' ./trprocessed.txt
sed -i 's/-/ /' ./trprocessed.txt
sed -i 's/1280x720.sc /1280x720 /' ./trprocessed.txt
sed -i 's/1440x900.sc /1440x900 /' ./trprocessed.txt
sed -i 's/1920x1080.sc /1920x1080 /' ./trprocessed.txt
cp trprocessed.txt totalresults.txt
rm trprocessed.txt

