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

To change LED states you need to first send the row (1-19) to change. Then send
3 integers, 0-524287, representing LED state in Red Green and Blue for that row.

Rows count up from the bottom going from 1-19. The LED states refer to the LEDs
with each bit representing an LED, which are big-endian on the left.

Example:

    < 10
    > Row 10 selected
    < 314572 157286 78643
    > Set state to {314572, 157286, 78643}
    # Set the 10th to an RGBW repeating pattern starting on the left

For the current prototype limits are 1-4 and only blue is controllable (state 0-15).

## WIP

This project is still very much work in progress. Updates will happen randomly
as parts arrive and knowledge is gained. This is my first real electronics
project so it may take a while if you're following along. I was just stoked to
get the shift register working:

![](https://f.cloud.github.com/assets/2546/2133182/88714a80-92be-11e3-959c-c7370c40f461.gif)
