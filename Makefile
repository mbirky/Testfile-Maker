CXX=g++
CFLAGS=-Wall -g

testfile_maker: main.o
	$(CXX) -o $@ $< $(CFLAGS)

clean:
	@rm testfile_maker main.o
