import json
import jwt


def test_hs_encoding(): 

    print("--- start encoding ---")

    encoded = jwt.encode({'some': 'payload'}, 'secret', algorithm='HS256') 

    print("encoded content : \n", encoded)

    fields = encoded.split('.')

    print("JWT header : \n", jwt.get_unverified_header(encoded))

    return encoded

def test_hs_decoding(input):

    print("--- start decoding ---")

    result = jwt.decode(input, 'secret', alg='HS256')

    print("result : ", result)

    print("unverified claims: \n", jwt.decode(input, verify=False))

    print("unverified claums: \n", jwt.get_unverified_header(input))

    

if __name__ == "__main__": 

    output = test_hs_encoding()

    test_hs_decoding(output)