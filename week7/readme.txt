After-action report:


The issue I encounter is that I don't know how to view the
picture. I followed the commands in spec, but there are errors.
So I download gimp online and copy the image in my own pc to see
what the images looks like. I do not run into some serious issue
while modifying the code. 

First I test the unmodified version with the command:make check clean
The output is:
time ./srt 1-test.ppm >1-test.ppm.tmp

real 0m53.095s
user 0m53.091s
sys  0m0.000s


Then I test the multithread version
The output is:
time ./srt 1-test.ppm >1-test.ppm.tmp

real 0m55.865s
user 0m55.860s
sys  0m0.001s

time ./srt 2-test.ppm >2-test.ppm.tmp

real 0m28.033s
user 0m55.778s
sys  0m0.004s

time ./srt 4-test.ppm >4-test.ppm.tmp

real 0m14.126s
user 0m56.176s
sys  0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp

real 0m7.288s
user 0m56.751s
sys  0m0.003s

The real time needed is nearly (unthreaded version time)/ numofthreads.
It's really very large improvement.

