# Traveller Problem

In order to compile and run this program you just need to go to the /scripts folder located in the root of the project. There you can find some scripts:

1. compile.sh
2. run.sh (runs reading the numbers from a file and making a diff with the official trace)
3. runRandom.sh (runs without a file of random numbers and prints to the terminal instead of a file)
4. runAllTests.sh (runs the cases 1, 2 and 3 and checks for differences with the traces given)

Executing the first script (compile.sh) will use the cmakelists.txt file on the /src folder to create a makefile inside the /bin folder. Then it will execute a make in order to compile the whole program.

After that, when you execute any of the run*.sh you will simply run the program with the arguments provided in the folder /bin/arguments.

**NOTE:** We have removed a whitespace at the beggining of the first file, we are not sure if that was meant to be there or if we inserted it there by accident. Anyway, that was to make the output of all the diffs empty instead of a weird "SOLUCIÓN INICIAL" line.

When I say "We" I mean "I" but "We" sounds kind of professional.

