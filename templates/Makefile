CC=g++
CPPFLAGS=-std=c++11 -Wall -Werror -g

EXECUTABLES=func_template class_template map_template typename_template

build: $(EXECUTABLES)

simple_template: func_template.cpp

class_template: class_template.cpp

map_template: map_template.cpp

typename_template: typename_template.cpp

clean:
	rm -rf *.o *.so *.a $(EXECUTABLES)
