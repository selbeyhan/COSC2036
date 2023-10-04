if [ -f HW3 ]; then
    rm HW3
fi
g++ HW3.cpp -o HW3
if [ ! -f HW3 ]; then
    echo   "Failed"
    exit
fi
./HW3 p1 p1.txt 6