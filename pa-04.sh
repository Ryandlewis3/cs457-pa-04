#!/bin/bash
echo
echo "Script to run PA-04"
echo "By: Mohamed Aboutabl"
echo

rm -f dispatcher   genMasterKey        kdc/kdc            kdc/logKDC.txt    
rm -f amal/amal    amal/logAmal.txt    amal/amalKey.bin   amal/amalIV.bin  
rm -f basim/basim  basim/logBasim.txt  basim/bsimKey.bin  basim/basimIV.bin  
rm -f *.mp4        kdc/*.bin           amal/*.bin         basim/*.bin

ln -s  ../bunny.mp4       bunny.mp4

echo
echo "=============================="
echo "Compiling Static source"
echo "=============================="
echo
	gcc genMasterKey.c              -o genMasterKey       -l:libcrypto.so.1.1
	gcc wrappers.c     dispatcher.c -o dispatcher

echo
echo "========================================="
echo "Generating Master Keys for Amal and Basim"
echo "========================================="
echo

./genMasterKey
mv   key.bin amal/amalKey.bin
mv   iv.bin  amal/amalIV.bin

./genMasterKey
mv   key.bin basim/basimKey.bin
mv   iv.bin  basim/basimIV.bin

echo "Sharing those Master Keys with the KDC"
cd   kdc
ln  -s ../amal/amalKey.bin   amalKey.bin
ln  -s ../amal/amalIV.bin    amalIV.bin
ln  -s ../basim/basimKey.bin basimKey.bin
ln  -s ../basim/basimIV.bin  basimIV.bin
cd ..

# make sure Aboutabl executable have the 'x' flag
chmod +x  *_aboutablEx*

echo
echo "*******************************************************"
echo "Testing STUDENT's Amal+Basim against Dr. Aboutabl's KDC"
echo "*******************************************************"
echo

    cp  kdc_aboutablExecutable         kdc/kdc
	gcc amal/amal.c    myCrypto.c   -o amal/amal    -l:libcrypto.so.1.1
	gcc basim/basim.c  myCrypto.c   -o basim/basim  -l:libcrypto.so.1.1

    ./dispatcher

    echo
    echo "======  STUDENT's   Amal   LOG  ========="
    cat amal/logAmal.txt

    echo
    echo "======  ABOUTABL'S  KDC    LOG  ========="
    cat kdc/logKDC.txt
    echo

    echo
    echo "======  STUDENT's   Basim  LOG  ========="
    cat basim/logBasim.txt
    echo

exit 0
read -p "Press [Enter] key to continue ..."

echo
echo "********************************************************"
echo "Testing STUDENT's Basim+KDC  against Dr. Aboutabl's Amal"
echo "********************************************************"
echo
    cp  amal_aboutablExecutable            amal/amal
        gcc basim/basim.c  myCrypto.c   -o basim/basim  -l:libcrypto.so.1.1
        gcc kdc/kdc.c      myCrypto.c   -o kdc/kdc      -l:libcrypto.so.1.1
    ./dispatcher

    echo
    echo "======  ABOUTABL'S  Amal   LOG  ========="
    cat amal/logAmal.txt

    echo
    echo "======  STUDENT's   KDC    LOG  ========="
    cat kdc/logKDC.txt
    echo

    echo
    echo "======  STUDENT's   Basim  LOG  ========="
    cat basim/logBasim.txt
    echo

exit 0
read -p "Press [Enter] key to continue ..."

echo
echo "********************************************************"
echo "Testing STUDENT's Amal+KDC  against Dr. Aboutabl's Basim"
echo "********************************************************"
echo

    cp  basim_aboutablExecutable       basim/basim
    gcc amal/amal.c    myCrypto.c   -o amal/amal    -l:libcrypto.so.1.1
    gcc kdc/kdc.c      myCrypto.c   -o kdc/kdc      -l:libcrypto.so.1.1
    
    ./dispatcher

    echo
    echo "======  STUDENT's   Amal   LOG  ========="
    cat amal/logAmal.txt

    echo 
    echo "======  STUDENT's   KDC    LOG  ========="
    cat kdc/logKDC.txt
    echo

    echo
    echo "======  ABOUTABL'S  Basim LOG  ========="
    cat basim/logBasim.txt
    echo

exit 0
read -p "Press [Enter] key to continue ..."

echo
echo "********************************************************"
echo "Testing STUDENT's Code All with itself"
echo "********************************************************"
echo
	gcc amal/amal.c    myCrypto.c   -o amal/amal    -l:libcrypto.so.1.1
	gcc basim/basim.c  myCrypto.c   -o basim/basim  -l:libcrypto.so.1.1
	gcc kdc/kdc.c      myCrypto.c   -o kdc/kdc      -l:libcrypto.so.1.1

    ./dispatcher

    echo
    echo "======  STUDENT's   Amal   LOG  ========="
    cat amal/logAmal.txt

    echo
    echo "======  STUDENT's   KDC    LOG  ========="
    cat kdc/logKDC.txt
    echo

    echo
    echo "======  STUDENT's   Basim  LOG  ========="
    cat basim/logBasim.txt
    echo

