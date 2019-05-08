import pandas as pd

def parseNanosecondsToDateTime(date,nanosecs):
    date = pd.Timestamp.strptime(date,'%m%d%Y')
    date = date + pd.Timedelta(nanosecs, unit ='ns')
    return date

def get_last_execution(message_df,t,idx=1):
    """ get the last execution happend before time stamp t
    """
    types = ['E']
    sliced = message_df[message_df.time<=t]
    if len(sliced.loc[message_df.type == 'E'])>=idx:
        return sliced.loc[message_df.type == 'E'].iloc[-idx]
    else:
        return pd.DataFrame(columns = message_df.columns)
