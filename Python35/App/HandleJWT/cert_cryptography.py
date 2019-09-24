from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa

import time
from dateutil import parser
from OpenSSL import crypto


def output_cert_Info(cert):
    
    if not isinstance(cert, x509.Certificate):
        return 

    print("Cert info: ")
    print("Version: " + cert.version.name + " val: " + str(cert.version.value))
    print("Serial number: ", cert.serial_number)
    print("fingerprint: ", cert.fingerprint(hashes.SHA256()))
    print("pubkey is RAS key: ", isinstance(cert.public_key(), rsa.RSAPublicKey))
    print("not valid before: ", cert.not_valid_before)
    print("not_valid_after: ", cert.not_valid_after)
    print("issuer: ", cert.issuer)
    print("subject: ", cert.subject)

    print("signature: ", cert.signature)


def get_der_certificate_public_key(data):
    
    pubCert = x509.load_der_x509_certificate(data, default_backend())

    print("Is certificate : ", isinstance(pubCert, x509.Certificate))

    output_cert_Info(pubCert)
    
    return pubCert.public_key()


def verify_cert_root_ca(cert, root_cert):

    print("verify the two cert root ca")

    try:
        # create a certificate store and add trusted certificates
        None
    except Exception as e:
        print("Err " + e)


def verify_chain_of_trust_chain(cert, root_cert):
    pass


def test_root_verify():
    
    try: 
        cert_path = '../cert/rootcert_nopassword/'
        yuxin_cert_file = 'yuxin.com.crt'
        root_cert_file = 'rootCA.crt'

        with open(cert_path + yuxin_cert_file, 'r') as cert_file:
            cert = x509.load_pem_x509_certificate(cert_file.read())
            output_cert_Info(cert)

        with open(cert_path + root_cert_file, 'r') as rootcert_file:
            root_cert = x509.load_pem_x509_certificate(rootcert_file.read())
            output_cert_Info(root_cert)

        if verify_chain_of_trust_chain(cert, root_cert):
            print("Verified the root certificate ")

        
    except:
        print("Except happened")


class cert_util(object):

    root_certificate = None
    cert_callback = {"ASN1": x509.load_der_x509_certificate, "PEM": x509.load_pem_x509_certificate}

    @staticmethod
    def load_certifcate_from_stream(data, type):
        if type not in cert_callback:
            return None

        return  cert_util.cert_callback[type](data)

    @staticmethod
    def verify_certificate_sign_by_root(data, type = "ASN1"):
        cert = cert_util.load_certifcate_from_stream(data, type)
        if not cert:
            return False

        return True

    @staticmethod
    def extract_public_key_from_certificate(data, type="ASN1"):
        cert = cert_util.load_certifcate_from_stream(data, type)
        if not cert:
            return False

        return cert.public_key()

    @staticmethod
    def import_eaadevice_rootcert(data, type):
        
        cert = cert_util.load_certifcate_from_stream(data, type)
        if not cert:
            return False

        cert_util.root_certificate = cert
        return True


def main():
    pass


if __name__ == "__main__":

    main()