noinst_LIBRARIES = libengine.a
libengine_a_SOURCES = area.cpp area.hpp camera.cpp camera.hpp console.cpp \
        console.hpp entity.cpp entity.hpp entitymgr.cpp netclient.cpp netclient.hpp \
        netpacket.cpp netpacket.hpp netserver.cpp netserver.hpp netserverclient.cpp \
        netserverclient.hpp p_plasma.cpp p_plasma.hpp particles.cpp particles.hpp  \
        physics.cpp physics.hpp projectile.cpp projectile.hpp renderer.cpp renderer.hpp \
        sector.cpp sector.hpp texture.cpp texture.hpp timer.cpp timer.hpp udpsocket.cpp \
        udpsocket.hpp util.cpp vector.cpp vector.hpp video.cpp video.hpp w_plasmacannon.cpp \
        w_plasmacannon.hpp weapon.cpp weapon.hpp radar.cpp radar.hpp types.hpp globals.hpp  \
        map_defines.hpp entitymgr.hpp stdutil.hpp engine.hpp asteroid.cpp asteroid.hpp

AM_CXXFLAGS = @SDL_CFLAGS@ @GL_CFLAGS@ -I../../libs/glpng 
AM_LDFLAGS = -l../../libs/glpng.la @GL_LDFLAGS@ @SDL_LDFLAGS@

entity_wrap.cxx : entity.i entity.hpp 
	$(SWIG) -c++ -python entity.i

entity_wrap.o : entity_wrap.cxx
	g++ -c entity_wrap.cxx @SDL_CFLAGS@ @GL_CFLAGS@ -I../../libs/glpng $(PYTHON_CPPFLAGS)

_entity.so : entity_wrap.o
	ld -shared libs7.so entity_wrap.o -o _entity.so

libs7.so : area.o asteroid.o camera.o console.o entity.o entity_wrap.o entitymgr.o \
			netclient.o netpacket.o netserver.o netserverclient.o p_plasma.o \
			particles.o physics.o projectile.o radar.o renderer.o sector.o \
			texture.o timer.o udpsocket.o util.o vector.o video.o w_plasmacannon.o \
			weapon.o
	ld -shared -o libs7.so area.o asteroid.o camera.o console.o entity.o entity_wrap.o entitymgr.o \
			netclient.o netpacket.o netserver.o netserverclient.o p_plasma.o \
			particles.o physics.o projectile.o radar.o renderer.o sector.o \
			texture.o timer.o udpsocket.o util.o vector.o video.o w_plasmacannon.o \
			weapon.o

all-local: libs7.so _entity.so

clean-local:
	rm libs7.so
	rm _entity.so
