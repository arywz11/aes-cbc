 src=$(wildcard *.c)
 obj=$(patsubst %.c, ./objs/%.o, $(notdir $(src)))
 target=app.out

 $(shell if [ ! -d "./objs/" ] ; then mkdir ./objs/; fi;)
 
 CFLAGS+=--std=c99
 $(target):$(obj)
	gcc -o $@ $^
	
./objs/%.o:./%.c
	gcc -c  $< -o $@

clean:
	rm -rf $(target) $(obj)
