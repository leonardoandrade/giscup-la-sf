import pg, sys

if __name__=='__main__':
    
    
    if(len(sys.argv)!=4):
        print "USAGE:\n\t"+sys.argv[0]+" <edge-input-file> <edge-output-file> <table>"  
        sys.exit()
    
    
    node_input_file=open(sys.argv[1])
    node_output_file=open(sys.argv[2])
    table=sys.argv[3]
    
    conn=pg.connect("giscup")
    
    
    
    conn.query("delete from "+table)
    
    
    for line in node_input_file:
        tok=line.split(",")
        conn.query("insert into "+table+"(id, the_geom) values("+tok[0]+",st_transform(st_setsrid('POINT("+tok[2]+" "+tok[1]+")',4326),900913))")
        
    for line in node_output_file:
        tok=line.split(",")    
        conn.query("update "+table+" set edge='"+tok[1]+"', confidence='"+tok[2]+"' where id = "+tok[0]+"")
