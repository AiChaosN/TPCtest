
if [ "$1" == "exe" ]; then
    run_file="../bin"
    for file in $run_file/q*; do
        # get file name without suffix, remove path part
        base_name=$(basename "$file")

        # run each q*.exe
        start_time=$(date +%s%N)/1000000
        # ./$file > /dev/null 2>&1
        ./$file >> a.out
        echo "$base_name run end, time: $(( $(date +%s%N)/1000000 - start_time )) ms"
    done
    echo "Run complete."
elif [ "$1" == "bc" ]; then
    run_file="../bitcode"
    for file in $run_file/q*.bc; do
        # get file name without suffix, remove path part
        base_name=$(basename "$file")

        start_time=$(date +%s%N)/1000000
        lli $file > /dev/null 2>&1
        echo "$base_name run end, time: $(( $(date +%s%N)/1000000 - start_time )) ms"
    done
    echo "Run complete."
fi



