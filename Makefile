
build:
	cd lib/ && \
	gcc -c ../core/ons_producer.cpp -O3 -Wall -Wextra -fPIC && \
	gcc -c ../core/ons_message.cpp -O3 -Wall -Wextra -fPIC && \
	ar -crs libonsrocketmq.a ons_producer.o ons_message.o

clean:
	cd lib/ && \
	rm ons_producer.o ons_message.o libonsrocketmq.a
