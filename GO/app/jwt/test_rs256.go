package main

import (
	"fmt"
	"time"

	"github.com/dgrijalva/jwt-go"
)

const (

	// DeviceFactory.cert
	Device_Factory_Cert_PEM = `-----BEGIN CERTIFICATE-----
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
-----END CERTIFICATE-----`

	// DeviceFactory.der (base64)
	Device_Factory_Cert_DER = "MIIDWTCCAkGgAwIBAgIUDgvGbBTAYI68i0R4Hg3tqjkSNgEwDQYJKoZIhvcNAQELBQAwPTEhMB8GA1UEChMYQWthbWFpIFRlY2hub2xvZ2llcyBJbmMuMRgwFgYDVQQDEw9EZXZpY2VQb3N0dXJlQ0EwHhcNMTgxMDAxMTg1MDAyWhcNMjAxMDAxMTg0MTMzWjA7MSEwHwYDVQQKDBhBa2FtYWkgVGVjaG5vbG9naWVzIEluYy4xFjAUBgNVBAMMDURldmljZUZhY3RvcnkwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDBFswzjaKpmy0jtoYLmeCOCMmka5nEExgrIJrfqL4DqfGdedcOWTvgAswkAm0uIdzlIicKmfff2sW3m85EnqAgl2Fvzd3fN68vF7gMI0uaokcAWLuEzmvNX3xM70/LUzFYbZnRIV0rcW4bRTG0XmC1Sm4PMswBGtI8oUQwV4AhK7RC9bKmzu60EJXNQpidPB81W2sh4jlCg7NGYtb1dmQbM3U9ZHW+cQggBl+T+X3qsDL3gcGz1cbpJyhzCuPsN4au2jjdEHVtpeBFg0sYQdQC7AdXi12/9WR/f6I2uMlMwIdN9U4+xSmz2LcZ5LaIbZc0zoHJ6RZfHtm9hclZFQ3HAgMBAAGjUzBRMAwGA1UdEwEB/wQCMAAwHwYDVR0jBBgwFoAUMyFh52X89c5pH570arS3hulJevAwEwYDVR0lBAwwCgYIKwYBBQUHAwIwCwYDVR0PBAQDAgWgMA0GCSqGSIb3DQEBCwUAA4IBAQA/2QTpKdI7ciHRNZve8qu7IzA8Ocq+HmVOLKO6wzRmlIy5t0Aey3mceKgCap0scTIXY9qEnXYTIxGs5aGjSpclFelg+pv2ZWRu3gJu6q5fLdm2fF/2cdRbyHmStMwZa6ooqemvi70J+TmUUPdaruVy8VYJg95/f9V2R6xo7rRjVv6jWcLfE+xPO9Z2kWw8PFIvwds8CQrwP2TGOzp1fP2ycujDzfeQA83gXYFdFUcA0jDDJtSwX9yBGgqFnDntQTH6X58T5njdOCM90YYlPVZX1K7wVWCMmePoUymFPBUUbctfYnsyOg74EATRURsDhhVQXBoltZK7Z6Mw3l76HQip"

	Public_KEY = `-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnzyis1ZjfNB0bBgKFMSv
vkTtwlvBsaJq7S5wA+kzeVOVpVWwkWdVha4s38XM/pa/yr47av7+z3VTmvDRyAHc
aT92whREFpLv9cj5lTeJSibyr/Mrm/YtjCZVWgaOYIhwrXwKLqPr/11inWsAkfIy
tvHWTxZYEcXLgAXFuUuaS3uF9gEiNQwzGTU1v0FqkqTBr4B8nW3HCN47XUu0t8Y0
e+lf4s4OxQawWD79J9/5d3Ry0vbV3Am1FtGJiJvOwRsIfVChDpYStTcHTCMqtvWb
V6L11BWkpzGXSW4Hv43qa+GSYOD2QU68Mb59oSk2OB+BtOLpJofmbGEGgvmwyCI9
MwIDAQAB
-----END PUBLIC KEY-----`

	Private_KEY = `-----BEGIN RSA PRIVATE KEY-----
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
-----END RSA PRIVATE KEY-----`
)

func test_jwt_encoding_decoding_rs() {

	{
		// jwt rs256 encoding
		token := jwt.NewWithClaims(jwt.SigningMethodRS256, jwt.MapClaims{
			"foo": "bar",
			"nbf": time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
		})

		// Sign and get the complete encoded token as a string using the secret
		rsa, err := jwt.ParseRSAPrivateKeyFromPEM([]byte(Private_KEY))
		if err != nil {
			fmt.Println(err)
			panic(err)
		}

		TokenString, err := token.SignedString(rsa)
		if err != nil {
			fmt.Println(err)
			panic(err)
		}
		fmt.Println(TokenString)

		// jwt rs356 decoding
		token, err = jwt.Parse(TokenString, func(token *jwt.Token) (interface{}, error) {
			return jwt.ParseRSAPublicKeyFromPEM([]byte(Public_KEY))
		})

		if err != nil {
			fmt.Println(err)
			panic(err)
		}

		fmt.Println("Raw : ", token.Raw)
		fmt.Println("Header : ", token.Header)
		if claims, ok := token.Claims.(jwt.MapClaims); ok {
			fmt.Println("Claims : ", claims)

			fmt.Println("Expires At : ", claims.VerifyExpiresAt(time.Now().Unix(), false))
			fmt.Println("Issues At : ", claims.VerifyIssuedAt(time.Now().Unix(), false))
			fmt.Println("Issuer : ", claims.VerifyIssuer("syx", false))
			fmt.Println("Not before : ", claims.VerifyNotBefore(time.Now().Unix(), false))
		}
		fmt.Println("Signature : ", token.Signature)
		fmt.Println("Valid : ", token.Valid)

	}

	{
		// Token from another example.  This token is expired
		var tokenString = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJmb28iOiJiYXIiLCJleHAiOjE1MDAwLCJpc3MiOiJ0ZXN0In0.HE7fK0xOQwFEr4WDgRWj4teRPZ6i3GLwD5YCm6Pwu_c"

		token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
			return []byte("AllYourBase"), nil
		})

		if token.Valid {
			fmt.Println("You look nice today")
		} else if ve, ok := err.(*jwt.ValidationError); ok {
			if ve.Errors&jwt.ValidationErrorMalformed != 0 {
				fmt.Println("That's not even a token")
			} else if ve.Errors&(jwt.ValidationErrorExpired|jwt.ValidationErrorNotValidYet) != 0 {
				// Token is either expired or not active yet
				fmt.Println("Timing is everything")
			} else {
				fmt.Println("Couldn't handle this token:", err)
			}
		} else {
			fmt.Println("Couldn't handle this token:", err)
		}
	}

	{
		// standard HMAC decoding
		// sample token string taken from the New example
		tokenString := "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJmb28iOiJiYXIiLCJuYmYiOjE0NDQ0Nzg0MDB9.u1riaD1rW97opCoAuRCTy4w58Br-Zk-bh7vLiRIsrpU"

		// Parse takes the token string and a function for looking up the key. The latter is especially
		// useful if you use multiple keys for your application.  The standard is to use 'kid' in the
		// head of the token to identify which key to use, but the parsed token (head and claims) is provided
		// to the callback, providing flexibility.
		token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
			// Don't forget to validate the alg is what you expect:
			if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
				return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
			}

			// hmacSampleSecret is a []byte containing your secret, e.g. []byte("my_secret_key")
			return []byte("my_secret_key"), nil
		})

		if claims, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
			fmt.Println(claims["foo"], claims["nbf"])
		} else {
			fmt.Println(err)
		}
	}

	fmt.Println(" ----- test_basic_encoding_decoding ----- ")

	// standard claim encoding
	{
		// Create the Claims
		// StandardClaims in body
		claims := &jwt.StandardClaims{
			Audience:  "syx",
			ExpiresAt: time.Now().Add(time.Hour * 2).Unix(),
			Id:        "123-456-789",
			Issuer:    "syx",
			IssuedAt:  time.Now().Unix(),
			NotBefore: time.Now().Unix(),
			Subject:   "syx-testing-001",
		}

		token := jwt.NewWithClaims(jwt.SigningMethodRS256, claims)

		// Sign and get the complete encoded token as a string using the secret
		rsa, err := jwt.ParseRSAPrivateKeyFromPEM([]byte(Private_KEY))
		if err != nil {
			fmt.Println(err)
			panic(err)
		}

		TokenString, err := token.SignedString(rsa)
		if err != nil {
			fmt.Println(err)
			panic(err)
		}
		fmt.Println(TokenString)

		// Parse token
		claims = &jwt.StandardClaims{
			ExpiresAt: time.Now().Add(time.Hour * 2).Unix(),
		}

		token, err = jwt.ParseWithClaims(TokenString, claims, func(token *jwt.Token) (interface{}, error) {

			if _, ok := token.Method.(*jwt.SigningMethodRSA); !ok {
				return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
			}

			return jwt.ParseRSAPublicKeyFromPEM([]byte(Public_KEY))
		})

		if err != nil {
			fmt.Println(err)
			panic(err)
		}

		fmt.Println("Raw : ", token.Raw)
		fmt.Println("Header : ", token.Header)
		if claims, ok := token.Claims.(*jwt.StandardClaims); ok && token.Valid {
			fmt.Println("Claims : ", claims)
			fmt.Println("Audience : ", claims.Audience)
			fmt.Println("Expired At : ", claims.ExpiresAt)
			fmt.Println("Id : ", claims.Id)
			fmt.Println("IssueAt : ", claims.IssuedAt)
			fmt.Println("Issuer : ", claims.Issuer)
			fmt.Println("NoBefore : ", claims.NotBefore)
			fmt.Println("Subject : ", claims.Subject)

			fmt.Println("Expires At : ", claims.VerifyExpiresAt(time.Now().Unix(), false))
			fmt.Println("Issues At : ", claims.VerifyIssuedAt(time.Now().Unix(), false))
			fmt.Println("Issuer : ", claims.VerifyIssuer("syx", false))
			fmt.Println("Not before : ", claims.VerifyNotBefore(time.Now().Unix(), false))
		}
		fmt.Println("Signature : ", token.Signature)
		fmt.Println("Valid : ", token.Valid)

	}

	// customed claim decoding
	{
		tokenString := "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJmb28iOiJiYXIiLCJleHAiOjE1MDAwLCJpc3MiOiJ0ZXN0In0.HE7fK0xOQwFEr4WDgRWj4teRPZ6i3GLwD5YCm6Pwu_c"

		type MyCustomClaims struct {
			Foo string `json:"foo"`
			jwt.StandardClaims
		}

		// sample token is expired.  override time so it parses as valid
		//at(time.Unix(0, 0), func() {
		token, err := jwt.ParseWithClaims(tokenString, &MyCustomClaims{}, func(token *jwt.Token) (interface{}, error) {
			return []byte("AllYourBase"), nil
		})

		if claims, ok := token.Claims.(*MyCustomClaims); ok && token.Valid {
			fmt.Printf("%v %v", claims.Foo, claims.StandardClaims.ExpiresAt)
		} else {
			fmt.Println(err)
		}
		//})
	}

	// customed claims
	{
		type MyCustomClaims struct {
			Foo string `json:"foo"`
			jwt.StandardClaims
		}

		// Create the Claims
		claims := MyCustomClaims{
			"yuxin sun test",
			jwt.StandardClaims{
				ExpiresAt: time.Now().AddDate(1, 10, 100).Unix(),
				Id:        "yusun",
				Issuer:    "yusun-issuer",
				Subject:   "yusun-sub",
				IssuedAt:  time.Now().Unix(),
				NotBefore: time.Now().Unix(),
			},
		}

		token := jwt.NewWithClaims(jwt.SigningMethodRS256, claims)

		// Sign and get the complete encoded token as a string using the secret
		rsa, err := jwt.ParseRSAPrivateKeyFromPEM([]byte(Private_KEY))
		if err != nil {
			fmt.Println(err)
			panic(err)
		}

		TokenString, err := token.SignedString(rsa)
		if err != nil {
			fmt.Println(err)
			panic(err)
		}
		fmt.Println(TokenString)

		// decoding
		newtoken, err := jwt.ParseWithClaims(TokenString, &MyCustomClaims{}, func(token *jwt.Token) (interface{}, error) {

			if _, ok := token.Method.(*jwt.SigningMethodRSA); !ok {
				return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
			}

			return jwt.ParseRSAPublicKeyFromPEM([]byte(Public_KEY))
		})

		if newClaims, ok := newtoken.Claims.(*MyCustomClaims); ok && !token.Valid {
			fmt.Println("Content: \n", newClaims.Foo,
				newClaims.StandardClaims.ExpiresAt,
				newClaims.StandardClaims.Id,
				newClaims.StandardClaims.Issuer,
				newClaims.StandardClaims.Subject,
				newClaims.StandardClaims.IssuedAt,
				newClaims.StandardClaims.NotBefore)
		} else {
			fmt.Println(err)
		}
	}

}

func test_rs256() {

	fmt.Println("--- test_rs256 ---")

	test_jwt_encoding_decoding_rs()

}
