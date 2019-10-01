from os import listdir, system, path
from os.path import isfile, join, isdir, exists
import os

targetRootFolder = ['inventory_app', 'version_app', 'zero_trust_inventory']

skipfiles = set(
['./inventory_app/test/test_portal_service.py',
'./inventory_app/test/test_jwtutil.py',
'./inventory_app/test/test_rule_engine.py',
'./inventory_app/test/test_risk_assesment_api.py',
'./inventory_app/test/test_cert_util.py',
'./inventory_app/test/test_customer_rule_service.py',
'__init__.py']
)

skipfolders = set(
    ['test']
)

def generate_doc(target, dest):
    param = ['pycco', target, '-d', dest]
    print(system(' '.join(param)))


def generate_doc_from_rootdir(rootdir, docdir):
    for f in listdir(rootdir):
        obj = join(rootdir, f)
        if isfile(obj) and obj.endswith('.py') and obj not in skipfolders:
            print(obj + ' : ' + docdir)
            generate_doc(obj, docdir)
        elif isdir(obj) and not f.startswith('.') and f not in skipfiles:
            generate_doc_from_rootdir(obj, join(docdir, f))


def scan_generate_doc():
    for rootdir in targetRootFolder:
        rootdir, docdir = join('./' + rootdir), join('./doc/' + rootdir)
        if exists(rootdir):
            generate_doc_from_rootdir(rootdir, docdir)


if __name__ == '__main__':

    scan_generate_doc()



def ensure_dir(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)

def main():
    # 
    filename = '/my/directory/filename.txt'
    dir = os.path.dirname(filename)

    try:
        os.stat(dir)
    except:
        os.mkdir(dir) 
    
        

if __name__ == "__main__":

    main()
