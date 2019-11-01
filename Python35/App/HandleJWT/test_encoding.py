import json
import jwt
import base64
import time

from dateutil import parser
from OpenSSL import crypto

# DeviceFactory.cert
device_factory_cert = b"""-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUDgvGbBTAYI68i0R4Hg3tqjkSNgEwDQYJKoZIhvcNAQEL
BQAwPTEhMB8GA1UEChMYQWthbWFpIFRlY2hub2xvZ2llcyBJbmMuMRgwFgYDVQQD
Ew9EZXZpY2VQb3N0dXJlQ0EwHhcNMTgxMDAxMTg1MDAyWhcNMjAxMDAxMTg0MTMz
WjA7MSEwHwYDVQQKDBhBa2FtYWkgVGVjaG5vbG9naWVzIEluYy4xFjAUBgNVBAMM
DURldmljZUZhY3RvcnkwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDB
FswzjaKpmy0jtoYLmeCOCMmka5nEExgrIJrfqL4DqfGdedcOWTvgAswkAm0uIdzl
IicKmfff2sW3m85EnqAgl2Fvzd3fN68vF7gMI0uaokcAWLuEzmvNX3xM70/LUzFY
bZnRIV0rcW4bRTG0XmC1Sm4PMswBGtI8oUQwV4AhK7RC9bKmzu60EJXNQpidPB81
W2sh4jlCg7NGYtb1dmQbM3U9ZHW+cQggBl+T+X3qsDL3gcGz1cbpJyhzCuPsN4au
2jjdEHVtpeBFg0sYQdQC7AdXi12/9WR/f6I2uMlMwIdN9U4+xSmz2LcZ5LaIbZc0
zoHJ6RZfHtm9hclZFQ3HAgMBAAGjUzBRMAwGA1UdEwEB/wQCMAAwHwYDVR0jBBgw
FoAUMyFh52X89c5pH570arS3hulJevAwEwYDVR0lBAwwCgYIKwYBBQUHAwIwCwYD
VR0PBAQDAgWgMA0GCSqGSIb3DQEBCwUAA4IBAQA/2QTpKdI7ciHRNZve8qu7IzA8
Ocq+HmVOLKO6wzRmlIy5t0Aey3mceKgCap0scTIXY9qEnXYTIxGs5aGjSpclFelg
+pv2ZWRu3gJu6q5fLdm2fF/2cdRbyHmStMwZa6ooqemvi70J+TmUUPdaruVy8VYJ
g95/f9V2R6xo7rRjVv6jWcLfE+xPO9Z2kWw8PFIvwds8CQrwP2TGOzp1fP2ycujD
zfeQA83gXYFdFUcA0jDDJtSwX9yBGgqFnDntQTH6X58T5njdOCM90YYlPVZX1K7w
VWCMmePoUymFPBUUbctfYnsyOg74EATRURsDhhVQXBoltZK7Z6Mw3l76HQip
-----END CERTIFICATE-----"""


# DeviceFactory.key
device_factory_private_key = b"""-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAwRbMM42iqZstI7aGC5ngjgjJpGuZxBMYKyCa36i+A6nxnXnX
Dlk74ALMJAJtLiHc5SInCpn339rFt5vORJ6gIJdhb83d3zevLxe4DCNLmqJHAFi7
hM5rzV98TO9Py1MxWG2Z0SFdK3FuG0UxtF5gtUpuDzLMARrSPKFEMFeAISu0QvWy
ps7utBCVzUKYnTwfNVtrIeI5QoOzRmLW9XZkGzN1PWR1vnEIIAZfk/l96rAy94HB
s9XG6Scocwrj7DeGrto43RB1baXgRYNLGEHUAuwHV4tdv/Vkf3+iNrjJTMCHTfVO
PsUps9i3GeS2iG2XNM6ByekWXx7ZvYXJWRUNxwIDAQABAoIBAGVN4LTrinwRvg0O
piVQBlB+q8xn57THj9aQtLDDh23Eq89DLWGJz7Anx5Lc8wtRGOPelz0oqrP3w+Qh
CodV8g0nXyeZit6iCHdcqmMz4Wav3TCBXWDALC8D+eMja2nxq+IJHrpqFsfEK1CD
bSCEo5h6BGRU8lNiDwtgULZMMh00NYk5AgLuPb3CrZv24AbOEWD8164Vqs61c2aj
HAh87+Wtd7iOT+eehAvv7JnznOoinmcv2/pj+HptL5XhjiWg4xB2ac3Ea1/10Z+M
VwBCd+4XAp+0boFo1W4BPlJVLx8w4Q4UEjVi5Gf3IdPT31D0Lb9o86R/oW8OCztf
F4qVoIECgYEA/TsrX+72W6C9s2sLa045tzQ7JWrHN0b7fgz2tXMqYp+J/G/78vu/
sKrVw9LZSlraoE0QXYJQGxDd1R0mKsFxR8eCyhI7jwMFXBE5s2WuZ401Jpl0KGHX
3mIk4cXUcRUcriQqDhfPYCWmG0RVLJZJRrGMRSkgYd+NB/rBKeKjPlsCgYEAwzNI
J6AE4lLQegpEjIHFWm5giQ8KJReGSUQ23K/5Y73qS5vtJzps4H42vUYv3/PnI85u
gkF8PTCEGUx5XI2nzdgF3+4bHahxsD2YKpquKnXXZM1nwBrfxCDCawBpZYbbt1bn
eyr47kjH6zWIfK/h2jHYq1B4Id1xsrfZzjTyYgUCgYEA1daXZCV4qBtu1gm41N5z
4n8ayxgGLmmkiecMlmEwE6RBc4hlK+TnFJrOdNSiZSWfpOouvagDWTe+++3ngwdj
T4fsrBMFdFjKt9pb7WAaDJuznGrNKiSlk8cw+e6C3RNE6tDjKo90sO5Z/ICRpFss
eaQInYaDL+MFRw26/FHEJC0CgYBc1Ua7kZ7BBCGh6MAxEoaJO3UtublZapaywX5V
9lrk1K1YyA9BWMfu/BeMbJTYLWb/4G0uBXbQowIwBe6x1ay4eMRSeyrqL/Hhn2l+
2ZF7IBAQIJ/2/NDutaXAvbFiV4Cm8O2l5gn9SR/K/OqsYflHi+0/jEWV1Xr9Q/KR
3xxnAQKBgQCIy0yZextMpdaS22mttXol5zcsJuVFeabLO7Jj3eJAedAlgR4hUUkj
cWs4qRvJRoQQ4S7FmO4l2p0brnnhFclJzt7xDI2QTWU+EE7OrdFnKYSV4n7LE1/s
7/npW5wRUI5ZKeQTw4zLq4fauNksCcUUANqG0uv1TPP6BIZJCivW6w==
-----END RSA PRIVATE KEY-----"""


def genetate_jwt_token():

    payload = {
        'sub': '3a2bd56f-ac78-4fda-afe2-be9b6188fb2f',
        'exp': int(time.time()) + 1800,
        'iat': int(time.time()),
        "iss": "https://signal-t.dps.stage.akamai-access.com"
    }

    headers = {
        'x5c': [
            base64.b64encode(device_factory_cert).decode('utf-8')
        ]
    }

    res = jwt.encode(payload, device_factory_private_key, algorithm='RS256', headers = headers)

    print(res)
    h, p, s = res.decode('utf-8').split('.')

    print(jwt.get_unverified_header(res))
    header = jwt.get_unverified_header(res)
    print(type(header))

    h += "=" * ((4 - len(h) % 4) % 4)
    p += "=" * ((4 - len(p) % 4) % 4)
    print(h)
    print( json.loads(base64.urlsafe_b64decode(h)) )
    print(p)
    print( json.loads(base64.urlsafe_b64decode(p)) )
    print(s)

    verify_jws_token(res, lambda x: x['sub'] == payload['sub'])


def verify_jws_token(token, callback):

    try:
        header = jwt.get_unverified_header(token)
        public_cert = base64.b64decode(header['x5c'][0].encode('utf-8'))
        cert = crypto.load_certificate(crypto.FILETYPE_PEM, public_cert)
        key = cert.get_pubkey().to_cryptography_key()

        payload = jwt.decode(token, key, algorithms=header['alg'])

        print("payload: ", payload)

        if callback:
            return callback(payload)

        return True

    except jwt.InvalidIssuerError:
        print("invalude issuer")
    except jwt.DecodeError:
        print("Decoding err")
    except jwt.InvalidAlgorithmError:
        print("Expired Signatured Error")
    except jwt.ExpiredSignatureError:
        print("Signature has been expired")
    except:
        print("unknown error")

    return False

def verify_ca(public_cert_data, ca_cert_data):

    ca_cert = crypto.load_certificate(crypto.FILETYPE_PEM, ca_cert_data)
    store = crypto.X509Store()
    store.add_cert(ca_cert)
    store_ctx = crypto.X509StoreContext(store, crypto.load_certificate(crypto.FILETYPE_ASN1, public_cert_data))

    return True if store_ctx.verify_certificate() is None else False


if __name__ == '__main__':

    jwt = genetate_jwt_token()