hotelFinder: hotel.o func.o
	g++ hotel.o func.o -o hotelFinder
hotel.o: hotel.cpp
	g++ -c hotel.cpp
func.o: func.cpp func.h
	g++ -c func.cpp
clean:
	rm *.o mycalc