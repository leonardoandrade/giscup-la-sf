import pg, sys

if __name__=='__main__':
    
    
    if(len(sys.argv)!=2):
        print "USAGE:\n\t"+sys.argv[0]+" <file-edge-geometry>"  
        sys.exit()
    conn=pg.connect("giscup")
    conn.query("delete from t_giscup_edge")
    f3=open(sys.argv[1])
    conn.query("begin work")
    count=0
    for line in f3:
        line=line[:-2]
        tok=line.split("^")
        tmp=[]
        c=0
        for i in tok[4:]:
            tmp.append(i)
        tmp_inv=[]
            
        for i in [ i for i in range(len(tmp)) if i%2==0]:
            tmp_inv.append(str(tmp[i+1])+" "+str(tmp[i]))
            
        wkt="LINESTRING("+",".join(tmp_inv)+")"
       # print "wkt=",wkt

        
        #print wkt
        #conn.query("update t_giscup_edge set name='"+tok[2]+"', type='"+tok[3]+"', length="+tok[4]+", the_geom=setsrid(geometryfromtext('"+wkt+"'),4326) where  gid="+tok[0]+"")
        conn.query("insert into t_giscup_edge(id, name, type, length, the_geom) values('"+tok[0]+"','"+tok[1].replace("'"," ")+"','"+tok[2]+"','"+tok[3]+"',st_transform(st_setsrid('"+wkt+"',4326),900913))")
        if count%10000==0:
            print ".",
            sys.stdout.flush()
            conn.query("end work")
            conn.query("begin work")
        count=count+1           
    conn.query("end work")
    f3.close()
