#include "Parser.hpp"

Parser::Parser(const std::string &inFileName, const std::string &outFileName){
    inFile.open(inFileName);
    if(!inFile.is_open()){
        std::cerr << "Can't open input file " << inFileName << std::endl;
    }
    else
        std::cout << "Opened "+inFileName+" to parse." << std::endl;
    outFile.open(outFileName);
    count = 0;
    start = time(0);
}

void Parser::readMessage(const long &size){
    // memset(message, 0x00, 64);
    inFile.read(message, size);
}

void Parser::convertMessage(const char &key){
    printProgress();
    char str[100] = {0};
    if(key=='S'){
        readMessage(11);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char eventCode = message[10];

        sprintf(str,"%c,%u,%u,%llu,%c\n",key,locateCode,trackingNumb,timeStamp,eventCode);
    }
    else if(key=='R'){
        readMessage(38);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        char marketCategory = message[18];
        char financialStatus = message[19];
        uint32_t numberOfSharesInALot = parse_uint32(message+20);
        char roundLotsOnly = message[24];
        char issueClassification = message[25];
        char subType[3]; strncpy(subType, message+26, 2); subType[2] = 0;
        char autenticity = message[28];
        char shortIndicator = message[29];
        char ipoFlag = message[30];
        char indicatorLULD = message[31];
        char flagETP = message[32];
        uint32_t ETPLevarage = parse_uint32(message+33);
        char inverseETPFlag = message[37];

        sprintf(str,"%c,%u,%u,%llu,%s,%c,%c,%u,%c,%c,%s,%c,%c,%c,%c,%c,%u,%c\n",
            key,locateCode,trackingNumb,timeStamp,stock,marketCategory,financialStatus,
            numberOfSharesInALot,roundLotsOnly,issueClassification,subType,autenticity,
            shortIndicator,ipoFlag,indicatorLULD,flagETP,ETPLevarage,inverseETPFlag);
    }
    else if(key=='H'){
        readMessage(24);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        char tradingState = message[18];
        char reserved = message[19];
        char reason[5]; strncpy(reason, message+20, 4); reason[4] = 0;
        sprintf(str,"%c,%u,%u,%llu,%s,%c,%c,%s\n",
            key,locateCode,trackingNumb,timeStamp,stock,tradingState,reserved,reason);
    }
    else if(key=='Y'){
        readMessage(19);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        char regSHO = message[18];
        sprintf(str,"%c,%u,%u,%llu,%s,%c\n",
            key,locateCode,trackingNumb,timeStamp,stock,regSHO);
    }
    else if(key=='L'){
        readMessage(25);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char mpidIdentifier[5]; strncpy(mpidIdentifier, message+10, 4); mpidIdentifier[4] = 0;
        char stock[9]; strncpy(stock, message+14, 8); stock[8] = 0;
        char primaryMarketMaker = message[22];
        char marketMakerMode = message[23];
        char makerParticipantState = message[24];
        sprintf(str,"%c,%u,%u,%llu,%s,%s,%c,%c,%c\n",
            key,locateCode,trackingNumb,timeStamp,mpidIdentifier,stock,
            primaryMarketMaker,marketMakerMode,makerParticipantState);
    }
    else if(key=='V'){
        readMessage(34);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t level1 = parse_uint64(message+10);
        uint64_t level2 = parse_uint64(message+18);
        uint64_t level3 = parse_uint64(message+26);
        sprintf(str,"%c,%u,%u,%llu,%llu.%08llu,%llu.%08llu,%llu.%08llu\n",
            key,locateCode,trackingNumb,timeStamp,
            level1/100000000,level1%100000000,
            level2/100000000,level2%100000000,
            level3/100000000,level3%100000000);
    }
    else if(key=='W'){
        readMessage(11);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char breachedLevel = message[10];
        sprintf(str,"%c,%u,%u,%llu,%c\n",
            key,locateCode,trackingNumb,timeStamp,breachedLevel);
    }
    else if(key=='K'){
        readMessage(27);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        uint32_t timeIPO = parse_uint32(message+18);
        char qualifierIPO = message[22];
        uint32_t priceIPO = parse_uint32(message+23);
        sprintf(str,"%c,%u,%u,%llu,%s,%u,%c,%u.%4u\n",
            key,locateCode,trackingNumb,timeStamp,stock,timeIPO,qualifierIPO,
            priceIPO/10000,priceIPO%10000);
    }
    else if(key=='J'){
        readMessage(34);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        uint32_t auctionCollarPrice = parse_uint32(message+18);
        uint32_t upperAuctionCollarPrice = parse_uint32(message+22);
        uint32_t lowerAuctionCollarPrice = parse_uint32(message+26);
        char auctionCollarExtension = message[30];
        sprintf(str,"%c,%u,%u,%llu,%s,%u.%4u,%u.%4u,%u.%4u,%c\n",
            key,locateCode,trackingNumb,timeStamp,stock,
            auctionCollarPrice/10000,auctionCollarPrice%10000,
            upperAuctionCollarPrice/10000,upperAuctionCollarPrice%10000,
            lowerAuctionCollarPrice/10000,lowerAuctionCollarPrice%10000,
            auctionCollarExtension);
    }
    else if(key=='h'){
        readMessage(20);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        char stock[9]; strncpy(stock, message+10, 8); stock[8] = 0;
        char marketCode = message[18];
        char haltAction = message[19];
        sprintf(str,"%c,%u,%u,%llu,%s,%c,%c\n",
            key,locateCode,trackingNumb,timeStamp,stock,marketCode,haltAction);
    }
    else if(key=='A'){
        readMessage(35);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        char direction = message[18];
        uint32_t size = parse_uint32(message+19);
        char stock[9]; strncpy(stock, message+23, 8); stock[8] = 0;
        uint32_t price = parse_uint32(message+31);
        sprintf(str,"%c,%u,%u,%llu,%llu,%c,%u,%s,%u.%4u\n",
            key,locateCode,trackingNumb,timeStamp,orderId,
            direction,size,stock,
            price/10000,price%10000);
    }
    else if(key=='F'){
        readMessage(39);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        char direction = message[18];
        uint32_t size = parse_uint32(message+19);
        char stock[9]; strncpy(stock, message+23, 8); stock[8] = 0;
        uint32_t price = parse_uint32(message+31);
        char mpid[5]; strncpy(mpid, message+35, 4); mpid[4] = 0;
        sprintf(str,"%c,%u,%u,%llu,%llu,%c,%u,%s,%u.%04u,%s\n",
            key,locateCode,trackingNumb,timeStamp,orderId,
            direction,size,stock,
            price/10000,price%10000,mpid);
    }
    else if(key=='E'){
        readMessage(30);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        uint32_t execSize = parse_uint32(message+18);
        uint64_t matchNumber = parse_uint64(message+22);
        sprintf(str,"%c,%u,%u,%llu,%llu,%u,%llu\n",
            key,locateCode,trackingNumb,timeStamp,orderId,
            execSize,matchNumber);
    }
    else if(key=='C'){
        readMessage(35);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        uint32_t execSize = parse_uint32(message+18);
        uint64_t matchNumber = parse_uint64(message+22);
        char printable = message[30];
        uint32_t price = parse_uint32(message+31);
        sprintf(str,"%c,%u,%u,%llu,%llu,%u,%llu,%c,%u.%4u\n",
            key,locateCode,trackingNumb,timeStamp,orderId,
            execSize,matchNumber,printable,
            price/10000,price%10000);
    }
    else if(key=='X'){
        readMessage(22);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        uint32_t cancSize = parse_uint32(message+18);
        sprintf(str,"%c,%u,%u,%llu,%llu,%u\n",
            key,locateCode,trackingNumb,timeStamp,orderId,cancSize);
    }
    else if(key=='D'){
        readMessage(18);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        sprintf(str,"%c,%u,%u,%llu,%llu\n",
            key,locateCode,trackingNumb,timeStamp,orderId);
    }
    else if(key=='U'){
        readMessage(34);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t oldOrderId = parse_uint64(message+10);
        uint64_t newOrderId = parse_uint64(message+18);
        uint32_t newSize = parse_uint32(message+26);
        uint32_t newPrice = parse_uint32(message+30);
        sprintf(str,"%c,%u,%u,%llu,%llu,%llu,%u,%u.%4u\n",
            key,locateCode,trackingNumb,timeStamp,oldOrderId,
            newOrderId,newSize,newPrice/10000,newPrice%10000);
    }
    else if(key=='P'){
        readMessage(43);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        char direction = message[18];
        uint32_t size = parse_uint32(message+19);
        char stock[9]; strncpy(stock, message+23, 8); stock[8] = 0;
        uint32_t price = parse_uint32(message+31);
        uint64_t matchId = parse_uint64(message+35);
        sprintf(str,"%c,%u,%u,%llu,%llu,%c,%u,%s,%u.%4u,%llu\n",
            key,locateCode,trackingNumb,timeStamp,orderId,
            direction,size,stock,price/10000,price%10000,matchId);
    }
    else if(key=='Q'){
        readMessage(39);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t size = parse_uint64(message+10);
        char stock[9]; strncpy(stock, message+18, 8); stock[8] = 0;
        uint32_t price = parse_uint32(message+26);
        uint64_t matchId = parse_uint64(message+30);
        char crossType = message[38];
        sprintf(str,"%c,%u,%u,%llu,%llu,%s,%u.%4u,%llu,%c\n",
            key,locateCode,trackingNumb,timeStamp,size,
            stock,price/10000,price%10000,matchId,crossType);
    }
    else if(key=='B'){
        readMessage(18);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t matchId = parse_uint64(message+10);
        sprintf(str,"%c,%u,%u,%llu,%llu\n",
            key,locateCode,trackingNumb,timeStamp,matchId);
    }
    else if(key=='I'){
        readMessage(49);
        uint16_t locateCode = parse_uint16(message);
        uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t pairedShares = parse_uint64(message+10);
        uint64_t imbalanceShares = parse_uint64(message+18);
        char imbalanceDirection = message[26];
        char stock[9]; strncpy(stock, message+27, 8); stock[8] = 0;
        uint32_t fairPrice = parse_uint32(message+35);
        uint32_t nearPrice = parse_uint32(message+39);
        uint32_t referencePrice = parse_uint32(message+43);
        char crossType = message[47];
        char priceVariationIndicator = message[48];
        sprintf(str,"%c,%u,%u,%llu,%llu,%llu,%c,%s,%u.%4u,%u.%4u,%u.%4u,%c,%c\n",
            key,locateCode,trackingNumb,timeStamp,pairedShares,
            imbalanceShares,imbalanceDirection,stock,
            fairPrice/10000,fairPrice%10000,
            nearPrice/10000,nearPrice%10000,
            referencePrice/10000,referencePrice%10000,
            crossType,priceVariationIndicator);
    }
    else{
        std::cerr << "Type " << key <<" not found @ line: "<< count << std::endl;
    }
    writeMessage(std::string(str));
}

void Parser::writeMessage(const std::string &str){
    outFile << str;
}

void Parser::closeStreams(){
    inFile.close();
    outFile.close();
    std::cout << "Finished, processed " << count << " messages in "
            << difftime(time(0),start) << " seconds."  << std::endl;
}

void Parser::process(){
    char c;
    while(!inFile.eof()){
        inFile.ignore(2);
        inFile.get(c);
        convertMessage(c);
    }
    closeStreams();
}

void Parser::printProgress(void){
    count ++;
    if((count % (5000000))==0){
        std::cout << "Processed " << count/1000000 << "Mio messages. "
        << count/difftime(time(0), start) << " messages per sec." << std::endl;
    }
}
