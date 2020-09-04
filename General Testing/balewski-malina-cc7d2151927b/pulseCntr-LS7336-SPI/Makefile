INCLUDES := -I/usr/include
LIBRARIES := -L/usr/local/lib
LIBS := -lwiringPi

CC :=cc

#NAME1 := rwMDR01
NAME1 := rdCNTRviaOTR

$(NAME1): $(NAME1).o
	$(CC) $^ -o $@ $(LIBRARIES) $(LIBS)
	@echo execute:  ./$(NAME1)

%.o: %.c 
	$(CC) -c  $< $(CFLAGS) 
	echo end of compilation of  $<

clean:
	rm -f  *.o $(NAME1)

