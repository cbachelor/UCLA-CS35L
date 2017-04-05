I ran into a few issues trying to inplement threading into srt. I
first looked at the main function, and saw how there was a huge chunk
of code that involved multiple nested for loops, and since no other
part in the main function had too much code that seemed intensive, I
knew that I had to implement threading into the loop. However,
pthread_create only accepted functions of one argument, I had to take
the for loop out into its own function called threadCall. I also
didn't want each thread to initialize all the variables that were in
the original main function, so I made them global variables, and
initialized them in a function initializeGlobals() for
convenience. However, I had to keep the "const double" variables
inside the threaded function since they were of type const and I
couldn't alter them. I made the total number of threads and the
'scene' variable global as well so that each thread can access these.

The main issue I ran into was with dividing the for loop in
threadCall() so each thread will do a different part of the
loop. Initially I had each thread divide the work up by dividing the
total width by number of threads, however I realized this will lead to
weird division problems. Instead, I just had each thread start at a
different offset and increment equally so that none of the loops
overlap. I also initially didn't realize that due to the race
conditions, the original print methods led to issues with the ordering
of printing. So, instead I stored all the outputs in order to solve
this issue. Also, another careless mistake that cost me the most time
was that I passed the thread number into threadCall(), by simply
passing the address of the variable used to loop through the
threads. This led to race conditions since the variable will change
values every time the for loop continued. So, I implemented an array
so that the loop variable will be stored locally.

Implementation of the threads led to significant performance:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m51.510s
user    0m51.499s
sys     0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m26.894s
user    0m53.524s
sys     0m0.006s

time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m13.668s
user    0m53.948s
sys     0m0.003s
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m7.279s
user    0m56.090s
sys     0m0.015s

While user time didn't change too much, the real time did decrease by
around 8 times with the use of 8 threads, which is quite
significant. The system call time barely had any increase as threads
increased.
