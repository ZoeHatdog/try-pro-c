#!/bin/bash

# This script sets up the Oracle XE database by creating the database and applying the schema and seed data.

# Start Oracle XE service
echo "Starting Oracle XE service..."
service oracle-xe start

# Wait for the database to be ready
echo "Waiting for Oracle XE to be ready..."
sleep 30

# Create the database schema
echo "Applying schema..."
sqlplus sys/password@localhost:1521/XE as sysdba <<EOF
@../sql/schema.sql
EOF

# Seed the database with initial data
echo "Seeding database..."
sqlplus sys/password@localhost:1521/XE as sysdba <<EOF
@../sql/seed.sql
EOF

echo "Database setup complete."