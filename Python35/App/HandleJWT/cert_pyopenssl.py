
import time
from dateutil import parser
from OpenSSL import crypto

def verify_chain_of_trust(trusted_cert, root_certs):

    # Create and fill a X509Store wiuth trust certs
    store = crypto.X509Store()

    #for cert in root_certs:
    cert_obj = crypto.load_certificate(crypto.FILETYPE_PEM, root_certs)
    store.add_cert(cert_obj)

    # Create a X509StoreContext with the cart and trusted certs
    # and verify the chain of trust
    store_ctx = crypto.X509StoreContext(store, crypto.load_certificate(crypto.FILETYPE_PEM ,trusted_cert))

    result = store_ctx.verify_certificate()

    if result is None:
        return True
    
    return False

def get_certificate_info(cert_file):

    cert = crypto.load_certificate(crypto.FILETYPE_PEM, cert_file)
    cert_issue = cert.get_issuer()

    print ("Certifcate version:  ", cert.get_version() + 1)
    
    print ("Certificate serial number: ", hex(cert.get_serial_number()))
    
    print ("Certificate algorithm: ", cert.get_signature_algorithm().decode("UTF-8"))
    
    print ("issuer:  ", cert_issue.commonName)
    
    datetime_struct = parser.parse(cert.get_notBefore().decode("UTF-8"))
    
    print ("issue time:  ",datetime_struct.strftime('%Y-%m-%d %H:%M:%S'))
    
    datetime_struct = parser.parse(cert.get_notAfter().decode("UTF-8"))
    
    print ("exp time: ", datetime_struct.strftime('%Y-%m-%d %H:%M:%S'))
    
    print ("expired: ", cert.has_expired())
    
    print("public key length:  ", cert.get_pubkey().bits())
    
    print("public key: \n" , crypto.dump_publickey(crypto.FILETYPE_PEM, cert.get_pubkey()).decode("utf-8"))
    
    print("Message main:")
    
    print("CN : Common Name  OU : organization unit")
    print("O  : organization    L  : geolocation")
    print("S  : state   C  : country")
    
    for item in cert_issue.get_components():
        print(item[0].decode("utf-8"), "  ——  ",item[1].decode("utf-8"))
    
    print(cert.get_extension_count())

def load_cert_file_stream(cert_file):

    with open(cert_file) as cert_file_hanlder:
        return cert_file_hanlder.read()

def get_public_key_from_certificate(cert_file):

    stream = load_cert_file_stream(cert_file)
    
    cert = crypto.load_certificate(crypto.FILETYPE_PEM, stream)
    
    return cert.get_pubkey().decode("utf-8")

def test_verify():

    try: 
        cert_path = '../cert/rootcert_nopassword/'
        yuxin_cert_file = 'yuxin.com.crt'
        root_cert_file = 'rootCA.crt'

        with open(cert_path + yuxin_cert_file, 'r') as cert_file:
            cert = cert_file.read()
            get_certificate_info(cert)

        with open(cert_path + root_cert_file, 'r') as rootcert_file:
            root_cert = rootcert_file.read()
            get_certificate_info(root_cert)

        if verify_chain_of_trust(cert, root_cert):
            print("Verified the root certificate ")

        
    except:
        print("Except happened")


if __name__ == "__main__":

    test_verify()