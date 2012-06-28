import pg, sys

conn=None
    
def import_nodes(file_nodes):
    conn.query("delete from t_giscup_node")    
    f1=open(file_nodes)
    conn.query("begin work")
    count=0
    for line in f1:
        tok=line.split(" ")
        conn.query("insert into t_giscup_node(gid, lat, lon, the_geom) values("+tok[0]+","+tok[1]+","+tok[2]+",setsrid(geometryfromtext('POINT("+tok[2]+" "+tok[1]+")'),4326))")
        #conn.query("insert into t_giscup_node(gid, lat, lon, the_geom) values("+tok[0]+","+tok[1]+","+tok[2]+",'POINT("+tok[2]+" "+tok[1]+")')")
        
        if count%10000==0:
            print ".",
            sys.stdout.flush()
            conn.query("end work")
            conn.query("begin work")
        count=count+1           
    conn.query("end work")
    f1.close()
    
def import_edges(file_edges):
    conn.query("delete from t_giscup_edge")
    f2=open(file_edges)
    conn.query("begin work")
    count=0
    for line in f2:
        tok=line.split(" ")
        conn.query("insert into t_giscup_edge(gid, start_node, end_node, cost) values("+tok[0]+","+tok[1]+","+tok[2]+","+tok[3]+")")
        
        if count%10000==0:
            print ".",
            sys.stdout.flush()
            conn.query("end work")
            conn.query("begin work")
        count=count+1           
    conn.query("end work")
    f2.close()
        
    
def import_edge_geometries(file_edge_geometries):
        
    f3=open(file_edge_geometries)
    conn.query("begin work")
    count=0
    for line in f3:
        line=line[:-2]
        tok=line.split("^")
        tmp=[]
        c=0
        for i in tok[4:]:
            if c%2==0 or c==(len(tok[4:])-1):
                tmp.append(str(i))
            else:
                tmp.append(str(i)+',')
            c=c+1
        wkt="LINESTRING("+" ".join(tmp)+")"
        

        
        #print wkt
        #conn.query("update t_giscup_edge set name='"+tok[2]+"', type='"+tok[3]+"', length="+tok[4]+", the_geom=setsrid(geometryfromtext('"+wkt+"'),4326) where  gid="+tok[0]+"")
        conn.query("update t_giscup_edge set name='"+tok[2]+"', type='"+tok[3]+"', length="+tok[4]+", the_geom='"+wkt+"' where  gid="+tok[0]+"")
                
        if count%1000==0:
            print ".",
            sys.stdout.flush()
            conn.query("end work")
            conn.query("begin work")
        count=count+1           
    conn.query("end work")
    f3.close()

        
        
def build_connections():
    pass
def draw_arows():
    pass


if __name__=='__main__':
    if len(sys.argv)!=4:
        print "usage:\n"+sys.argv[0]+" <node-file> <edge-file> <edge-geometry-file>"
        sys.exit()
        
    conn=pg.connect("giscup")

    import_nodes(sys.argv[1])
    #import_edges(sys.argv[2])
    #import_edge_geometries(sys.argv[3])
