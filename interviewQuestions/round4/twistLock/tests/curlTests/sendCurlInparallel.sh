#! /bin/bash

numOfRequest=$1
numOfWords=7
startTime=$(date +%s)

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=aha" &
p1=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=buba" &
p2=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=bgc" &
p3=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=zebra" &
p4=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=" &
p5=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=123" &
p6=$!

seq $numOfRequest | parallel -j0 curl -s "http://127.0.0.1:8000/api/v1/similar?word=@@!@*b" &
p7=$!

numOfRequestSent=$(($numOfRequest * $numOfWords))
wait $p1 $p2 $p3 $p4 $p5 $p6 $p7
endTime=$(date +%s)
testDuration=$(( $endTime - $startTime ))
echo "sendCurlParallel - test took $testDuration seconds"
echo "sendCurlParallel - Done waiting for all background processes, sent $numOfRequestSent requests, terminating..."
