if [[ "$#" -eq "3" ]]; then
    nodes="$1"
    edges="$2"
    probability="$3"    
elif [[ "$#" -eq "2" ]]; then 
    nodes="$1"
    edges="$2"
    probability="0.1"    
elif [[ "$#" -eq "1" ]]; then
    nodes="$1"
    edges=$((2 * $1))
    probability=0.1 
else
    nodes=10
    edges=20
    probability=0.1  
fi

g++ CreateMatrix.cpp -o main

echo "Creating incidence matrix. It has:"
echo "  $nodes vertices;"
echo "  $edges edges."
echo "Probability of generating loop = $probability"

./main "$nodes" "$edges" "$probability"
echo "Matrix created."
rm main

gcc main.c -D _BUFFER  -o main
echo "Finding loops... Reading from file using buffer. Buffer size = 10 KB."
./main
if [[ ($nodes -lt "51") && ($edges -lt "101") ]]; then
    dot -Tsvg output.dot -o ./Graph.svg
fi
rm main output.dot

gcc main.c -D _BYCHAR -o main
echo "Finding loops... Reading from file character by character."
./main
rm main output.dot