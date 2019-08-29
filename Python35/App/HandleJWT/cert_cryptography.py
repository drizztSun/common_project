from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa

def output_cert_Info(cert):
    
    if not isinstance(cert, x509.Certificate):
        return 

    print("Cert info: ")
    print("Version: " + cert.version)
    print("Serial number: " + cert.serial_number)
    print("fingerprint: " + cert.fingerprint(hashes.SHA256()))
    print("pubkey is RAS key: " + isinstance(cert.public_key(), rsa.RSAPublicKey))
    print("not valid before: " + cert.not_valid_before)
    print("not_valid_after: ", cert.not_valid_after)
    print("issuer: ", cert.issuer)
    print("subject: ", cert.subject)

    print("signature: ", cert.signature)

def get_der_certificate_public_key(data):
    
    pubCert = x509.load_der_x509_certificate(data, default_backend())

    print("Is certificate : ", isinstance(pubCert, x509.Certificate))

    pubCert = x509.load_der_x509_certificate(data, default_backend())

    # output_cert_Info(pubCert)
    return pubCert.public_key()

def verify_cert_root_ca(cert, root_cert):

    print("verify the two cert root ca")

    try:
        # create a certificate store and add trusted certificates
        None
    except Exception as e:
        print("Err " + e)

def main():
    None

if __name__ == "__main__":

    main()