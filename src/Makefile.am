noinst_PROGRAMS = s7d s7 s7t
s7d_SOURCES = sector7d.cpp sector7d.hpp 

s7_SOURCES = sector7.cpp sector7.hpp 

s7t_SOURCES = sector7t.cpp 

AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../libs/glpng -Iengine

SUBDIRS = engine
LDADD = engine/libengine.la ../libs/glpng/libglpng.a -lncurses @GL_LIBS@ @SDL_LIBS@

