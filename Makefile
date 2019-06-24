CXX = g++

SDL_LIB = -lmingw32 -lSDL2main -lSDL2 -L/usr/local/lib # -lSDL2 -Wl,-rpath=/usr/local/lib,.
SDL_INCLUDE = -I/usr/local/include

CXXFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = SimpleVis

all: $(EXE)

$(EXE): .bld/main.o .bld/AttrWindow.o .bld/Fps.o .bld/Universe.o .bld/View.o .bld/LinAlg.o .bld/Base.o\
        .bld/alglib/ap.o .bld/alglib/linalg.o .bld/alglib/alglibinternal.o .bld/alglib/alglibmisc.o \
		.bld/DemoObj.o .bld/DemoLight.o .bld/Motive.o .bld/Multithread.o
	$(CXX) $^ $(LDFLAGS) -o $@ 

.bld/main.o: main.cpp AttrWindow.h LinAlg.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

.bld/AttrWindow.o: AttrWindow.cpp AttrWindow.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

.bld/StringManip.o: StringManip.cpp StringManip.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

.bld/Fps.o: Fps.cpp Fps.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/Universe.o: Universe.cpp Universe.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/Motive.o: Motive.cpp Motive.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/View.o: View.cpp View.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/LinAlg.o: LinAlg.cpp LinAlg.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/Multithread.o: Multithread.cpp Multithread.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/Base.o: Base.cpp Base.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/DemoObj.o: objects/DemoObj.cpp objects/DemoObj.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/DemoLight.o: objects/DemoLight.cpp objects/DemoLight.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/alglib/ap.o: alglib/src/ap.cpp alglib/src/ap.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/alglib/linalg.o: alglib/src/linalg.cpp alglib/src/linalg.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/alglib/alglibinternal.o: alglib/src/alglibinternal.cpp alglib/src/alglibinternal.h
	$(CXX) $(CXXFLAGS) $< -o $@

.bld/alglib/alglibmisc.o: alglib/src/alglibmisc.cpp alglib/src/alglibmisc.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)