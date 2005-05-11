noinst_LIBRARIES = libengine.a
libengine_a_SOURCES = area.cpp area.hpp camera.cpp camera.hpp console.cpp \
        console.hpp entity.cpp entity.hpp entitymgr.cpp netclient.cpp netclient.hpp \
        netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp netserverclient.cpp \
        netserverclient.hpp p_plasma.cpp p_plasma.hpp particles.cpp particles.hpp  \
        physics.cpp physics.hpp projectile.cpp projectile.hpp renderer.cpp renderer.hpp \
        sector.cpp sector.hpp texture.cpp texture.hpp timer.cpp timer.hpp udpsocket.cpp \
        udpsocket.hpp util.cpp vector.cpp vector.hpp video.cpp video.hpp w_plasmacannon.cpp \
        w_plasmacannon.hpp weapon.cpp weapon.hpp radar.cpp radar.hpp types.hpp globals.hpp  \
        map_defines.hpp entitymgr.hpp stdutil.hpp engine.hpp

AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../../libs/glpng 
AM_LDFLAGS = -l../../libs/glpng.la @GL_LDFLAGS@ @SDL_LDFLAGS@

