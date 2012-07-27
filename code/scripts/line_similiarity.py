import pg

conn=None

def compute_similarity2(line_gid):
    tmp=conn.query("select astext(st_pointn(the_geom,1)), astext(st_pointn(the_geom,2)), astext(st_pointn(the_geom,3)) from t_giscup_subline where gid='"+str(line_gid)+"' ").getresult()
    start_point=tmp[0][0]
    middle_point=tmp[0][1]
    end_point=tmp[0][2]
    n_points_mainline=conn.query("select st_numpoints(the_geom) from t_giscup_mainline limit 1").getresult()[0][0]
    end_point_mindist=9999999999
    start_point_mindist=999999999
    end_point_closest_id=-1
    start_point_closest_id=-1

    
    
    
    for i in range(n_points_mainline):
        d=conn.query("select st_distance(st_pointn(the_geom,"+str(i+1)+"),setsrid(geometryfromtext('"+start_point+"'),900913)), st_distance(st_pointn(the_geom,"+str(i+1)+"), setsrid(geometryfromtext('"+end_point+"'),900913))  from t_giscup_mainline limit 1").getresult()[0]
        if d[0]<start_point_mindist:
            start_point_closest_id=i+1
            start_point_mindist=d[0]
        if d[1]<end_point_mindist:
            end_point_closest_id=i+1
            end_point_mindist=d[1]
            
    if start_point_closest_id < end_point_closest_id:
        sim=1.0
    elif start_point_closest_id == end_point_closest_id:
        sim=0.5
    else:
        sim=0.0
        
    tmp=conn.query("select st_distance((the_geom),setsrid(geometryfromtext('"+start_point+"'),900913)), st_distance((the_geom),setsrid(geometryfromtext('"+start_point+"'),900913)), st_distance((the_geom),setsrid(geometryfromtext('"+middle_point+"'),900913))  from t_giscup_mainline limit 1").getresult()[0]
    d1=tmp[0]
    d2=tmp[1]
    d3=tmp[2]
    
    sim=sim*(min(d1,d2,d3)/((d1+d2+d3)/3))
    print "start_point_mindist=",start_point_mindist,"end_point_mindist=",end_point_mindist, "start_point_closest_id=",start_point_closest_id,"end_point_closest_id=",end_point_closest_id
    conn.query("update t_giscup_subline  set similarity='"+str(sim)+"' where gid='"+str(line_gid)+"'")  
            
def compute_similarity(line_gid):

    length_mainline=conn.query("select st_length2d(the_geom) from t_giscup_mainline limit 1").getresult()[0][0]
    length_subline=conn.query("select st_length2d(the_geom) from t_giscup_subline where gid='"+str(line_gid)+"'").getresult()[0][0]
    n_points_mainline=conn.query("select st_numpoints(the_geom) from t_giscup_mainline limit 1").getresult()[0][0]
    n_points_subline=conn.query("select st_numpoints(the_geom) from t_giscup_subline where gid='"+str(line_gid)+"' limit 1").getresult()[0][0]
    start_point=conn.query("select astext(st_pointn(the_geom,1)) from t_giscup_subline where gid='"+str(line_gid)+"' ").getresult()[0][0]
    end_point=conn.query("select astext(st_pointn(the_geom,3)) from t_giscup_subline where gid='"+str(line_gid)+"' ").getresult()[0][0]
    sum_dist=0.0
    for i in range(n_points_mainline):
        d=conn.query("select st_distance(st_pointn(the_geom,"+str(i+1)+"),setsrid(geometryfromtext('"+start_point+"'),900913)), st_distance(st_pointn(the_geom,"+str(i+1)+"),setsrid(geometryfromtext('"+end_point+"'),900913))  from t_giscup_mainline limit 1").getresult()[0]
        print "gid=",line_gid,"i=",i+1,"d1=",d[0],"d2=",d[1]," delta=",((d[1]-d[0])/length_subline)*(length_subline/((d[0]+d[1])/2))
        partial=((d[1]-d[0])/length_subline)*(length_subline/((d[0]+d[1])/0.2))
        #partial=((d[1]-d[0]))*(1.0/max(d[0],d[1])**(length_subline/100))
        print partial
        sum_dist=sum_dist+partial
    
    print "subline (gid=",line_gid,") has ",n_points_subline," points and main line has ",n_points_mainline," points, sum_dis=",sum_dist
    conn.query("update t_giscup_subline  set similarity='"+str(round(sum_dist,4))+"' where gid='"+str(line_gid)+"'")
    
    
    
    
if __name__=='__main__':
    conn=pg.connect("giscup")
    gids=[]
    rs=conn.query("select gid from t_giscup_subline").getresult()
    for r in rs:
        gid=r[0]
        compute_similarity2(gid)
