#!/bin/bash

# wrapper to the c++ executable BookConstructor.

display_usage() {
    echo
    echo "usage: $0 [-lf] [-n #] data_folder mm/dd/yyyy venue ticker"
    echo
    echo " -h, --help     Display usage instructions"
    echo " -l, --list     Display all the date venues available at data_folder/binary"
    echo " -f, --force    To force program execution if output files already exists"
    echo " -n,            Number of levels to sotre for the book, default is 5"
    echo
}

# fix naming convention
fix_naming() {
    #
    # assumes that the files with _ITCH_50 have a format like yyyymmdd.VENUE_ITCH_50.gz
    # instead of mmddyyy.VENUE_ITCH50.gz
    # this happens, as of 04-29-2019, for PSX and BX
    #
    FLAG=$( ls "$DATA_FOLDER"binary | grep --quiet _ITCH_50);
    if [ $FLAG ]; then echo; fi
    for line in $( ls "$DATA_FOLDER"binary | grep _ITCH_50); do
        read new_file < <(echo ${line:4:2}${line:6:2}${line:0:4}${line:8} | sed 's/_ITCH_50/_ITCH50/')
        mv "$DATA_FOLDER"binary/$line "$DATA_FOLDER"binary/$new_file
        echo $line has been renamed as $new_file
    done
    if [ $FLAG ]; then echo; fi
}

display_list() {
    # displays files in DATA_FOLDER as
    fix_naming
    echo
    echo "Available dates and venues: "
    echo
    echo $'mm-dd-yyyy\tVenue'

    ls "$DATA_FOLDER"binary | egrep '^[0-9]{8}.(NASDAQ|BX|PSX)_ITCH50.gz' |
    sed -n 's/[0-9]\{2\}/&-/p' |
    sed -n 's/[0-9]\{2\}-[0-9]\{2\}/&-/p' |
    sed -n 's/\([0-9]\{2\}-[0-9]\{2\}-[0-9]\{4\}\)\.\([^_]*\)_ITCH50.gz/\1\t\2/p' | tr t $'\t'
    echo
}

POSITIONAL=()
DISPLAY_LIST_FLAG=0
LEVELS_FLAG=0
FORCE_FLAG=0
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -l|--list)
    DISPLAY_LIST_FLAG=1
    shift
    ;;
    -n)
    LEVELS_FLAG=1
    LEVELS="$2"
    shift
    shift
    ;;
    -f|--force)
    FORCE_FLAG=1
    shift
    ;;
    -h|--help)
    display_usage
    shift
    exit
    ;;
    -*)
    echo
    echo Unrecognied option: $key
    echo
    display_usage
    exit
    ;;
    *)
    POSITIONAL+=("$1")
    shift
    ;;
esac
done

set -- "${POSITIONAL[@]}"

# required arguments
if [ ${#POSITIONAL[@]} -lt 4 -a $DISPLAY_LIST_FLAG -eq 0 ]; then
    display_usage
    exit
elif [ $DISPLAY_LIST_FLAG -eq 1 -a ${#POSITIONAL[@]} -eq 1 ]; then
    DATA_FOLDER=${POSITIONAL[0]}
    display_list
    exit
fi

DATA_FOLDER=${POSITIONAL[0]}
DATE=${POSITIONAL[1]}
VENUE=${POSITIONAL[2]}
STOCK=${POSITIONAL[3]}

if [[ ! -z $TMPDIR ]]; then
    TMP=$TMPDIR
else
    TMP=/tmp/
fi

# add trailing backslah if needed
[[ "${STR}" != */ ]] && STR="${STR}/"

if [[ ! -z $DATA_FOLDER ]]; then
    :
else
    echo No directory named $DATA_FOLDER
    exit
fi

# delete backshlash from date
read DATE < <(echo $DATE | tr -d /)

if [ -e "$DATA_FOLDER"binary -a -e "$DATA_FOLDER"messages -a -e "$DATA_FOLDER"book ]; then
    :
else
    echo
    echo folder structure should be:
    echo
    echo $DATA_FOLDER
    echo "|"
    echo "|-binary"
    echo "|-messages"
    echo "|-book"
    exit
fi

# if -l is invoked
if [ $DISPLAY_LIST_FLAG == 1 ]; then
    display_list
    exit
fi

# if -n is not invoked
if [ $LEVELS_FLAG == 0 ]; then
    LEVELS=5
fi

fix_naming

# check if date and venues combination is present
PROTOCOL_FORMAT=_ITCH50

# date and venue strign to check if the combination is available n the data file
STR_DATE_VENUE=${DATE:0:2}-${DATE:2:2}-${DATE:4}$'\t'$VENUE

if display_list | grep --quiet "$STR_DATE_VENUE"; then

    FILE_NAME=$DATE.$VENUE$PROTOCOL_FORMAT.gz
    INPUT_FILE_PATH="$DATA_FOLDER"binary/$FILE_NAME

    DECOMPRESSED_INPUT_FILE_PATH=$TMP$DATE.$VENUE$PROTOCOL_FORMAT

    if [ -e $DECOMPRESSED_INPUT_FILE_PATH ]; then
        :
    else
        echo
        echo copying $INPUT_FILE_PATH into a temporary folder
        cp $INPUT_FILE_PATH $TMP
        echo
    fi

    if [ -e $DECOMPRESSED_INPUT_FILE_PATH ]; then
        echo
        echo $DECOMPRESSED_INPUT_FILE_PATH already exists. Skipping decompression
        echo
    else
        echo decompressing $FILE_NAME
        gzip -d $TMP$FILE_NAME
    fi

    GZIP_STATUS=$?
    BOOK_DIR="$DATA_FOLDER"book/
    MESS_DIR="$DATA_FOLDER"messages/

    if (($GZIP_STATUS==0)); then
        BOOK_FILE_NAME="$DATE.$VENUE$PROTOCOL_FORMAT"_"$STOCK"_book_$LEVELS.csv
        MESS_FILE_NAME="$DATE.$VENUE$PROTOCOL_FORMAT"_"$STOCK"_message.csv
        if [ -e $BOOK_DIR$BOOK_FILE_NAME -a -e $MESS_DIR$MESS_FILE_NAME -a $FORCE_FLAG -eq 0 ]; then
            echo
            echo $BOOK_FILE_NAME and $MESS_FILE_NAME already exists. To force Execution run with -f option.
            echo
            exit
        else
            ./bin/BookConstructor $DECOMPRESSED_INPUT_FILE_PATH $TMP $TMP $LEVELS $STOCK
            echo
            echo moving output files to $BOOK_DIR and $MESS_DIR
            echo
            mv $TMP$BOOK_FILE_NAME $BOOK_DIR
            mv $TMP$MESS_FILE_NAME $MESS_DIR
            if [ -e $TMP$FILE_NAME ]; then
                rm $TMP$FILE_NAME
            fi
        fi
    else
        echo Decompression of $TMP$FILE_NAME not sucsesfull
    fi
else
    echo
    echo $STR_DATE_VENUE not available
    echo
    display_list
    exit
fi
