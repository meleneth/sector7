noinst_PROGRAMS = s7d s7
s7d_SOURCES = sector7d.cpp sector7d.hpp renderer.cpp renderer.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp entitymgr.cpp entity.cpp entity.hpp event.cpp event.hpp vector.cpp vector.hpp game.hpp game.cpp particles.cpp particles.hpp physics.cpp physics.hpp player.cpp player.hpp weapon.cpp weapon.hpp w_plasmacannon.cpp w_plasmacannon.hpp projectile.cpp projectile.hpp p_plasma.cpp p_plasma.hpp video.cpp video.hpp texture.cpp texture.hpp util.cpp
s7d_LDADD = ../libs/glpng/libglpng.a @GL_LIBS@ @SDL_LIBS@ 
#-lSDL_mixer
s7_SOURCES = sector7.cpp sector7.hpp renderer.cpp renderer.hpp console.cpp console.hpp netclient.cpp netclient.hpp netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp udpsocket.cpp udpsocket.hpp entitymgr.cpp entity.cpp entity.hpp event.cpp event.hpp vector.cpp vector.hpp game.hpp game.cpp particles.cpp particles.hpp physics.cpp physics.hpp player.cpp player.hpp weapon.cpp weapon.hpp w_plasmacannon.cpp w_plasmacannon.hpp projectile.cpp projectile.hpp p_plasma.cpp p_plasma.hpp video.cpp video.hpp texture.cpp texture.hpp util.cpp

s7_LDADD = ../libs/glpng/libglpng.a @GL_LIBS@ @SDL_LIBS@ 
#-lSDL_mixer
#engine/libengine.a levels/liblevels.a entities/libentities.a base/libbase.a weapons/libweapons.a projectiles/libprojectiles.a
AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../libs/glpng 
#-Iinclude -Ientities -Iprojectiles -Iweapons -Iengine -Ibase -Ilevels
#SUBDIRS = base entities weapons projectiles levels engine include tests levels

