INCLUDES := -I/usr/include
LIBRARIES := -L/usr/local/lib
# for time measurement needs  -lrt  for Linux
LIBS += -lrt 
# for trig func need -lm
LIBS += -lm

# on Mac OsX use


CC :=cc

NAME := interval2

$(NAME): $(NAME).o
	$(CC) $^ -o $@   $(LIBRARIES) $(LIBS)
	@echo execute:   ./$(NAME)

%.o: %.c 
	$(CC) -c  $< $(CFLAGS) 
	echo end of compilation of  $<

clean:
	rm -f  *.o $(NAME)

