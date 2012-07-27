import random

if __name__=='__main__':
    b_distance_100=float(random.randint(0,100))
    b_direction_100=float(random.randint(0,100))
    b_adjacency_100=float(random.randint(0,100))
    
    b_distance=round(b_distance_100/(b_distance_100+b_direction_100+b_adjacency_100),2)
    b_direction=round(b_direction_100/(b_distance_100+b_direction_100+b_adjacency_100),2)
    b_adjacency=round(b_adjacency_100/(b_distance_100+b_direction_100+b_adjacency_100),2)
    
    
    topology_adjacent_same_edge=float(random.randint(80,200))/100
    topology_adjacent_accessible=float(random.randint(80,200))/100
    topology_adjacent_same_streetname=float(random.randint(80,200))/100
    print str(b_distance)+";"+str(b_direction)+";"+str(b_adjacency)+";"\
    +str(topology_adjacent_same_edge)+";"+str(topology_adjacent_accessible)+";"+str(topology_adjacent_same_streetname)
