# CS:APP assignment 5.18
`Computer Systems: A Programmer's Perspective`

This is formerly an assignment to optimize the algorithm shown in practice 5.5 and 5.6. We attempt to use the methods introduced in chapter 5 to attain minimum CPE. And now we made this repo a basic benchmarking program which will run through every test cases consisting of different loop unrolling and loop splitting method, and will give a result on which of the method is the best depending on your machine.

## We require your help :D

Please kindly run this program the default way and copy the result to this markdown website [here](https://hackmd.io/JbIPKc1lQtmOTWdNqDUh1g).

## Dependencies

For performance measurement, you must have the package `cpupower` installed in your machine. For installation, run the below command on Ubuntu:
```
$ sudo apt install linux-tools-common linux-tools-generic
```
and then check the other package needed (if necessary, machine wise so we can't list them here) and install them. Mostly are linux kernel tools.

We use **gnuplot** to plot the performance comparison graph. So you need it installed in your system.
```
$ sudo apt install gnuplot
```

## Running the test
There are altogether 3 types of tests provided by our program.

### Default test
For basic benchmarking, run the below command gives the follwing result:
```
$ make default
./test_poly default
Please copy the result between lines
--------------------
Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz
CPU max freq = 3400000000 hz
1,10: 1.557728  
1,7: 1.579318
1,9: 1.581421
1,6: 1.584928
1,8: 1.591485
--------------------
Program closing...
```
To help us out, please copy the result between the lines to the following markdown page
[HackMD](https://hackmd.io/JbIPKc1lQtmOTWdNqDUh1g)

### Plot test
For visualized test result, plotted with gnuplot, run the following command:
```
$ make plot ARGS="x,y x,y x,y"
```
x and y can be any number ranged from 1 to 8, which indicates the number of loop and number of splitting. For example:
```
$ make plot ARGS="1,1 2,5 3,8"
```

### Compare test
Shows only the CPE evaluated from several functions indicated by the argument:
```
$ make compare ARGS="1,1 2,2 3,3"
```

For more information, kindly refer to the comment in the code or open an issue.
