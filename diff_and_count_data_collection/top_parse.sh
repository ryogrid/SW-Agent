#! /bin/sh

# refresh rate is 1 second
top -d 1 | grep $1 | ./top_parse.rb
