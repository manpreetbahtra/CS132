| declare three constants
    i: dc.b #63
    j: dc.b #3
    k: dc.b #0

|declare storage of one byte in main memory for the result of k and .
    resultk: ds.b 1

    move.b i, D0
    move.b j, D1
    move.b k, D2

|Main loop

| i-j

while: sub.w D1, D0
| if I is greater than or equal to branch to increment k, otherwise end the loop. 
    beg igreaterequal
    jmp 0
igreaterequal: inc.b D2
    move.b D2, resultk
    jmp while
