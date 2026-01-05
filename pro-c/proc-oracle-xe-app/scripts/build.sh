#!/bin/bash

# Set the Oracle environment variables
export ORACLE_HOME=/path/to/oracle/home
export LD_LIBRARY_PATH=$ORACLE_HOME/lib:$LD_LIBRARY_PATH
export PATH=$ORACLE_HOME/bin:$PATH

# Compile the Pro*C source files
proc main.pc
proc db/connection.pc
proc db/queries.pc

# Link the object files to create the executable
gcc -o my_app main.o connection.o queries.o -L$ORACLE_HOME/lib -lclntsh

# Clean up the object files
rm -f *.o

echo "Build completed successfully."