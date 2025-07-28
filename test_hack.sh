#!/bin/bash

echo "Testing hack case 1: All employees leave"
echo "5 100
I 100
I 200  
S 150
F 1
F 2" | g++ -o test final_robust_solution.cpp && ./test

echo -e "\n\nTesting hack case 2: Extreme salary adjustments"
echo "6 10
I 50
A 1000
S 1040  
F 1
I 100
F 1" | ./test

echo -e "\n\nTesting hack case 3: Empty operations"
echo "1 100
F 1" | ./test

echo -e "\n\nTesting hack case 4: Large numbers"
echo "7 1000000000
I 1000000000
A 999999999
S 1999999999
F 1
I 2000000000
S 1
F 1" | ./test

echo -e "\n\nTesting hack case 5: Multiple same salaries"
echo "8 10
I 20
I 20
I 30
F 1
F 2
F 3
S 15
F 1" | ./test

echo -e "\n\nTesting hack case 6: Zero and negative cases"
echo "5 0
I 0
S 1
F 1
A 2
F 1" | ./test