INCLUDES := -I/usr/include
LIBRARIES := -L/usr/local/lib
LIBS := -lwiringPi

CC :=cc

NAME := spi_max144

$(NAME): $(NAME).o
	$(CC) $^ -o $@ $(LIBRARIES) $(LIBS)
	@echo execute:  sudo ./$(NAME)

%.o: %.c 
	$(CC) -c  $< $(CFLAGS) 
	echo end of compilation of  $<

clean:
	rm -f  *.o $(NAME)

