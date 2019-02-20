
for i in `seq 5`
do
    for f in ../scenes/nonbvhscenes/*.sc
    do 
        time -p ../raytracer "$f"
       # rm $f
        echo "${f#*/}"  
    done >> nobvh.txt 2>&1
done


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
