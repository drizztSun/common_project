import time
from dateutil import parser
from OpenSSL import crypto


class CertUtil(object):
    
    root_certs = None
    store = None
    cert_type = {"ASN1": crypto.FILETYPE_ASN1, "PEM": crypto.FILETYPE_PEM}

    def __init__(self):
        pass

    @staticmethod
    def verify_certificate_sign_by_root(data, type = "ASN1"):
        """
            data : certificate binary stream
            type : certificate encoding type
        """
        if type not in CertUtil.cert_type or not CertUtil.root_certs or not data:
            return False
        try:
            store_ctx = crypto.X509StoreContext(CertUtil.store, crypto.load_certificate(CertUtil.cert_type[type], data))
            return True if store_ctx.verify_certificate() is None else False
        except:
            return False

    @staticmethod
    def extract_public_key_from_certificate(data, type="ASN1"):
        """
            extract public key from certificate, pem and der fromat
        """
        if type not in CertUtil.cert_type or not data:
            return None
        try:
            cert = crypto.load_certificate(CertUtil.cert_type[type], data)
            return cert.get_pubkey().to_cryptography_key()
        except:
            return None

    @staticmethod
    def import_eaa_device_ca(data, type):
        """
            data : certificate stream
            type : certifcate encoding type
        """
        if type not in CertUtil.cert_type or not data:
            return False
        try:
            CertUtil.root_certs = crypto.load_certificate(CertUtil.cert_type[type], data)
            CertUtil.store = crypto.X509Store()
            CertUtil.store.add_cert(CertUtil.root_certs)
            return True
        except:
            CertUtil.root_certs, CertUtil.store = None, None
            return False