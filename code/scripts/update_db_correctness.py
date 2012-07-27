import pg, sys

if __name__=='__main__':


    if(len(sys.argv)!=3):
        print "USAGE:\n\t"+sys.argv[0]+" <points-ground-truth-file> <table>"
        sys.exit()


    node_input_file=open(sys.argv[1])
    table=sys.argv[2]


    conn=pg.connect("giscup")

    count=0
    conn.query("BEGIN WORK")
    for line in node_input_file:
        tok=line.split(",")
        conn.query("update "+table+" set correct = (edge='"+tok[1]+"'), right_edge='"+tok[1]+"' where id="+tok[0])
        if count%100==0:
        
            conn.query("END WORK")
            conn.query("BEGIN WORK")
    conn.query("END WORK")            
            
    
