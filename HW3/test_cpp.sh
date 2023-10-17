if [ -f HW3 ]; then
    rm HW3
fi
g++ HW3.cpp -o HW3
if [ ! -f HW3 ]; then
    echo   "Complile Fail"
    exit
fi

# ./HW3 p1 outputs/p1.txt 5
# echo "finished p1"
# ./HW3 p2 outputs/p2.txt 6
# echo "finished p2"
# ./HW3 e1 outputs/e1.txt 6
# echo "finished e1"
# ./HW3 e2 outputs/e2.txt 6
# echo "finished e2"
# ./HW3 e3 outputs/e3.txt 5
# echo "finished e3"
# ./HW3 e4 outputs/e4.txt 6
# echo "finished e4"
./HW3 e5 outputs/e5.txt 4
echo "finished e5"