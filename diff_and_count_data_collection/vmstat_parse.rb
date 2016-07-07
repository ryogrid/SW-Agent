#!/usr/bin/ruby

ARGF.each{ |line|
    splited = line.split(/\s+/)
    begin
       puts splited[13] + "," + splited[14] + "," + splited[15] + "," + splited[16]
    rescue
    end
}
