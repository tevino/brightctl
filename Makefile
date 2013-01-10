all: clean build
build:
	mkdir -p bin
	gcc brightctl.c -o bin/brightctl
clean:
	rm bin/brightctl -f
install:
	install -o root -g root -m 755 bin/brightctl /usr/bin/
	chmod +s /usr/bin/brightctl