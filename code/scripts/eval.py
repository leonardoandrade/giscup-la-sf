import sys

if __name__=='__main__':
    if len(sys.argv)!=3:
        print "USAGE:\n\t ",sys.argv[0],"<truth-file> <test-file>"
        sys.exit(0)
        
    truth_file=open(sys.argv[1])
    truth={}
    ev=0.0
    
    
    for line in truth_file:
        tok=line.replace("\n","").split(",")
        #print "truth",tok   
        truth[tok[0]]=tok[1]
    
    
    points_evaluated=0
    test_file=open(sys.argv[2])
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
    print "official evaluation for files '",sys.argv[1],"' and '",sys.argv[2],"' is ",ev," (",points_evaluated,") points evaluated"
    print "internal evaluatios '",sys.argv[1],"' and '",sys.argv[2],"' is ",round(internal_evaluation,2),"%"
