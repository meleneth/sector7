noinst_PROGRAMS = s7d s7
s7d_SOURCES = ncu.cpp ncu.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp
s7d_LDADD = ../libs/glpng/libglpng.a @GL_LIBS@ @SDL_LIBS@ 
#-lSDL_mixer
s7_SOURCES = ncu.cpp ncu.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp
#entitymgr.cpp entity.cpp entity.hpp
s7_LDADD = ../libs/glpng/libglpng.a @GL_LIBS@ @SDL_LIBS@ 
#-lSDL_mixer
#engine/libengine.a levels/liblevels.a entities/libentities.a base/libbase.a weapons/libweapons.a projectiles/libprojectiles.a
AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../libs/glpng 
#-Iinclude -Ientities -Iprojectiles -Iweapons -Iengine -Ibase -Ilevels
#SUBDIRS = base entities weapons projectiles levels engine include tests levels

