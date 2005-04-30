noinst_PROGRAMS = s7d s7 s7t
s7d_SOURCES = netserverclient.cpp netserverclient.hpp sector7d.cpp sector7d.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp entitymgr.cpp entity.cpp entity.hpp vector.cpp vector.hpp particles.cpp particles.hpp physics.cpp physics.hpp weapon.cpp weapon.hpp w_plasmacannon.cpp w_plasmacannon.hpp projectile.cpp projectile.hpp p_plasma.cpp p_plasma.hpp video.cpp video.hpp texture.cpp texture.hpp util.cpp sector.cpp sector.hpp timer.cpp timer.hpp
s7d_LDADD = ../libs/glpng/libglpng.a -lncurses @GL_LIBS@ @SDL_LIBS@ 
#-lSDL_mixer
s7_SOURCES = netserverclient.cpp netserverclient.hpp sector7.cpp sector7.hpp renderer.cpp renderer.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp entitymgr.cpp entity.cpp entity.hpp vector.cpp vector.hpp particles.cpp particles.hpp physics.cpp physics.hpp weapon.cpp weapon.hpp w_plasmacannon.cpp w_plasmacannon.hpp projectile.cpp projectile.hpp p_plasma.cpp p_plasma.hpp video.cpp video.hpp texture.cpp texture.hpp util.cpp sector.cpp sector.hpp timer.cpp timer.hpp

s7_LDADD = ../libs/glpng/libglpng.a -lncurses @GL_LIBS@ @SDL_LIBS@ 

s7t_SOURCES = sector7t.cpp entity.cpp entitymgr.cpp sector.cpp vector.cpp texture.cpp util.cpp udpsocket.cpp netpacket.cpp console.cpp netserver.cpp netserver.hpp netserverclient.cpp netserverclient.hpp
s7t_LDADD = ../libs/glpng/libglpng.a -lncurses @GL_LIBS@ @SDL_LIBS@
#-lSDL_mixer
#engine/libengine.a levels/liblevels.a entities/libentities.a base/libbase.a weapons/libweapons.a projectiles/libprojectiles.a
AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../libs/glpng 
#-Iinclude -Ientities -Iprojectiles -Iweapons -Iengine -Ibase -Ilevels
#SUBDIRS = base entities weapons projectiles levels engine include tests levels

