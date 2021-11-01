#!/bin/bash

DB="hl";
USER="root";
PASS="3.14Oneer";

mysql -uroot -p3.14Oneer -h db -e "CREATE DATABASE IF NOT EXISTS $DB;";

cd build/bin && ./server -db