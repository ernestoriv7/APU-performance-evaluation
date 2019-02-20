
for i in `seq 5`
do
    for f in ../scenes/cpu/*.sc
    do 
        time -p ../raytracer "$f"
        echo "${f#*cpu/}"  
    done #>> cpuresults.txt 2>&1
echo "++++++++++Corrida terminada++++++++++++++" #>> cpuresults.txt 2>&1
done >> cpuresults.txt 2>&1


# CPUPATH="../scenes/cpu"
#rm "$CPUPATH/*"
#bash ../scenes/casesgen.sh

#for i in `seq 5`
#do
#    for f in ../scenes/cpu/*.sc 
#    do 
#        time -p ../raytracer "$f"
#        echo "$f"  
#    done
#echo "Corrida $i terminada" 
#done >> results.txt 2>&1
