import pandas as pd

def parseNanosecondsToDateTime(date,nanosecs):
    date = pd.Timestamp.strptime(date,'%m%d%Y')
    date = date + pd.Timedelta(nanosecs, unit ='ns')
    return date
