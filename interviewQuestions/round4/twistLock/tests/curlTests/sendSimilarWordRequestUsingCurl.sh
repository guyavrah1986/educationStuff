#! /bin/bash

mycurl() {
    curl -s "http://127.0.0.1:8000/api/v1/similar?word=aha"
}
export -f mycurl

seq 100000 | parallel -j0 mycurl

