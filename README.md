WHAT IS MOBIN?

Mobin is a representation of **mo**rse code with **bin**ary digits.
Morse is composed of dots '.' and dashes '-'. In mobin, a dot is one bit (1), a dash is two bits (11).
The final string is not represented in binary, but in hexadecimal. So the string "T" will not be represented as "1100", but 0xC -> C. However, the examples provided in the three lines below are in binary, as it helps show how mobin is structured.

Betwen digits, add one 0.  So -. (N) becomes 110 1 -> 0xD
Between letters, add two 0s, so ... --- ... (SOS) becomes 1010100 1101101100 10101 (00)-> 0xA9B654
Between words, add three 0s, so ..- \ ... ..- ... (U SUS) becomes 101011000 10101001010110010101 (000) -> 0xAC54ACA8
Words will only be considered separate through spaces.

Each hexadecimal digit is four bits. If (mobin_len % 4 != 0) we will add (4 - remainder) zeros to make up for it, shown above in parentheses.

In the worst case scenario, a mobin string will be 4.25 times longer than its alphanumerical equivalent. ("!!!!" -> "D6B66B5B35AD9AD6C") (same with '\'', ',' and ')' )
In the  best case scenario, a mobin string will be half as long as its alphanumerical equivalent. ("ee" -> "9") (same with "e ")
In all cases, mobin will occupy less space than its equivalent morse string, even if it is still longer than the alphanumerical string. 

Mobin is case-insensitive.