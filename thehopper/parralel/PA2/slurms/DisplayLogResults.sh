

#!/bin/bash

keywords="Running\|Time\|Starting\|result\|Calculating\|Fibonacchi\|Parallel\|Serial\|Multiplying"

echo "--------------------------"
echo "Displaying Results:"
echo "--------------------------"

for SlurmFile in $(ls logs/ | grep ".log"); do
   echo $SlurmFile
   echo " Results:"
   cat logs/$SlurmFile | grep $keywords   
   echo "----------------------------"
done


