all : MakeAll

DIRS =	Common	\
	BEE	\
	Exec	\
	Test
BIN  = bin

MakeAll:
	if [ ! -d $(BIN) ]; then \
		mkdir $(BIN); \
	fi

	for i in $(DIRS); do \
                (cd $$i; make); \
	done;

clean:
	for i in $(DIRS); do \
		(cd $$i; make clean); \
	done;
	rm -rf $(BIN)
