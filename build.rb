#!/usr/bin/ruby

CC = 'gcc'
FLAGS = '-std=c99'
CMD = "#{CC} #{FLAGS}"

cmd = "rm -f webby *.o"
puts cmd
puts `#{cmd}`

# cmd = "#{CMD} -c server.c"
# puts cmd
# puts `#{cmd}`

# cmd = `#{CMD} -c main.c`
# puts cmd
# puts `#{cmd}`

objects = `ls *.o`

if objects.empty?
	puts "No .o files to compile."
else
	cmd =`#{CMD} #{objects} -o webby`
	puts cmd
	puts `#{cmd}`
end
