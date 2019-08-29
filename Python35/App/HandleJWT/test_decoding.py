# To verify the jws token

# Header:
# {
#  "x5c": [
#    "MIIFFjCCAv6gAwIBAgIJ<snip-for-email>em/yCmhoyb7n6Xptg=="
#  ],
#  "alg": "RS256",
#  "typ": "JWT"
# }
 
#Payload:
#{
#  "iss": "https://etpcas.akamai.com",
#  "iat": 1565970443,
#  "sub": "3a2bd56f-ac78-4fda-afe2-be9b6188fb2f",
#  "exp": 1565974043
#}

# JWS string
# eyJ4NWMiOlsiTUlJRkZqQ0NBdjZnQXdJQkFnSUpBSlFSN3h0ek9hbmxNQTBHQ1NxR1NJYjNEUUVCQ3dVQU1JR2ZNUXN3Q1FZRFZRUUdFd0pWVXpFV01CUUdBMVVFQ0F3TlRXRnpjMkZqYUhWelpYUjBjekVTTUJBR0ExVUVCd3dKUTJGdFluSnBaR2RsTVJ3d0dnWURWUVFLREJOQmEyRnRZV2tnVkdWamFHNXZiRzluYVdWek1Rd3dDZ1lEVlFRTERBTkxUVWt4R1RBWEJnTlZCQU1NRUVWQlFTQkVaWFpwWTJVZ1EwRWdSekV4SFRBYkJna3Foa2lHOXcwQkNRRVdEbXR0YVVCaGEyRnRZV2t1WTI5dE1CNFhEVEU1TURneE5URXhNamMwTlZvWERUSXdNRGd4TlRFeE1qYzBOVm93Z2FVeEN6QUpCZ05WQkFZVEFsVlRNUll3RkFZRFZRUUlEQTFOWVhOellXTm9kWE5sZEhSek1SSXdFQVlEVlFRSERBbERZVzFpY21sa1oyVXhIREFhQmdOVkJBb01FMEZyWVcxaGFTQlVaV05vYm05c2IyZHBaWE14RERBS0JnTlZCQXNNQTB0TlNURWZNQjBHQTFVRUF3d1dSVUZCSUVSbGRtbGpaU0JEWlhKMGFXWnBZMkYwWlRFZE1Cc0dDU3FHU0liM0RRRUpBUllPYTIxcFFHRnJZVzFoYVM1amIyMHdnZ0VpTUEwR0NTcUdTSWIzRFFFQkFRVUFBNElCRHdBd2dnRUtBb0lCQVFET0lhZXhrWE5qdU5zdWFibDQxZml3eG9jQVNST3Y0SVJFZVd0aGJJT1VEcVdPaytxdzlzSFB0ZWxNdGFVc055emx0MlRmaTVlNlBGMXhUZXdrQnk3QUVGTE8vZEQwS2hvd1ZHbTdFendyYjNrQ2VROEI3Rld6ZGFCQis0c25nbk9ZVk9UQ3ZOMWFFTnYwQlZtTWVBN2NkbjlCMlpVTkhaaGRobytZRmNQQ3VWWGJoZm9zYWRnM2xMQlluOWhuSVlyLzJNK01samtwbkJPN2xMTlBNVmtoRGxMZU9lY0llaEgzdmJiSStZeDIxRU1ISmVFSytsNlorbnV1WXZWR0diNlV4M3Q1NVFRU1NJZElWWG5KQi9ocWVaRlhib2dMcWdUT0VOVS9PR3d1Y2hJRlJYd1NwelpMZzdRL2dWZStiSmx3VE5aUnZUQitIN0prZFM0NWlwdDFBZ01CQUFHalRUQkxNQWtHQTFVZEV3UUNNQUF3SFFZRFZSME9CQllFRk9KU3p1WXVHQ053MktZenlCNmlGcFAvbC9WeE1COEdBMVVkSXdRWU1CYUFGTnQrSHg3dnNVdXU4dElHWm1aekVuVXFBSUlyTUEwR0NTcUdTSWIzRFFFQkN3VUFBNElDQVFBV2JvVWQ5eHp1NGVxQndrbmFhVkVZUkUyZHQ5Q2hPSkZhMEtBcGREUHF1d3ZodW5NRDVPUzBEcFl1VHhRWTZpYnRnTjBRVi9pL2MvaVRENk9ZeFNnbXJDdnp5L1AwYk94NlZ3RFBpVi9Ka1BMUjU0NzlwbjNyZVplb0pNMWw4VmVyMm51VWp0dFpIRFlNTWE0TFIzdnJrUEhpK1o5S1QvRjVyU1E4aHZRNGRSQXIyUEduQjltQzY3S3IxZldaR2VHbDNCZnlIRWY2M2gwWm1OWHVQakthSml5eTdYODAxbzVheTBWRlNQV3VsZlBGemlzNkdLNmdNVFYwQ00vTCtQK3U3dFZoTnBkaE5CVzRoSnRDMmswbWlSZ2RORXJqMlBjOGJITmkxRko0RnZydnF6elZuUUVxYWYybnVhWWNndDBETVh6K3YvdFlkN2tPbENBVFEwNUloL09EYTJxMnUvRU9xUFNTUFJwSThiSlQrN0RyUGpXTTB5K0ZQOHhEdWt3MUNYLzM2WHZERUhuZWd2ZWlJZiszQWNIZjMxZE4rRnV5VHR0cnFZckVmSHVGbWlRbm1vUFF2U21GOUlLMHRhcTM2UUJyYUNKaDBUZ0RjZGV1Nmg3Tm9ZVVJsRXF5dG56blk3RXRuMk0wTUx3UG5qWDZkV0Y2VWFWUnBLMGFKUzNSait6SC9RMVB6WlNIanBSUDd5YnJsZDA0SWZVREVuVG9wdmFqVTZ1ZjdTbUtpRTFPTFJ0S05VaWt4N3ZMREVCQ1RpV1JIcXdud0ZKcG5Vc3pBNlJ6bXhFRkxQVUsvM2w0Zjl0MHkvbk9MQ0FHc3NyREZ1WUVya09mYzhWRlltMzVKeEZmNWtDa3lTbTM0NUtpL3dlVk5UemxFZW0veUNtaG95YjduNlhwdGc9PSJdLCJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJodHRwczovL2V0cGNhcy5ha2FtYWkuY29tIiwiaWF0IjoxNTY1OTcwNDQzLCJzdWIiOiIzYTJiZDU2Zi1hYzc4LTRmZGEtYWZlMi1iZTliNjE4OGZiMmYiLCJleHAiOjE1NjU5NzQwNDN9.mb2iOsillWacFiFPg7sb3Wf6t41rM_WOXHCMyMBRVi8DKTVa9bbl2xHHG4M8waSESfOUVhqoqvALn80bHcGbtknIKy8rqjaJjRBzrv5TH3WXjVzOMbqbbn42GDpiDnsBr4h0g1Zfz64msc7QySy2VG8CWowSFoypn71uZ_naIBRUk8GQ5R6N5-7Mxf55zc29U0sHyXbfwTKSeUjKzZBQxtHKbTlPmq1r1JKVrDdS-tfOuXFY9V6SlIzxlWPq6puPtz7Lrjxwwhb9rPHKTKcKZ6oqcRjaUSVClORuchpSgfzCzeINazt6--HtUHyCoQU4S-_9X2ZSulIJ-9ZmoDbrqg

# base64URLDecoding result at below. 

# {"x5c":
#   ["MIIFFjCCAv6gAwIBAgIJAJQR7xtzOanlMA0GCSqGSIb3DQEBCwUAMIGfMQswCQYDVQQGEwJVUzEWMBQGA1UECAwNTWFzc2FjaHVzZXR0czESMBAGA1UEBwwJQ2FtYnJpZGdlMRwwGgYDVQQKDBNBa2FtYWkgVGVjaG5vbG9naWVzMQwwCgYDVQQLDANLTUkxGTAXBgNVBAMMEEVBQSBEZXZpY2UgQ0EgRzExHTAbBgkqhkiG9w0BCQEWDmttaUBha2FtYWkuY29tMB4XDTE5MDgxNTExMjc0NVoXDTIwMDgxNTExMjc0NVowgaUxCzAJBgNVBAYTAlVTMRYwFAYDVQQIDA1NYXNzYWNodXNldHRzMRIwEAYDVQQHDAlDYW1icmlkZ2UxHDAaBgNVBAoME0FrYW1haSBUZWNobm9sb2dpZXMxDDAKBgNVBAsMA0tNSTEfMB0GA1UEAwwWRUFBIERldmljZSBDZXJ0aWZpY2F0ZTEdMBsGCSqGSIb3DQEJARYOa21pQGFrYW1haS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDOIaexkXNjuNsuabl41fiwxocASROv4IREeWthbIOUDqWOk+qw9sHPtelMtaUsNyzlt2Tfi5e6PF1xTewkBy7AEFLO/dD0KhowVGm7Ezwrb3kCeQ8B7FWzdaBB+4sngnOYVOTCvN1aENv0BVmMeA7cdn9B2ZUNHZhdho+YFcPCuVXbhfosadg3lLBYn9hnIYr/2M+MljkpnBO7lLNPMVkhDlLeOecIehH3vbbI+Yx21EMHJeEK+l6Z+nuuYvVGGb6Ux3t55QQSSIdIVXnJB/hqeZFXbogLqgTOENU/OGwuchIFRXwSpzZLg7Q/gVe+bJlwTNZRvTB+H7JkdS45ipt1AgMBAAGjTTBLMAkGA1UdEwQCMAAwHQYDVR0OBBYEFOJSzuYuGCNw2KYzyB6iFpP/l/VxMB8GA1UdIwQYMBaAFNt+Hx7vsUuu8tIGZmZzEnUqAIIrMA0GCSqGSIb3DQEBCwUAA4ICAQAWboUd9xzu4eqBwknaaVEYRE2dt9ChOJFa0KApdDPquwvhunMD5OS0DpYuTxQY6ibtgN0QV/i/c/iTD6OYxSgmrCvzy/P0bOx6VwDPiV/JkPLR5479pn3reZeoJM1l8Ver2nuUjttZHDYMMa4LR3vrkPHi+Z9KT/F5rSQ8hvQ4dRAr2PGnB9mC67Kr1fWZGeGl3BfyHEf63h0ZmNXuPjKaJiyy7X801o5ay0VFSPWulfPFzis6GK6gMTV0CM/L+P+u7tVhNpdhNBW4hJtC2k0miRgdNErj2Pc8bHNi1FJ4FvrvqzzVnQEqaf2nuaYcgt0DMXz+v/tYd7kOlCATQ05Ih/ODa2q2u/EOqPSSPRpI8bJT+7DrPjWM0y+FP8xDukw1CX/36XvDEHnegveiIf+3AcHf31dN+FuyTttrqYrEfHuFmiQnmoPQvSmF9IK0taq36QBraCJh0TgDcdeu6h7NoYURlEqytnznY7Etn2M0MLwPnjX6dWF6UaVRpK0aJS3Rj+zH/Q1PzZSHjpRP7ybrld04IfUDEnTopvajU6uf7SmKiE1OLRtKNUikx7vLDEBCTiWRHqwnwFJpnUszA6RzmxEFLPUK/3l4f9t0y/nOLCAGssrDFuYErkOfc8VFYm35JxFf5kCkySm345Ki/weVNTzlEem/yCmhoyb7n6Xptg=="],
#    "alg":"RS256",
#    "typ":"JWT"
# }
# {
#   "iss":"https://etpcas.akamai.com",
#   "iat":1565970443,
#   "sub":"3a2bd56f-ac78-4fda-afe2-be9b6188fb2f",
#   "exp":1565974043

import json
import base64
import jwt
from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa

import cert_cryptography
#from cert_cryptography import output_cert_Info


# publickey = b'-----BEGIN CERTIFICATE-----MIIFFjCCAv6gAwIBAgIJAJQR7xtzOanlMA0GCSqGSIb3DQEBCwUAMIGfMQswCQYDVQQGEwJVUzEWMBQGA1UECAwNTWFzc2FjaHVzZXR0czESMBAGA1UEBwwJQ2FtYnJpZGdlMRwwGgYDVQQKDBNBa2FtYWkgVGVjaG5vbG9naWVzMQwwCgYDVQQLDANLTUkxGTAXBgNVBAMMEEVBQSBEZXZpY2UgQ0EgRzExHTAbBgkqhkiG9w0BCQEWDmttaUBha2FtYWkuY29tMB4XDTE5MDgxNTExMjc0NVoXDTIwMDgxNTExMjc0NVowgaUxCzAJBgNVBAYTAlVTMRYwFAYDVQQIDA1NYXNzYWNodXNldHRzMRIwEAYDVQQHDAlDYW1icmlkZ2UxHDAaBgNVBAoME0FrYW1haSBUZWNobm9sb2dpZXMxDDAKBgNVBAsMA0tNSTEfMB0GA1UEAwwWRUFBIERldmljZSBDZXJ0aWZpY2F0ZTEdMBsGCSqGSIb3DQEJARYOa21pQGFrYW1haS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDOIaexkXNjuNsuabl41fiwxocASROv4IREeWthbIOUDqWOk+qw9sHPtelMtaUsNyzlt2Tfi5e6PF1xTewkBy7AEFLO/dD0KhowVGm7Ezwrb3kCeQ8B7FWzdaBB+4sngnOYVOTCvN1aENv0BVmMeA7cdn9B2ZUNHZhdho+YFcPCuVXbhfosadg3lLBYn9hnIYr/2M+MljkpnBO7lLNPMVkhDlLeOecIehH3vbbI+Yx21EMHJeEK+l6Z+nuuYvVGGb6Ux3t55QQSSIdIVXnJB/hqeZFXbogLqgTOENU/OGwuchIFRXwSpzZLg7Q/gVe+bJlwTNZRvTB+H7JkdS45ipt1AgMBAAGjTTBLMAkGA1UdEwQCMAAwHQYDVR0OBBYEFOJSzuYuGCNw2KYzyB6iFpP/l/VxMB8GA1UdIwQYMBaAFNt+Hx7vsUuu8tIGZmZzEnUqAIIrMA0GCSqGSIb3DQEBCwUAA4ICAQAWboUd9xzu4eqBwknaaVEYRE2dt9ChOJFa0KApdDPquwvhunMD5OS0DpYuTxQY6ibtgN0QV/i/c/iTD6OYxSgmrCvzy/P0bOx6VwDPiV/JkPLR5479pn3reZeoJM1l8Ver2nuUjttZHDYMMa4LR3vrkPHi+Z9KT/F5rSQ8hvQ4dRAr2PGnB9mC67Kr1fWZGeGl3BfyHEf63h0ZmNXuPjKaJiyy7X801o5ay0VFSPWulfPFzis6GK6gMTV0CM/L+P+u7tVhNpdhNBW4hJtC2k0miRgdNErj2Pc8bHNi1FJ4FvrvqzzVnQEqaf2nuaYcgt0DMXz+v/tYd7kOlCATQ05Ih/ODa2q2u/EOqPSSPRpI8bJT+7DrPjWM0y+FP8xDukw1CX/36XvDEHnegveiIf+3AcHf31dN+FuyTttrqYrEfHuFmiQnmoPQvSmF9IK0taq36QBraCJh0TgDcdeu6h7NoYURlEqytnznY7Etn2M0MLwPnjX6dWF6UaVRpK0aJS3Rj+zH/Q1PzZSHjpRP7ybrld04IfUDEnTopvajU6uf7SmKiE1OLRtKNUikx7vLDEBCTiWRHqwnwFJpnUszA6RzmxEFLPUK/3l4f9t0y/nOLCAGssrDFuYErkOfc8VFYm35JxFf5kCkySm345Ki/weVNTzlEem/yCmhoyb7n6Xptg==-----END CERTIFICATE-----'

# Der format certificate is base64 encoding certificate
publickey = b'MIIFFjCCAv6gAwIBAgIJAJQR7xtzOanlMA0GCSqGSIb3DQEBCwUAMIGfMQswCQYDVQQGEwJVUzEWMBQGA1UECAwNTWFzc2FjaHVzZXR0czESMBAGA1UEBwwJQ2FtYnJpZGdlMRwwGgYDVQQKDBNBa2FtYWkgVGVjaG5vbG9naWVzMQwwCgYDVQQLDANLTUkxGTAXBgNVBAMMEEVBQSBEZXZpY2UgQ0EgRzExHTAbBgkqhkiG9w0BCQEWDmttaUBha2FtYWkuY29tMB4XDTE5MDgxNTExMjc0NVoXDTIwMDgxNTExMjc0NVowgaUxCzAJBgNVBAYTAlVTMRYwFAYDVQQIDA1NYXNzYWNodXNldHRzMRIwEAYDVQQHDAlDYW1icmlkZ2UxHDAaBgNVBAoME0FrYW1haSBUZWNobm9sb2dpZXMxDDAKBgNVBAsMA0tNSTEfMB0GA1UEAwwWRUFBIERldmljZSBDZXJ0aWZpY2F0ZTEdMBsGCSqGSIb3DQEJARYOa21pQGFrYW1haS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDOIaexkXNjuNsuabl41fiwxocASROv4IREeWthbIOUDqWOk+qw9sHPtelMtaUsNyzlt2Tfi5e6PF1xTewkBy7AEFLO/dD0KhowVGm7Ezwrb3kCeQ8B7FWzdaBB+4sngnOYVOTCvN1aENv0BVmMeA7cdn9B2ZUNHZhdho+YFcPCuVXbhfosadg3lLBYn9hnIYr/2M+MljkpnBO7lLNPMVkhDlLeOecIehH3vbbI+Yx21EMHJeEK+l6Z+nuuYvVGGb6Ux3t55QQSSIdIVXnJB/hqeZFXbogLqgTOENU/OGwuchIFRXwSpzZLg7Q/gVe+bJlwTNZRvTB+H7JkdS45ipt1AgMBAAGjTTBLMAkGA1UdEwQCMAAwHQYDVR0OBBYEFOJSzuYuGCNw2KYzyB6iFpP/l/VxMB8GA1UdIwQYMBaAFNt+Hx7vsUuu8tIGZmZzEnUqAIIrMA0GCSqGSIb3DQEBCwUAA4ICAQAWboUd9xzu4eqBwknaaVEYRE2dt9ChOJFa0KApdDPquwvhunMD5OS0DpYuTxQY6ibtgN0QV/i/c/iTD6OYxSgmrCvzy/P0bOx6VwDPiV/JkPLR5479pn3reZeoJM1l8Ver2nuUjttZHDYMMa4LR3vrkPHi+Z9KT/F5rSQ8hvQ4dRAr2PGnB9mC67Kr1fWZGeGl3BfyHEf63h0ZmNXuPjKaJiyy7X801o5ay0VFSPWulfPFzis6GK6gMTV0CM/L+P+u7tVhNpdhNBW4hJtC2k0miRgdNErj2Pc8bHNi1FJ4FvrvqzzVnQEqaf2nuaYcgt0DMXz+v/tYd7kOlCATQ05Ih/ODa2q2u/EOqPSSPRpI8bJT+7DrPjWM0y+FP8xDukw1CX/36XvDEHnegveiIf+3AcHf31dN+FuyTttrqYrEfHuFmiQnmoPQvSmF9IK0taq36QBraCJh0TgDcdeu6h7NoYURlEqytnznY7Etn2M0MLwPnjX6dWF6UaVRpK0aJS3Rj+zH/Q1PzZSHjpRP7ybrld04IfUDEnTopvajU6uf7SmKiE1OLRtKNUikx7vLDEBCTiWRHqwnwFJpnUszA6RzmxEFLPUK/3l4f9t0y/nOLCAGssrDFuYErkOfc8VFYm35JxFf5kCkySm345Ki/weVNTzlEem/yCmhoyb7n6Xptg=='

privatekey = """-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAnzyis1ZjfNB0bBgKFMSvvkTtwlvBsaJq7S5wA+kzeVOVpVWw
kWdVha4s38XM/pa/yr47av7+z3VTmvDRyAHcaT92whREFpLv9cj5lTeJSibyr/Mr
m/YtjCZVWgaOYIhwrXwKLqPr/11inWsAkfIytvHWTxZYEcXLgAXFuUuaS3uF9gEi
NQwzGTU1v0FqkqTBr4B8nW3HCN47XUu0t8Y0e+lf4s4OxQawWD79J9/5d3Ry0vbV
3Am1FtGJiJvOwRsIfVChDpYStTcHTCMqtvWbV6L11BWkpzGXSW4Hv43qa+GSYOD2
QU68Mb59oSk2OB+BtOLpJofmbGEGgvmwyCI9MwIDAQABAoIBACiARq2wkltjtcjs
kFvZ7w1JAORHbEufEO1Eu27zOIlqbgyAcAl7q+/1bip4Z/x1IVES84/yTaM8p0go
amMhvgry/mS8vNi1BN2SAZEnb/7xSxbflb70bX9RHLJqKnp5GZe2jexw+wyXlwaM
+bclUCrh9e1ltH7IvUrRrQnFJfh+is1fRon9Co9Li0GwoN0x0byrrngU8Ak3Y6D9
D8GjQA4Elm94ST3izJv8iCOLSDBmzsPsXfcCUZfmTfZ5DbUDMbMxRnSo3nQeoKGC
0Lj9FkWcfmLcpGlSXTO+Ww1L7EGq+PT3NtRae1FZPwjddQ1/4V905kyQFLamAA5Y
lSpE2wkCgYEAy1OPLQcZt4NQnQzPz2SBJqQN2P5u3vXl+zNVKP8w4eBv0vWuJJF+
hkGNnSxXQrTkvDOIUddSKOzHHgSg4nY6K02ecyT0PPm/UZvtRpWrnBjcEVtHEJNp
bU9pLD5iZ0J9sbzPU/LxPmuAP2Bs8JmTn6aFRspFrP7W0s1Nmk2jsm0CgYEAyH0X
+jpoqxj4efZfkUrg5GbSEhf+dZglf0tTOA5bVg8IYwtmNk/pniLG/zI7c+GlTc9B
BwfMr59EzBq/eFMI7+LgXaVUsM/sS4Ry+yeK6SJx/otIMWtDfqxsLD8CPMCRvecC
2Pip4uSgrl0MOebl9XKp57GoaUWRWRHqwV4Y6h8CgYAZhI4mh4qZtnhKjY4TKDjx
QYufXSdLAi9v3FxmvchDwOgn4L+PRVdMwDNms2bsL0m5uPn104EzM6w1vzz1zwKz
5pTpPI0OjgWN13Tq8+PKvm/4Ga2MjgOgPWQkslulO/oMcXbPwWC3hcRdr9tcQtn9
Imf9n2spL/6EDFId+Hp/7QKBgAqlWdiXsWckdE1Fn91/NGHsc8syKvjjk1onDcw0
NvVi5vcba9oGdElJX3e9mxqUKMrw7msJJv1MX8LWyMQC5L6YNYHDfbPF1q5L4i8j
8mRex97UVokJQRRA452V2vCO6S5ETgpnad36de3MUxHgCOX3qL382Qx9/THVmbma
3YfRAoGAUxL/Eu5yvMK8SAt/dJK6FedngcM3JEFNplmtLYVLWhkIlNRGDwkg3I5K
y18Ae9n7dHVueyslrb6weq7dTkYDi3iOYRW8HRkIQh06wEdbxt0shTzAJvvCQfrB
jg/3747WSsf/zBTcHihTRBdAv6OmdhV4/dD5YBfLAkLrd+mX7iE=
-----END RSA PRIVATE KEY-----
"""




def testdecoding(token):
    # publicCert = b‘MIIFFjCCAv6gAwIBAgIJAJQR7xtzOanlMA0GCSqGSIb3DQEBCwUAMIGfMQswCQYDVQQGEwJVUzEWMBQGA1UECAwNTWFzc2FjaHVzZXR0czESMBAGA1UEBwwJQ2FtYnJpZGdlMRwwGgYDVQQKDBNBa2FtYWkgVGVjaG5vbG9naWVzMQwwCgYDVQQLDANLTUkxGTAXBgNVBAMMEEVBQSBEZXZpY2UgQ0EgRzExHTAbBgkqhkiG9w0BCQEWDmttaUBha2FtYWkuY29tMB4XDTE5MDgxNTExMjc0NVoXDTIwMDgxNTExMjc0NVowgaUxCzAJBgNVBAYTAlVTMRYwFAYDVQQIDA1NYXNzYWNodXNldHRzMRIwEAYDVQQHDAlDYW1icmlkZ2UxHDAaBgNVBAoME0FrYW1haSBUZWNobm9sb2dpZXMxDDAKBgNVBAsMA0tNSTEfMB0GA1UEAwwWRUFBIERldmljZSBDZXJ0aWZpY2F0ZTEdMBsGCSqGSIb3DQEJARYOa21pQGFrYW1haS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDOIaexkXNjuNsuabl41fiwxocASROv4IREeWthbIOUDqWOk+qw9sHPtelMtaUsNyzlt2Tfi5e6PF1xTewkBy7AEFLO/dD0KhowVGm7Ezwrb3kCeQ8B7FWzdaBB+4sngnOYVOTCvN1aENv0BVmMeA7cdn9B2ZUNHZhdho+YFcPCuVXbhfosadg3lLBYn9hnIYr/2M+MljkpnBO7lLNPMVkhDlLeOecIehH3vbbI+Yx21EMHJeEK+l6Z+nuuYvVGGb6Ux3t55QQSSIdIVXnJB/hqeZFXbogLqgTOENU/OGwuchIFRXwSpzZLg7Q/gVe+bJlwTNZRvTB+H7JkdS45ipt1AgMBAAGjTTBLMAkGA1UdEwQCMAAwHQYDVR0OBBYEFOJSzuYuGCNw2KYzyB6iFpP/l/VxMB8GA1UdIwQYMBaAFNt+Hx7vsUuu8tIGZmZzEnUqAIIrMA0GCSqGSIb3DQEBCwUAA4ICAQAWboUd9xzu4eqBwknaaVEYRE2dt9ChOJFa0KApdDPquwvhunMD5OS0DpYuTxQY6ibtgN0QV/i/c/iTD6OYxSgmrCvzy/P0bOx6VwDPiV/JkPLR5479pn3reZeoJM1l8Ver2nuUjttZHDYMMa4LR3vrkPHi+Z9KT/F5rSQ8hvQ4dRAr2PGnB9mC67Kr1fWZGeGl3BfyHEf63h0ZmNXuPjKaJiyy7X801o5ay0VFSPWulfPFzis6GK6gMTV0CM/L+P+u7tVhNpdhNBW4hJtC2k0miRgdNErj2Pc8bHNi1FJ4FvrvqzzVnQEqaf2nuaYcgt0DMXz+v/tYd7kOlCATQ05Ih/ODa2q2u/EOqPSSPRpI8bJT+7DrPjWM0y+FP8xDukw1CX/36XvDEHnegveiIf+3AcHf31dN+FuyTttrqYrEfHuFmiQnmoPQvSmF9IK0taq36QBraCJh0TgDcdeu6h7NoYURlEqytnznY7Etn2M0MLwPnjX6dWF6UaVRpK0aJS3Rj+zH/Q1PzZSHjpRP7ybrld04IfUDEnTopvajU6uf7SmKiE1OLRtKNUikx7vLDEBCTiWRHqwnwFJpnUszA6RzmxEFLPUK/3l4f9t0y/nOLCAGssrDFuYErkOfc8VFYm35JxFf5kCkySm345Ki/weVNTzlEem/yCmhoyb7n6Xptg==’

    header, payload, signature = token.split('.')
    header = json.loads(base64.urlsafe_b64decode(header))
    data = base64.b64decode(header['x5c'][0].encode('utf-8'))
    key = cert_cryptography.get_der_certificate_public_key(data)

    try:
        result = jwt.decode(token, key, algorithms='RS256')

    except jwt.InvalidIssuerError:
        print("invalude issuer")
    except jwt.DecodeError:
        print("Decoding err")
    except jwt.InvalidAlgorithmError:
        print("Expired Signatured Error")
    except jwt.ExpiredSignatureError:
        print("Signature has been expired")
    else :
        print("Decoding works well")


def Main():

    jws = 'eyJ4NWMiOlsiTUlJRkZqQ0NBdjZnQXdJQkFnSUpBSlFSN3h0ek9hbmxNQTBHQ1NxR1NJYjNEUUVCQ3dVQU1JR2ZNUXN3Q1FZRFZRUUdFd0pWVXpFV01CUUdBMVVFQ0F3TlRXRnpjMkZqYUhWelpYUjBjekVTTUJBR0ExVUVCd3dKUTJGdFluSnBaR2RsTVJ3d0dnWURWUVFLREJOQmEyRnRZV2tnVkdWamFHNXZiRzluYVdWek1Rd3dDZ1lEVlFRTERBTkxUVWt4R1RBWEJnTlZCQU1NRUVWQlFTQkVaWFpwWTJVZ1EwRWdSekV4SFRBYkJna3Foa2lHOXcwQkNRRVdEbXR0YVVCaGEyRnRZV2t1WTI5dE1CNFhEVEU1TURneE5URXhNamMwTlZvWERUSXdNRGd4TlRFeE1qYzBOVm93Z2FVeEN6QUpCZ05WQkFZVEFsVlRNUll3RkFZRFZRUUlEQTFOWVhOellXTm9kWE5sZEhSek1SSXdFQVlEVlFRSERBbERZVzFpY21sa1oyVXhIREFhQmdOVkJBb01FMEZyWVcxaGFTQlVaV05vYm05c2IyZHBaWE14RERBS0JnTlZCQXNNQTB0TlNURWZNQjBHQTFVRUF3d1dSVUZCSUVSbGRtbGpaU0JEWlhKMGFXWnBZMkYwWlRFZE1Cc0dDU3FHU0liM0RRRUpBUllPYTIxcFFHRnJZVzFoYVM1amIyMHdnZ0VpTUEwR0NTcUdTSWIzRFFFQkFRVUFBNElCRHdBd2dnRUtBb0lCQVFET0lhZXhrWE5qdU5zdWFibDQxZml3eG9jQVNST3Y0SVJFZVd0aGJJT1VEcVdPaytxdzlzSFB0ZWxNdGFVc055emx0MlRmaTVlNlBGMXhUZXdrQnk3QUVGTE8vZEQwS2hvd1ZHbTdFendyYjNrQ2VROEI3Rld6ZGFCQis0c25nbk9ZVk9UQ3ZOMWFFTnYwQlZtTWVBN2NkbjlCMlpVTkhaaGRobytZRmNQQ3VWWGJoZm9zYWRnM2xMQlluOWhuSVlyLzJNK01samtwbkJPN2xMTlBNVmtoRGxMZU9lY0llaEgzdmJiSStZeDIxRU1ISmVFSytsNlorbnV1WXZWR0diNlV4M3Q1NVFRU1NJZElWWG5KQi9ocWVaRlhib2dMcWdUT0VOVS9PR3d1Y2hJRlJYd1NwelpMZzdRL2dWZStiSmx3VE5aUnZUQitIN0prZFM0NWlwdDFBZ01CQUFHalRUQkxNQWtHQTFVZEV3UUNNQUF3SFFZRFZSME9CQllFRk9KU3p1WXVHQ053MktZenlCNmlGcFAvbC9WeE1COEdBMVVkSXdRWU1CYUFGTnQrSHg3dnNVdXU4dElHWm1aekVuVXFBSUlyTUEwR0NTcUdTSWIzRFFFQkN3VUFBNElDQVFBV2JvVWQ5eHp1NGVxQndrbmFhVkVZUkUyZHQ5Q2hPSkZhMEtBcGREUHF1d3ZodW5NRDVPUzBEcFl1VHhRWTZpYnRnTjBRVi9pL2MvaVRENk9ZeFNnbXJDdnp5L1AwYk94NlZ3RFBpVi9Ka1BMUjU0NzlwbjNyZVplb0pNMWw4VmVyMm51VWp0dFpIRFlNTWE0TFIzdnJrUEhpK1o5S1QvRjVyU1E4aHZRNGRSQXIyUEduQjltQzY3S3IxZldaR2VHbDNCZnlIRWY2M2gwWm1OWHVQakthSml5eTdYODAxbzVheTBWRlNQV3VsZlBGemlzNkdLNmdNVFYwQ00vTCtQK3U3dFZoTnBkaE5CVzRoSnRDMmswbWlSZ2RORXJqMlBjOGJITmkxRko0RnZydnF6elZuUUVxYWYybnVhWWNndDBETVh6K3YvdFlkN2tPbENBVFEwNUloL09EYTJxMnUvRU9xUFNTUFJwSThiSlQrN0RyUGpXTTB5K0ZQOHhEdWt3MUNYLzM2WHZERUhuZWd2ZWlJZiszQWNIZjMxZE4rRnV5VHR0cnFZckVmSHVGbWlRbm1vUFF2U21GOUlLMHRhcTM2UUJyYUNKaDBUZ0RjZGV1Nmg3Tm9ZVVJsRXF5dG56blk3RXRuMk0wTUx3UG5qWDZkV0Y2VWFWUnBLMGFKUzNSait6SC9RMVB6WlNIanBSUDd5YnJsZDA0SWZVREVuVG9wdmFqVTZ1ZjdTbUtpRTFPTFJ0S05VaWt4N3ZMREVCQ1RpV1JIcXdud0ZKcG5Vc3pBNlJ6bXhFRkxQVUsvM2w0Zjl0MHkvbk9MQ0FHc3NyREZ1WUVya09mYzhWRlltMzVKeEZmNWtDa3lTbTM0NUtpL3dlVk5UemxFZW0veUNtaG95YjduNlhwdGc9PSJdLCJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJodHRwczovL2V0cGNhcy5ha2FtYWkuY29tIiwiaWF0IjoxNTY1OTcwNDQzLCJzdWIiOiIzYTJiZDU2Zi1hYzc4LTRmZGEtYWZlMi1iZTliNjE4OGZiMmYiLCJleHAiOjE1NjU5NzQwNDN9.mb2iOsillWacFiFPg7sb3Wf6t41rM_WOXHCMyMBRVi8DKTVa9bbl2xHHG4M8waSESfOUVhqoqvALn80bHcGbtknIKy8rqjaJjRBzrv5TH3WXjVzOMbqbbn42GDpiDnsBr4h0g1Zfz64msc7QySy2VG8CWowSFoypn71uZ_naIBRUk8GQ5R6N5-7Mxf55zc29U0sHyXbfwTKSeUjKzZBQxtHKbTlPmq1r1JKVrDdS-tfOuXFY9V6SlIzxlWPq6puPtz7Lrjxwwhb9rPHKTKcKZ6oqcRjaUSVClORuchpSgfzCzeINazt6--HtUHyCoQU4S-_9X2ZSulIJ-9ZmoDbrqg'
    
    testdecoding(jws)


if __name__ == "__main__":

    Main()