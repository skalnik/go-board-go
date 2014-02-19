# Go board, Go!

An LED based Go board.

## Background

After the frustrations of a normal Go board being knocked around, @sshirokov &
myself started brainstorming how to make a board which is less susceptible to
pieces being knocked around. One of our DJ friends said we should mash it up
with a [Monome](http://monome.org/), and then once I stumbled upon the [4x4 LED
Compatible Button Pad](https://www.sparkfun.com/products/7835) on Sparkfun,
things have taken off from there.

## Firmware Serial API

A basic serial API is available which allows control of the LEDs and alerts when
a button is pressed.

There is a framed protocol to change LED states. Each frame starts with an
`0xAD` constant, followed by the size of the message, then the message itself,
with a checksum at the end.

| Offset  | Description                                                    |
|---------|----------------------------------------------------------------|
| 0x00    | Frame start - constant 0xAD                                    |
| 0x02    | Message length - 0x00-0xFF With the upper bound being unlikely |
| 0x03... | Data. Starting at byte 0x03 and for N bytes                    |
| 0x03+N  | CRC8 Checksum                                                  |

Then treating the `message` part of the frame as

| Offset | Description |
|--------|-------------|
| 0x00   | Operation   |
| 0x01+  | Args        |

The only supported message is Set LED State, which takes the location of the LED
in X then Y coordinates, and then the color value of the LED:

| Value | Description                    |
|-------|--------------------------------|
| 0x01  | Red                            |
| 0x02  | Green                          |
| 0x04  | Blue                           |
| 0x??  | Or the above together for more |

So setting the LED at (5,5) to Red would look something like this:

| Offset  | Value  | Description                                                           |
|---------|--------|-----------------------------------------------------------------------|
| 0x00    | 0xAD   | Start                                                                 |
| 0x01    | 0x04   | Length of message                                                     |
| 0x02    | 0x01   | Set LED State                                                         |
| 0x03    | 0x05   | X position 5                                                          |
| 0x04    | 0x05   | Y position 5                                                          |
| 0x05    | 0x01   | Color value in LSB, 0x01 red, 0x02 green, 0x04 blue (OR for multiple) |
| 0x06    | 0x04   | CRC8 checksum                                                         |

## WIP

This project is still very much work in progress. Updates will happen randomly
as parts arrive and knowledge is gained. This is my first real electronics
project so it may take a while if you're following along. I was just stoked to
get the shift register working:

![](https://f.cloud.github.com/assets/2546/2133182/88714a80-92be-11e3-959c-c7370c40f461.gif)
