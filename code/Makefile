CC=g++
LIBS=/usr/lib/libgeos.a -lpqxx
OBJS=GCPoint.o GCEdge.o GCDataUtils.o GCRoadNetwork.o

GCPoint.o: GCPoint.cpp GCPoint.h
	$(CC) -c GCPoint.cpp -o GCPoint.o

GCEdge.o: GCEdge.cpp GCEdge.h
	$(CC) -c GCEdge.cpp -o GCEdge.o

GCDataUtils.o: GCDataUtils.cpp GCDataUtils.h
	$(CC) -c GCDataUtils.cpp -o GCDataUtils.o

GCRoadNetwork.o: GCRoadNetwork.cpp GCRoadNetwork.h 
	$(CC) -c GCRoadNetwork.cpp -o GCRoadNetwork.o

boda: $(OBJS) boda.cpp
	$(CC) boda.cpp  $(OBJS) $(LIBS)  -o boda 

clean:
	rm *.o boda
