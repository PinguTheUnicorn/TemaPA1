# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
build: crypto stocks valley ridge

crypto: crypto.o
	g++ -o crypto crypto.o

crypto.o: crypto.cpp
	g++ -c crypto.cpp

stocks: stocks.o
	g++ -o stocks stocks.o

stocks.o: stocks.cpp
	g++ -c stocks.cpp

valley: valley.o
	g++ -o valley valley.o

valley.o: valley.cpp
	g++ -c valley.cpp

ridge: ridge.o
	g++ -o ridge ridge.o

ridge.o: ridge.cpp
	g++ -c ridge.cpp

run-p1:      # nume necesar
	./crypto

run-p2:      # nume necesar
	./stocks

run-p3:      # nume necesar
	# java Valley
	./valley

run-p4:      # nume necesar
	./ridge

clean:		 # nume necesar
	# rm -f *.class
	rm -f valley
	rm -f crypto
	rm -f stocks
	rm -f ridge
	rm -f *.o
