/* 
Кодирование и раскодирование UTF-8
Реализация алгоритма перевода текста из UTF-32 в UTF-8, и обратно. 

Функция decode выполняет обратное преобразование. Правила кодирования текста в UTF-8 приведены в таблице:

Кодирование символов Unicode в UTF-8
Код символа в Unicode
1
2
3
4
0 0000 0000 0000 0xxx xxxx	0xxx xxxx	—	—	—
0 0000 0000 0yyy yyxx xxxx	110y yyyy	10xx xxxx	—	—
0 0000 zzzz yyyy yyxx xxxx	1110 zzzz	10yy yyyy	10xx xxxx	—
u uuzz zzzz yyyy yyxx xxxx	1111 0uuu	10zz zzzz	10yy yyyy	10xx xxxx
*/
package main

import (
	"fmt"
)

func encode(rs []rune) []byte {
	utf8 := make([]byte, 0)
	for _, r := range rs {
		switch {
		case r < 128:
			utf8 = append(utf8, byte(r))
		case r < 2048:
			utf8 = append(utf8, byte((r>>6)|0b11000000), byte((r&0b111111)|0b10000000))
		case r < 65536:
			utf8 = append(utf8,
 byte((r>>12)|0b11100000), byte(((r>>6)&0b111111)|0b10000000), byte((r&0b111111)|0b10000000))
		default:
			utf8 = append(utf8,
 byte((r>>18)|0b11110000), 
byte(((r>>12)&0b111111)|0b10000000), 
byte(((r>>6)&0b111111)|0b10000000),
 byte((r&0b111111)|0b10000000))
		}
	}
	return utf8
}

func decode(bs []byte) []rune {
	rs := make([]rune, 0)
	for i := 0; i < len(bs); {
		switch {
		case bs[i] < 128:
			rs = append(rs, rune(bs[i]))
			i++
		case bs[i]&0b11100000 == 0b11000000:
			r := (rune(bs[i]&0b11111) << 6) | 
rune(bs[i+1]&0b111111)
			rs = append(rs, r)
			i += 2
		case bs[i]&0b11110000 == 0b11100000:
			r := (rune(bs[i]&0b1111) << 12) | 
(rune(bs[i+1]&0b111111) << 6) | rune(bs[i+2]&0b111111)
			rs = append(rs, r)
			i += 3
		case bs[i]&0b11111000 == 0b11110000:
			r := (rune(bs[i]&0b111) << 18) | 
(rune(bs[i+1]&0b111111) << 12) | (rune(bs[i+2]&0b111111) << 6) | rune(bs[i+3]&0b111111)
			rs = append(rs, r)
			i += 4
		}
	}
	return rs
}

func printUTF32(rs []rune) {
	fmt.Println("UTF-32:", rs)
}

func printUTF8(bs []byte) {
	fmt.Println("UTF-8 Encoded:", bs)
}

func printDecoded(rs []rune) {
	fmt.Println("Decoded UTF-32:", rs)
}

func printString(s string) {
	fmt.Println("Decoded String:", s)
}

func main() {
	s := "∑因@ѣ具希ν}"
	rs := []rune(s)
	encoded := encode(rs)
	decoded := decode(encoded)
	printUTF32(rs)
	printUTF8(encoded)
	printDecoded(decoded)
	printString(string(decoded))
}
