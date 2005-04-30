noinst_LTLIBRARIES = libengine.la
        libengine_la_SOURCES = area.cpp area.hpp camera.cpp camera.hpp console.cpp \
        console.hpp entity.cpp entity.hpp entitymgr.cpp netclient.cpp netclient.hpp \
        netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp netserverclient.cpp \
        netserverclient.hpp p_plasma.cpp p_plasma.hpp particles.cpp particles.hpp  \
        physics.cpp physics.hpp projectile.cpp projectile.hpp renderer.cpp renderer.hpp \
        sector.cpp sector.hpp texture.cpp texture.hpp timer.cpp timer.hpp udpsocket.cpp \
        udpsocket.hpp util.cpp vector.cpp vector.hpp video.cpp video.hpp w_plasmacannon.cpp \
        w_plasmacannon.hpp weapon.cpp weapon.hpp 

AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../../libs/glpng 
libengine_la_LIBFLAGS = -l../../libs/glpng.la @GL_LDFLAGS@ @SDL_LDFLAGS@

