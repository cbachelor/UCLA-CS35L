randlibhw.so: randlibhw.c
	$gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o
	$gcc $(CFLAGS) -shared -o randlibhw.so randlibhw.o
randlibsw.so: randlibsw.c
	$gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
	$gcc $(CFLAGS) -shared -o randlibsw.so randlibsw.o
randmain: randmain.c randcpuid.c
	$gcc $(CFLAGS) -c randcpuid.c -o randcpuid.o
	$gcc $(CFLAGS) -c randmain.c -o randmain.o
	$gcc $(CFLAGS) -ldl -Wl,-rpath,$(PWD) randcpuid.o randmain.o -o randmain
