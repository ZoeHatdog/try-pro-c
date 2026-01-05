# Project Title: Pro*C Oracle XE Application

## Overview
This project is a Pro*C application that integrates with Oracle XE as the database. It provides a structured way to connect to the database, execute queries, and manage data. The application is designed to be easily built and run using provided scripts and Docker configurations.

## Project Structure
```
proc-oracle-xe-app
├── src
│   ├── main.pc          # Main entry point for the application
│   ├── db
│   │   ├── connection.pc # Handles database connections
│   │   └── queries.pc    # Contains SQL query definitions
│   └── include
│       └── db.h         # Header file for database operations
├── sql
│   ├── schema.sql       # SQL schema for database structure
│   └── seed.sql         # Initial data for testing
├── scripts
│   ├── build.sh         # Build script for compiling Pro*C files
│   ├── run.sh           # Script to run the compiled application
│   └── setup_db.sh      # Script to set up the Oracle XE database
├── docker
│   ├── docker-compose.yml # Docker configuration for services
│   └── oracle-xe.Dockerfile # Dockerfile for Oracle XE image
├── Makefile              # Build instructions for the project
├── .env.example          # Template for environment variables
└── README.md             # Project documentation
```

## Setup Instructions
1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd proc-oracle-xe-app
   ```

2. **Build the Application**
   Run the build script to compile the Pro*C files:
   ```bash
   ./scripts/build.sh
   ```

3. **Set Up the Database**
   Use the setup script to create the database and apply the schema:
   ```bash
   ./scripts/setup_db.sh
   ```

4. **Run the Application**
   Execute the run script to start the application:
   ```bash
   ./scripts/run.sh
   ```

## Usage
After setting up the database and building the application, you can run the application to interact with the Oracle XE database. The application will execute predefined queries and display results as specified in the code.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.