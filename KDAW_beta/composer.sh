#!/bin/zsh -e
if [ "$#" -eq 0 ]; then
    echo "usage: $0 [textfile] ... [textfile]"
    exit 1
fi

for arg in "$@"; do
    case "$arg" in
        *.txt)
            ;;
        *)
            echo "input file name must be *.txt"
            exit 1
            ;;
    esac
done

echo -n "tempo: "
read tempo

filewav_all=()
for arg in "$@"; do
    filename_raw="${arg:0:-4}.raw"
    filename_wav="${arg:0:-4}.wav"
    filewav_all+=($filename_wav)
    ./compose $tempo $arg $filename_raw
    sox -b 16 -c 1 -e s -r 44100 $filename_raw $filename_wav
    rm $filename_raw
done

if [ "$#" -gt 1 ]; then
    echo -n "output file name: "
    read outputfile

    case "$outputfile" in
        *.wav)
            sox -m $filewav_all[@] $outputfile
            ;;
        *)
            echo "output file name must be *.wav"
            ;;
    esac

    for arg; do
        rm ${arg:0:-4}.wav
    done
fi
