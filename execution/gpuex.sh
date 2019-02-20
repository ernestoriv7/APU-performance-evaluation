
for i in `seq 5`
do
    for f in ../scenes/gpu/*.sc
    do 
        time -p ../raytracer "$f"
        echo "${f#*gpu/}"  
    done #>> gpuresults.txt 2>&1
echo "++++++++++Corrida terminada++++++++++++++" #>> gpuresults.txt 2>&1
done >> gpuresults.txt 2>&1


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
