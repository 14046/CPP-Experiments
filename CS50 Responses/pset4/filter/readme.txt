Only filter() passes its test results.
reflect(), blur(), and edges() seem to work properly to the naked eye, but don't pass all their tests.
The hexadecimal values of certain pixels do not output as expected.

TODO:

Debug reflect()
Debug blur()
Debug edges()

RESULTS:

:) helpers.c exists
:) filter compiles
:) grayscale correctly filters single pixel with whole number average
:) grayscale correctly filters single pixel without whole number average
:) grayscale leaves alone pixels that are already gray
:) grayscale correctly filters simple 3x3 image
:) grayscale correctly filters more complex 3x3 image
:) grayscale correctly filters 4x4 image
:( reflect correctly filters 1x2 image
    expected "0 0 255\n255 0...", not "200 0 0\n0 0 2..."
:( reflect correctly filters 1x3 image
    expected "0 0 255\n0 255...", not "0 0 0\n0 255 0..."
:( reflect correctly filters image that is its own mirror image
    expected "255 0 0\n255 0...", not "0 255 0\n255 0..."
:( reflect correctly filters 3x3 image
    expected "70 80 90\n40 5...", not "110 130 140\n4..."
:( reflect correctly filters 4x4 image
    expected "100 110 120\n7...", not "110 130 140\n1..."
:( blur correctly filters middle pixel
    expected "127 140 149\n", not "60 75 85\n"
:( blur correctly filters pixel on edge
    expected "80 95 105\n", not "0 0 0\n"
:( blur correctly filters pixel in corner
    expected "70 85 95\n", not "0 0 0\n"
:( blur correctly filters 3x3 image
    expected "70 85 95\n80 9...", not "0 0 0\n0 0 0\n..."
:( blur correctly filters 4x4 image
    expected "70 85 95\n80 9...", not "0 0 0\n0 0 0\n..."
:) edges correctly filters middle pixel
:( edges correctly filters pixel on edge
    expected "213 228 255\n", not "0 0 0\n"
:( edges correctly filters pixel in corner
    expected "76 117 255\n", not "0 0 0\n"
:( edges correctly filters 3x3 image
    expected "76 117 255\n21...", not "0 0 0\n0 0 0\n..."
:( edges correctly filters 4x4 image
    expected "76 117 255\n21...", not "0 0 0\n0 0 0\n..."