OBJECTS = main.o

Project5: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@

clean:
	rm -i *.o Project5

run:
	./Project5 finkelMarkov.txt myMarkov.txt

