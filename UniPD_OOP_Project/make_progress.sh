#!/bin/bash

# pulizia dei file esistenti per ricreare il progetto da zero

echo "removing pre existing files..."
make clean -s
rm -rf Makefile
rm -rf .qmake.stash
rm -rf UniPD_OOP_Project.pro
rm -rf UniPD_OOP_Project.pro.user
rm -rf UniPD_OOP_Project.app

# creazione del .pro e modifica aggiungendo i QT widgets

qmake -project
echo "QT += widgets" >> UniPD_OOP_Project.pro
#decommentare la prossima riga prima di eseguire questo script se si vuole debuggare
#echo "CONFIG+=debug" >> UniPD_OOP_Project.pro
qmake 



PROJECT_DIR=$(pwd)

TOTAL_CPP=46
BUILT_O=0

echo
echo "Building project... ($TOTAL_CPP files)"

# make con -s per non mostrare i messaggi

make -s &
MAKE_PID=$!

trap "kill $MAKE_PID 2>/dev/null; exit" SIGINT
# Progress bar loop

while [ "$BUILT_O" -lt "$TOTAL_CPP" ]; do
    BUILT_O=$(find "$PROJECT_DIR" -type f -name "*.o" | wc -l)
    PERCENT=$(( 100 * BUILT_O / TOTAL_CPP ))

    BAR_LENGTH=30
    FILLED=$(( PERCENT * BAR_LENGTH / 100 ))
    [ $FILLED -gt $BAR_LENGTH ] && FILLED=$BAR_LENGTH
    EMPTY=$(( BAR_LENGTH - FILLED ))
    BAR=$(printf "%0.s#" $(seq 1 $FILLED))
    BAR="$BAR$(printf "%0.s_" $(seq 1 $EMPTY))"

    printf "\r[%s] %3d%% (%d/%d files)" "$BAR" "$PERCENT" "$BUILT_O" "$TOTAL_CPP"
    sleep 0.25
done

printf "\r[%s] 100%% (%d/%d files)\n" "$(printf "%0.s#" $(seq 1 $BAR_LENGTH))" "$TOTAL_CPP" "$TOTAL_CPP"

echo
echo "Build completed!"