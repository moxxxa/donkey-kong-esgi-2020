LIB = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
GCC=g++

donkey-kong: *.cpp
	$(GCC) -o $@ $^ $(LIB)

%.o: %.c
	$(GCC) -c $< $(LIB)

clean:
	-rm -rf $(TARGET)

