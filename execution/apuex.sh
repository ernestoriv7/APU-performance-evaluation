
#for i in `seq 5`
#do
    for f in ../scenes/apu/*.sc
    do 
        time -p ../raytracer "$f"
        rm $f
        echo "${f#*apu/}"  
    done >> apuresults.txt 2>&1
#echo "++++++++++Corrida terminada++++++++++++++" #>> apuresults.txt 2>&1
#done >> apuresults.txt 2>&1


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
