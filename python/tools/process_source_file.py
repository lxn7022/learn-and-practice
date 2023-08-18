



def extract_method_of_struct(filename):
    with open(filename) as f:
        for line in f :
            if line.startswith("//") : 
                print(line[:-1])
            if line.startswith("func"):
                fields = line.split()
                print(" ".join(fields[3:-1])) 
            

def process_oauth():
    basepath = "./oauth/"
    filenames = ['oauth.go', 'db.go', 'token.go', 'merchant.go']
    for filename in filenames :
        fname = basepath+filename
        print(">>>>>>>>>>>>>>>>>>>>>>>:", fname)
        extract_method_of_struct(fname)
        
def process_rbac():
    basepath = "./rbac/"
    filenames = ['user.go', 'role.go', 'rbac.go', 'permission.go']
    for filename in filenames :
        fname = basepath+filename
        print(">>>>>>>>>>>>>>>>>>>>>>>:", fname)
        extract_method_of_struct(fname)
        
def process_crypt():
    basepath = "./crypt/"
    filenames = ['aes.go', 'hash.go', 'rsa.go', 'sign.go']
    for filename in filenames :
        fname = basepath+filename
        print(">>>>>>>>>>>>>>>>>>>>>>>:", fname)
        with open(fname) as f:
            for line in f :
                if line.startswith("//") : 
                    print(line[:-1])
                if line.startswith("func"):
                    print(line[:-2])
        
def process_mtenant():
    basepath = "./mtenant/"
    filenames = ['db.go', 'mtenant.go', 'tenant.go']
    for filename in filenames :
        fname = basepath+filename
        print(">>>>>>>>>>>>>>>>>>>>>>>:", fname)
        extract_method_of_struct(fname)    
                        
if __name__ == "__main__":
    #process_oauth()
    #process_rbac()
    #process_crypt()
    process_mtenant()