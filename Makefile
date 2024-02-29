all:
	test -d bin || mkdir bin
	make -C src
	cp src/lzd bin
.PHONY: doc
doc:
	make -C doc
clean:
	make clean -C doc
	make clean -C src
