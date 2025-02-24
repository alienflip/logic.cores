PROG=$1
rm main
gcc -o main main.c
./main "$PROG"