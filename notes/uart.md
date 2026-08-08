# UART1 Baud Rate Calculation

The UART uses the PL011 baud-rate formula:

```text
baudrate = UART_CLK / (16 × divisor)
```

The divisor is split into two parts:

```text
divisor = IBRD + FBRD / 64
```

where:

* `IBRD` is the integer part of the divisor.
* `FBRD` is the fractional part, represented using 6 bits.

## Avoiding floating-point arithmetic

Instead of calculating the divisor as a floating-point number, multiply it by 64:

```text
divisor × 64 = UART_CLK × 64 / (16 × baudrate)
```

Since `64 / 16 = 4`:

```text
div = 4 × UART_CLK / baudrate
```

This means `div` is effectively a fixed-point number where the lower 6 bits represent the fractional portion.

The integer and fractional parts can then be extracted using:

```text
IBRD = div >> 6
FBRD = div & 0x3F
```

`0x3F` is binary `111111`, so it extracts the lowest 6 bits.

## Example: 150 MHz clock, 115200 baud

Given:

```text
UART_CLK = 150,000,000 Hz
baudrate = 115,200
```

Calculate:

```text
div = (4 × 150,000,000) / 115,200
    = 5208
```

Extract the integer part:

```text
IBRD = 5208 >> 6
     = 81
```

Extract the fractional part:

```text
FBRD = 5208 & 0x3F
     = 8
```

Therefore:

```text
IBRD = 81
FBRD = 8
```

The actual divisor represented by these values is:

```text
81 + 8/64
= 81.125
```

The resulting baud rate is approximately:

```text
150,000,000 / (16 × 81.125)
≈ 115207 baud
```

which is extremely close to the requested `115200 baud`.

## Why the code uses `>> 6` and `& 0x3F`

The UART's fractional divisor has 6 bits.

Therefore, multiplying the divisor by 64 moves the fractional portion into those 6 bits:

```text
                 integer       fractional
                    ↓               ↓
div =  [ IBRD bits ][ FBRD 6 bits ]
                    ↑               ↑
                  >> 6            & 0x3F
```

So:

```text
div >> 6
```

removes the 6 fractional bits and gives the integer divisor.

And:

```text
div & 0x3F
```

keeps only those 6 fractional bits.

## Important note

The calculation above uses integer division, so the divisor is truncated rather than rounded. For better accuracy, the divisor can instead be rounded to the nearest integer before splitting it into `IBRD` and `FBRD`.
