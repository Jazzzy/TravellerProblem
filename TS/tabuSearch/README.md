# Traveller Problem

In order to compile and run this program you just need to go to the /scripts folder located in the root of the project. There you can find some scripts:

1. compile.sh
2. run.sh (runs reading the numbers from a file and making a diff with the official trace)
3. runRandom.sh (runs generating random numbers each time)
4. runAllTests.sh (runs cases 1, 2 and 3 to test for differences with the correct traces)

Executing the first script (compile.sh) will use the cmakelists.txt file on the /src folder to create a makefile inside the /bin folder. Then it will execute a make in order to compile the whole program.

After that, when you execute any of the run*.sh you will simply run the program with the arguments provided in the folder /bin/arguments.
