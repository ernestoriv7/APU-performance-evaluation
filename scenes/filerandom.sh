for file in cpu/* 
do
  #file=${file#*/}
  mv "$file" "cpu/"$RANDOM\_"${file#*/}"
  #echo $file 
done

for x in gpu/* 
do
  #file=${file#*/}
  mv "$x" "gpu/"$RANDOM\_"${x#*/}"
  #echo $file 
done

for y in apu/* 
do
  #file=${file#*/}
  mv "$y" "apu/"$RANDOM\_"${y#*/}"
  #echo $file 
done
