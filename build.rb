#!/usr/bin/ruby

CC = 'gcc'
FLAGS = '-std=c99'
CMD = "#{CC} #{FLAGS}"

puts `rm -f webby *.o`

cmd = "#{CMD} -c server.c"
puts cmd
puts `#{cmd}`

cmd = `#{CMD} -c main.c`
puts cmd
puts `#{cmd}`

objects = `ls *.o`
cmd =`#{CMD} #{objects} -o webby`
puts cmd
puts `#{cmd}`
