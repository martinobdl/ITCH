import pandas as pd

def parseNanosecondsToDateTime(nanosecs,date=None):
    """ Converts from nanosecs to pandas timestamp.
    """

    time = pd.Timedelta(nanosecs, unit ='ns')

    if date:
        date_str = pd.Timestamp.strptime(date,'%m%d%Y')
    else:
        date_str = pd.Timestamp.strptime('01012001','%m%d%Y')
    return date_str + time

def get_last_execution(message_df,t,idx=1):
    """ get the last execution happend before time stamp t
    """
    types = ['E']
    sliced = message_df[message_df.time<=t]
    if len(sliced.loc[message_df.type == 'E'])>=idx:
        return sliced.loc[message_df.type == 'E'].iloc[-idx]
    else:
        return pd.DataFrame(columns = message_df.columns)

def normalize(vector):
    return vector/len(vector)
