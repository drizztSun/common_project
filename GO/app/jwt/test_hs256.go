package main

import (
	"encoding/json"
	"fmt"
	"time"

	"github.com/dgrijalva/jwt-go"
)

type JwtHeader struct {
	Alg string   `json:"alg"`
	Typ string   `json:"typ"`
	X5c []string `json:"x5c"`
}

type JwtContent struct {
	Iss string `json:"iss"`
	Exp int32  `json:"exp"`
	Sub string `json:"sub"`
}

func encodeJWTHS256() {

	header := JwtHeader{
		Alg: "HS256",
		Typ: "JWT",
		X5c: []string{
			"MIIEXjCCA0agAwIBAgICE...",
		},
	}

	content := JwtContent{
		Iss: "http://cas.test.com",
		Exp: 1569805261,
		Sub: "yusun_laptop_macbook",
	}

	headerJson, err := json.Marshal(header)
	contentJson, err := json.Marshal(content)

	if err == nil {
		fmt.Println("header json : ", headerJson)
		fmt.Println("content json : ", contentJson)
	}
}

func decodeJWTHS256() {

	// sample token string taken from the New example
	tokenString := "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJmb28iOiJiYXIiLCJuYmYiOjE0NDQ0Nzg0MDB9.u1riaD1rW97opCoAuRCTy4w58Br-Zk-bh7vLiRIsrpU"
	var hmacSampleSecret []byte

	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
		}

		// hmacSampleSecret is a []byte containing your secret, e.g. []byte("my_secret_key")
		fmt.Println("res: ", hmacSampleSecret)
		return hmacSampleSecret, nil
	})

	if claim, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
		fmt.Println(claim["foo"], claim["nbf"])
	} else {
		fmt.Println(err)
	}
}

func test_jwt_encoding_decoding() {

	{
		// standard HMAC encoding
		// Create a new token object, specifying signing method and the claims
		// you would like it to contain.
		hmacSampleSecret := []byte("my-secret")
		token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
			"foo": "bar",
			"nbf": time.Date(2015, 10, 10, 12, 0, 0, 0, time.UTC).Unix(),
		})

		// Sign and get the complete encoded token as a string using the secret
		tokenString, err := token.SignedString(hmacSampleSecret)

		fmt.Println(tokenString, err)
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

func Test_hs256() {

	// encodeJWTHS256();

	test_jwt_encoding_decoding()

	// decodeJWTHS256();
}
