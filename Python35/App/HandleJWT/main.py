
import json

from jwt import (
    JWT,
    jwk_from_dict,
    jwk_from_pem,
)

JWTCase = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCIsIng1YyI6Inh4eHh4In0.eyJpc3MiOiJjYXMudGVzdC5jb20iLCJleHAiOjE1Njk4MDUyNjEsInN1YiI6Inl1c3VuX2xhcHRvcF9tYWNib29rIn0.UOh7zpCM_gYekciirq3xFzPqR7qAo6IpsF-jOl83_0VOub7b_wivS9m2M2cR2Hql9bHcxI30vUyykW69yth2Hz5GxUC7L0HQPPzzUloY7sOUv1DS4ixGQnW-iQO4tL6Lepb-LuGx9tqb2ZuTkiCDoN8LXh7D_1p47RgGdnbWWLtHSM7F1PyAXVZEAp1DH_2YxmZZC77zoJMEO6jVhtzVG9H4N38HHU_AkiXEIGZbOdU056pp1gdZLg6Kv9u2Z-Tc8FoCalQpAgCzjbND3ZmU8S-8AAAa-RfR471YwuA6Iy7Rb8ZRRpnu7Ke3uVVVcxItfyVleFWhIFtQEsC9pls7Yw"

publicKey = "-----BEGIN PUBLIC KEY-----\
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnzyis1ZjfNB0bBgKFMSv\
vkTtwlvBsaJq7S5wA+kzeVOVpVWwkWdVha4s38XM/pa/yr47av7+z3VTmvDRyAHc\
aT92whREFpLv9cj5lTeJSibyr/Mrm/YtjCZVWgaOYIhwrXwKLqPr/11inWsAkfIy\
tvHWTxZYEcXLgAXFuUuaS3uF9gEiNQwzGTU1v0FqkqTBr4B8nW3HCN47XUu0t8Y0\
e+lf4s4OxQawWD79J9/5d3Ry0vbV3Am1FtGJiJvOwRsIfVChDpYStTcHTCMqtvWb\
V6L11BWkpzGXSW4Hv43qa+GSYOD2QU68Mb59oSk2OB+BtOLpJofmbGEGgvmwyCI9\
MwIDAQAB\
-----END PUBLIC KEY-----"

privateKey = "-----BEGIN RSA PRIVATE KEY-----\
MIIEogIBAAKCAQEAnzyis1ZjfNB0bBgKFMSvvkTtwlvBsaJq7S5wA+kzeVOVpVWw\
kWdVha4s38XM/pa/yr47av7+z3VTmvDRyAHcaT92whREFpLv9cj5lTeJSibyr/Mr\
m/YtjCZVWgaOYIhwrXwKLqPr/11inWsAkfIytvHWTxZYEcXLgAXFuUuaS3uF9gEi\
NQwzGTU1v0FqkqTBr4B8nW3HCN47XUu0t8Y0e+lf4s4OxQawWD79J9/5d3Ry0vbV\
3Am1FtGJiJvOwRsIfVChDpYStTcHTCMqtvWbV6L11BWkpzGXSW4Hv43qa+GSYOD2\
QU68Mb59oSk2OB+BtOLpJofmbGEGgvmwyCI9MwIDAQABAoIBACiARq2wkltjtcjs\
kFvZ7w1JAORHbEufEO1Eu27zOIlqbgyAcAl7q+/1bip4Z/x1IVES84/yTaM8p0go\
amMhvgry/mS8vNi1BN2SAZEnb/7xSxbflb70bX9RHLJqKnp5GZe2jexw+wyXlwaM\
+bclUCrh9e1ltH7IvUrRrQnFJfh+is1fRon9Co9Li0GwoN0x0byrrngU8Ak3Y6D9\
D8GjQA4Elm94ST3izJv8iCOLSDBmzsPsXfcCUZfmTfZ5DbUDMbMxRnSo3nQeoKGC\
0Lj9FkWcfmLcpGlSXTO+Ww1L7EGq+PT3NtRae1FZPwjddQ1/4V905kyQFLamAA5Y\
lSpE2wkCgYEAy1OPLQcZt4NQnQzPz2SBJqQN2P5u3vXl+zNVKP8w4eBv0vWuJJF+\
hkGNnSxXQrTkvDOIUddSKOzHHgSg4nY6K02ecyT0PPm/UZvtRpWrnBjcEVtHEJNp\
bU9pLD5iZ0J9sbzPU/LxPmuAP2Bs8JmTn6aFRspFrP7W0s1Nmk2jsm0CgYEAyH0X\
+jpoqxj4efZfkUrg5GbSEhf+dZglf0tTOA5bVg8IYwtmNk/pniLG/zI7c+GlTc9B\
BwfMr59EzBq/eFMI7+LgXaVUsM/sS4Ry+yeK6SJx/otIMWtDfqxsLD8CPMCRvecC\
2Pip4uSgrl0MOebl9XKp57GoaUWRWRHqwV4Y6h8CgYAZhI4mh4qZtnhKjY4TKDjx\
QYufXSdLAi9v3FxmvchDwOgn4L+PRVdMwDNms2bsL0m5uPn104EzM6w1vzz1zwKz\
5pTpPI0OjgWN13Tq8+PKvm/4Ga2MjgOgPWQkslulO/oMcXbPwWC3hcRdr9tcQtn9\
Imf9n2spL/6EDFId+Hp/7QKBgAqlWdiXsWckdE1Fn91/NGHsc8syKvjjk1onDcw0\
NvVi5vcba9oGdElJX3e9mxqUKMrw7msJJv1MX8LWyMQC5L6YNYHDfbPF1q5L4i8j\
8mRex97UVokJQRRA452V2vCO6S5ETgpnad36de3MUxHgCOX3qL382Qx9/THVmbma\
3YfRAoGAUxL/Eu5yvMK8SAt/dJK6FedngcM3JEFNplmtLYVLWhkIlNRGDwkg3I5K\
y18Ae9n7dHVueyslrb6weq7dTkYDi3iOYRW8HRkIQh06wEdbxt0shTzAJvvCQfrB\
jg/3747WSsf/zBTcHihTRBdAv6OmdhV4/dD5YBfLAkLrd+mX7iE=\
-----END RSA PRIVATE KEY-----"

def encode() :
    message = {
        'iss': 'https://example.com/',
        'sub': 'yosida95',
        'iat': 1485969205,
        'exp': 1485972805,
    }

    with open('./App/HandleJWT/rsa_private_key.pem', 'rb') as fh:
        signing_key = jwk_from_pem(fh.read())

    try :

        jwt = JWT()
        compact_jws = jwt.encode(message, signing_key, 'RS256')

        with open('./App/HandleJWT/rsa_public_key.json', 'r') as fh:
            verifying_key = jwk_from_dict(json.load(fh))

        message_received = jwt.decode(compact_jws, verifying_key)

        assert message == message_received
    except :
        print("error")
    finally:
        print("succeed")

def test_decoding():

    print(" --- test decoding ---")

    

def Main():

    print("--starting handle jwt ---")

    # encode()

    test_decoding()


if __name__ == "__main__":

    Main()