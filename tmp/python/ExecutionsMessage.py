#!/usr/bin/env python2.7
import sys
import pandas as pd
from datetime import datetime as dt
from matplotlib import pyplot as plt
import utility

if __name__ == "__main__":

    fileName = str(sys.argv[1])
    outFile = ".".join(fileName.split('.')[:-1])+'_Executions.csv'
    try:
        print "Reading file " + fileName
        df = pd.read_csv(fileName);
    except:
        print "Error in reading the file."
    try:
        print "Converting time..."
        df.time = df.time.map(lambda t: utility.parseNanosecondsToDateTime(fileName,t))
    except:
        print "Error in date conversion."

    print "Writing messages..."
    df_Executions = df[(df.type == "P") | (df.type == "E")]
    df_Executions.to_csv(outFile,index=False)
    print outFile+" closed."

    print "Done."
