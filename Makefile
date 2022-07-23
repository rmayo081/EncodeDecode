#Default target, compile both programs
build: encode decode

#Rules for building encode executable
encode: filebuffer.h state24.h filebuffer.o state24.o encode.o
	gcc -Wall -std=c99 state24.c filebuffer.c  encode.c -o encode

#Rules for building decode executable
decode: filebuffer.h state24.h filebuffer.o state24.o decode.o
	gcc -Wall -std=c99 state24.o filebuffer.o  decode.o -o decode

#Rules for building filebuffer component object
filebuffer.o: filebuffer.h filebuffer.c
	gcc -Wall -std=c99 -c filebuffer.c -o filebuffer.o

#Rules for building state24 component object
state24.o: state24.h filebuffer.h state24.c
	gcc -Wall -std=c99 -c state24.c -o state24.o

#Rules for building encode component object
encode.o: state24.h filebuffer.h encode.c
	gcc -Wall -std=c99 -c encode.c -o encode.o
#Rules for building decode component object
decode.o: state24.h filebuffer.h decode.c
	gcc -Wall -std=c99 -c decode.c -o decode.o

#Target to clean the directory
clean:
	rm -f output.bin output.txt
	rm -f stdout.txt stderr.txt
	rm -f state24.o filebuffer.o encode.o decode.o
	rm -f encode
	rm -f decode