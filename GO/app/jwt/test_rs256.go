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

	// Code in JWT does check the '\n'
	Device_Factory_Private_KEY = "-----BEGIN RSA PRIVATE KEY-----\nMIIEpAIBAAKCAQEAwRbMM42iqZstI7aGC5ngjgjJpGuZxBMYKyCa36i+A6nxnXnXDlk74ALMJAJtLiHc5SInCpn339rFt5vORJ6gIJdhb83d3zevLxe4DCNLmqJHAFi7hM5rzV98TO9Py1MxWG2Z0SFdK3FuG0UxtF5gtUpuDzLMARrSPKFEMFeAISu0QvWyps7utBCVzUKYnTwfNVtrIeI5QoOzRmLW9XZkGzN1PWR1vnEIIAZfk/l96rAy94HBs9XG6Scocwrj7DeGrto43RB1baXgRYNLGEHUAuwHV4tdv/Vkf3+iNrjJTMCHTfVOPsUps9i3GeS2iG2XNM6ByekWXx7ZvYXJWRUNxwIDAQABAoIBAGVN4LTrinwRvg0OpiVQBlB+q8xn57THj9aQtLDDh23Eq89DLWGJz7Anx5Lc8wtRGOPelz0oqrP3w+QhCodV8g0nXyeZit6iCHdcqmMz4Wav3TCBXWDALC8D+eMja2nxq+IJHrpqFsfEK1CDbSCEo5h6BGRU8lNiDwtgULZMMh00NYk5AgLuPb3CrZv24AbOEWD8164Vqs61c2ajHAh87+Wtd7iOT+eehAvv7JnznOoinmcv2/pj+HptL5XhjiWg4xB2ac3Ea1/10Z+MVwBCd+4XAp+0boFo1W4BPlJVLx8w4Q4UEjVi5Gf3IdPT31D0Lb9o86R/oW8OCztfF4qVoIECgYEA/TsrX+72W6C9s2sLa045tzQ7JWrHN0b7fgz2tXMqYp+J/G/78vu/sKrVw9LZSlraoE0QXYJQGxDd1R0mKsFxR8eCyhI7jwMFXBE5s2WuZ401Jpl0KGHX3mIk4cXUcRUcriQqDhfPYCWmG0RVLJZJRrGMRSkgYd+NB/rBKeKjPlsCgYEAwzNIJ6AE4lLQegpEjIHFWm5giQ8KJReGSUQ23K/5Y73qS5vtJzps4H42vUYv3/PnI85ugkF8PTCEGUx5XI2nzdgF3+4bHahxsD2YKpquKnXXZM1nwBrfxCDCawBpZYbbt1bneyr47kjH6zWIfK/h2jHYq1B4Id1xsrfZzjTyYgUCgYEA1daXZCV4qBtu1gm41N5z4n8ayxgGLmmkiecMlmEwE6RBc4hlK+TnFJrOdNSiZSWfpOouvagDWTe+++3ngwdjT4fsrBMFdFjKt9pb7WAaDJuznGrNKiSlk8cw+e6C3RNE6tDjKo90sO5Z/ICRpFsseaQInYaDL+MFRw26/FHEJC0CgYBc1Ua7kZ7BBCGh6MAxEoaJO3UtublZapaywX5V9lrk1K1YyA9BWMfu/BeMbJTYLWb/4G0uBXbQowIwBe6x1ay4eMRSeyrqL/Hhn2l+2ZF7IBAQIJ/2/NDutaXAvbFiV4Cm8O2l5gn9SR/K/OqsYflHi+0/jEWV1Xr9Q/KR3xxnAQKBgQCIy0yZextMpdaS22mttXol5zcsJuVFeabLO7Jj3eJAedAlgR4hUUkjcWs4qRvJRoQQ4S7FmO4l2p0brnnhFclJzt7xDI2QTWU+EE7OrdFnKYSV4n7LE1/s7/npW5wRUI5ZKeQTw4zLq4fauNksCcUUANqG0uv1TPP6BIZJCivW6w==\n-----END RSA PRIVATE KEY-----"
)

func test_jwt_encoding_decoding_rs() {

	{
		// jwt rs256 encoding
		token := jwt.NewWithClaims(jwt.SigningMethodRS256, jwt.MapClaims{
			"foo": "bar",
			"nbf": time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
		})

		// Sign and get the complete encoded token as a string using the secret
		rsa, err := jwt.ParseRSAPrivateKeyFromPEM([]byte(Device_Factory_Private_KEY))
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
		// jwt.Parse(TokenString)

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
		mySigningKey := []byte("AllYourBase")

		// Create the Claims
		// StandardClaims in body
		claims := &jwt.StandardClaims{
			ExpiresAt: 1569805261,
			Issuer:    "test",
		}

		token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
		ss, err := token.SignedString(mySigningKey)
		fmt.Printf("%v %v", ss, err)
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
		mySigningKey := []byte("testkeyforsigning")

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

		token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
		ss, err := token.SignedString(mySigningKey)
		fmt.Printf("%v %v", ss, err)

		// decoding
		newtoken, err := jwt.ParseWithClaims(ss, &MyCustomClaims{}, func(token *jwt.Token) (interface{}, error) {
			return []byte("testkeyforsigning"), nil
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
