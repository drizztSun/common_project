import jose
from time import time

def main():

    claims = {
        'iss': 'http://www.example.com',
        'exp': int(time()) + 3600,
        'sub': 42,
    }

    # *** JWK
    # *** A JSON Web Key (JWK) [6] is a JSON data structure that represents a cryptographic key. 
    # Using a JWK rather than one or more parameters allows for a generalized key as input that can be applied to a number of different algorithms that may expect a different number of inputs. 
    # All JWE and JWS operations expect a JWK rather than inflexible function parameters.
    # JWK format

    jwk = {'k': 'password'}





if __name__ == '__main__':

    main()