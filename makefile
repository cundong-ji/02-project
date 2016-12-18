CC=gcc
CPPFLAGS= -I./include -I/usr/local/include/hiredis
LIBS= -lfcgi

src = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(src))

upload = ./upload
target = $(upload)

all:$(target)
$(objects):%.o:%.c	
	$(CC) -c $< -o $@ $(LIBS) 

$(upload):./upload.o
	$(CC) $^ -o $@ $(LIBS)

.PHONY:clean all
clean:
	-rm -rf $(target) $(objects)
