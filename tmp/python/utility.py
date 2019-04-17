import pandas as pd

def parseNanosecondsToDateTime(fileName,nanosecs):
    date = pd.Timestamp.strptime(fileName.split('/')[-1].split('.')[0],'%Y%m%d')
    date = date + pd.Timedelta(nanosecs, unit ='ns')
    return date
