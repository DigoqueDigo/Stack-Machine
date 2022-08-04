CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
LIBS = -lm
OBJS = main.o stack.o guiao1.o guiao2.o guiao3.o guiao4.o guiao5.o
TARGET = stack
DOC_FILE = Doxyfile


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


run:
	./stack


doc: $(DOC_FILE)
	doxygen $(DOC_FILE)


coverxygen: doc
	python3 -m coverxygen --xml-dir ./xml --src-dir ./ --output doc-coverage.info;\
	lcov --summary doc-coverage.info;\
	genhtml --no-function-coverage --no-branch-coverage doc-coverage.info -o .


clean_object: $(TARGET)
	rm *.o


clean_doc: doc coverxygen
	rm -r html/ latex/ Stack-Machine xml;\
	rm emerald.png amber.png gcov.css glass.png index.html index-sort-l.html ruby.png snow.png updown.png doc-coverage.info;