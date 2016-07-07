#!/usr/bin/ruby

ARGF.each{ |line|
    splited = line.split(/\s+/)
    begin
       puts splited[9]
    rescue
    end
}
