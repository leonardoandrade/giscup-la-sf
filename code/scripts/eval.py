import sys,os 

def evaluate_file(truth_file_path, test_file_path):
    
    truth_file=open(truth_file_path)
    truth={}
    ev=0.0
    
    for line in truth_file:
        tok=line.replace("\n","").split(",")
        #print "truth",tok   
        truth[tok[0]]=tok[1]
    
    
    points_evaluated=0
    test_file=open(test_file_path)
    for line in test_file:
        tok=line.replace("\n","").replace("\r","").split(",")
        #print "test:",tok
        try:
            if(truth[tok[0]]==tok[1]):
                ev=ev+float(tok[2])
            else:
                ev=ev-float(tok[2])
            points_evaluated=points_evaluated+1
        except KeyError:
            pass
            
    internal_evaluation=((points_evaluated+ev)/(points_evaluated*2))*100
    #print "official evaluation for files '",sys.argv[1],"' and '",sys.argv[2],"' is ",ev," (",points_evaluated," points)"
    #print "internal evaluation for files '",sys.argv[1],"' and '",sys.argv[2],"' is ",round(internal_evaluation,2),"% (",points_evaluated," points)"
    return (internal_evaluation, ev, points_evaluated)

if __name__=='__main__':
    if len(sys.argv)!=4:
        print "USAGE:\n\t ",sys.argv[0],"<command> <truth-file/directory> <test-file/directory>\n command can be 'file' (single files) or 'directory' (all files in directories)"
        sys.exit(0)
        
        
    command=sys.argv[1]
    if command=='file':
        (percent, official, total_points) = evaluate_file(sys.argv[2],sys.argv[3])
        print "official evaluation for files '",sys.argv[2],"' and '",sys.argv[3],"' is ",official," (",total_points," points)"
        print "internal evaluation for files '",sys.argv[2],"' and '",sys.argv[3],"' is ",round(percent,2),"% (",total_points," points)"
    elif command=='directory':
        dir_ground_truth=sys.argv[2]
        dir_test=sys.argv[3]
        fs=sorted([f for f in os.listdir(dir_ground_truth) if f[-4:]=='.txt'])
        sum_percent=0.0
        count=0
        for f in fs:
            (percent, official, total_points) = evaluate_file(dir_ground_truth+"/"+f , dir_test+"/"+f)
            print "eval for file '"+f+"' is ",round(percent,2),"%"
            count=count+1
            sum_percent=sum_percent+percent
        print "average_percent=",round(sum_percent/float(count),2),"%"
    else:
        print "command '"+command+"' not recognized" 
        sys.exit(0)
    
