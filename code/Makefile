CC=g++
LIBS=/usr/lib/libproj.a /usr/lib/libgeos.a
OBJS=GCPoint.o GCEdge.o GCDataUtils.o GCRoadNetwork.o GCPointsTrack.o
HEADERS=GCDataUtils.h  GCEdge.h  GC.h  GCPoint.h  GCPointsTrack.h  GCRoadNetwork.h
FLAGS=-g

GCPointsTrack.o: GCPointsTrack.cpp GCPointsTrack.h
	$(CC) $(FLAGS)  -c GCPointsTrack.cpp -o GCPointsTrack.o

GCPoint.o: GCPoint.cpp GCPoint.h
	$(CC) $(FLAGS)  -c GCPoint.cpp -o GCPoint.o

GCEdge.o: GCEdge.cpp GCEdge.h
	$(CC) $(FLAGS) -c GCEdge.cpp -o GCEdge.o

GCDataUtils.o: GCDataUtils.cpp GCDataUtils.h
	$(CC) $(FLAGS) -c GCDataUtils.cpp -o GCDataUtils.o

GCRoadNetwork.o: GCRoadNetwork.cpp GCRoadNetwork.h 
	$(CC) $(FLAGS) -c GCRoadNetwork.cpp -o GCRoadNetwork.o

mapmatch.exe: $(OBJS) main.cpp
	$(CC) main.cpp  $(OBJS) $(LIBS) $(FLAGS) -o mapmatch.exe

all: mapmatch.exe

clean:
	rm *.o *.exe

