#!/bin/bash

# Set environment variables for Oracle XE connection
export ORACLE_HOME=/path/to/oracle/home
export LD_LIBRARY_PATH=$ORACLE_HOME/lib
export PATH=$ORACLE_HOME/bin:$PATH

# Run the compiled Pro*C application
./path/to/compiled/application_executable

# Check if the application ran successfully
if [ $? -eq 0 ]; then
    echo "Application executed successfully."
else
    echo "Application execution failed."
fi