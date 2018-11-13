# CS:APP assignment 5.18
`Computer Systems: A Programmer's Perspective`

This is an assignment to optimize the algorithm shown in practice 5.5 and 5.6. We attempt to use the methods introduced in chapter 5 to attain minimum CPE.

## Dependencies

The following test code were tested in Ubuntu 18.04. Before running the code you are advised to first install the dependencies which included the 'PAPI' library (Performance Application Programming Interface).

```
$ sudo apt-get install libpapi-dev
```
We use **gnuplot** to plot the performance comparison graph. So you need it installed in your system.

For Arch linux user, the package contaning the papi-library is named `papi` and can be found in the AUR(Arch User Repository).

## Running the test
```
$ make
```
Run the above command to compile the source code

```
$ make plot1
```
There are altogether three options which are -- plot1, plot2, plot3, each of them generates comparison graph between different targets.
*   `$ make plot1`
    Generates comparison graph between original algorithm of 5.5 and 5.6.
*   `$ make plot2`
    Generates comparison graph between original algorithm of 5.5 and optimized 5.5.
*   `$ make plot3`
    Generates comparison graph between original algorithm of 5.6 and optimized 5.6.
