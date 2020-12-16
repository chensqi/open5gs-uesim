all:
	gcc subscriber_generator.c -o subscriber_generator  $(pkg-config --libs --cflags libmongoc-1.0)
	./subscriber_generator 5
	gcc register_subscriber.c -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0  -o register_subscriber
	./register_subscriber
