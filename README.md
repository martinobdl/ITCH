# ITCH

<b>Nasdaq Total View ITCH 5.0 Book Reconstructor.</b>

Nasdaq Total View is the data feed distributed from Nasdaq to clients in order to reconstuct the full depth order book. The data feed is in binary format and the specifications are listed below.

The aim of the project is to have a set of tools to transform the data feed into analyzable data.

############################################################################################

<b>parser</b>

The parser just transform bynary data in a csv file, following the specifications listed below.

specs @: https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHspecification.pdf

ITCH data: ftp://emi.nasdaq.com/ITCH/

############################################################################################

<b>Book ReConstructor</b>

Main tool. From a single parsed csv (coming from the parser) it outputs two csv for the specified security.

1) Message.csv: which is a user friendly format of the input data. Nasdaq data feed is optimized for space and hence it is not easy to analyze, e.g. a cancellation order ( type D in the specification ) refer to an already existing order without reporting neither the name of the security, size of the order or its price.
In the output message of the reconstructor the data is indiced by the columns:

type    time    id  side    size    price   cancSize    execSize    oldId   oldSize oldPrice

type:
time:
id:
side:
size:
price:
cancSize:
execSize:
oldId:
oldSize:
oldPrice:

2) Book.csv: contains the order book up to the specified number of levels. The structure is:

time    bestBidPrice    bestBidSize bestAskPrice    bestAskSize     2ndBestBidPrice    2ndBestBidSize ....

###########################################################################################
