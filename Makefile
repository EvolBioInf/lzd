all:
	test -d bin || mkdir bin
	make -C src
	cp src/lzd bin
doc:
	make -C doc
clean:
	make clean -C doc
	make clean -C src
