all:
	gcc subscriber_generator.c -o subscriber_generator  $(pkg-config --libs --cflags libmongoc-1.0)
	./subscriber_generator 5
	gcc register_subscriber.c -o register_subscriber -I/usr/include/libmongoc-1.0 -I/usr/include/libbson-1.0 -lmongoc-1.0 -lssl -lcrypto -lrt -lresolv -lz -lsnappy -lbson-1.0
	./register_subscriber
