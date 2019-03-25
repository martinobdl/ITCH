# ITCH
ITCH 5.0 parser

build with
  g++ -std=c++11 ITCH_50_parser.cpp -o ITCH_50_parser
  
exec with:
  ./ITCH_50_parser path/of/the/ITCH_50
  
specs @: https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHspecification.pdf

ITCH data: ftp://emi.nasdaq.com/ITCH/

##############################################

added headers for the general structure of the program.

##############################################

Example of test compilation (from tests folder): g++ -std=c++11 mexTest.cpp ../c++/Message.cpp ../c++/Reader.cpp -o testMex
