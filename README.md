<h1>mapH</h1>
mapH is a handheld georeferenced soil pH meter originally built as a demo for the 2018 Cracking the Nut conference. It was meant to illustrate potential applications of novel approaches to small-scale hardware development and production to climate smart agriculture in developing country contexts. It is based on the [DF Robot Analog Spear Tip pH sensor](https://www.dfrobot.com/product-1668.html), Arduino Pro Micro, and the Adafruit FONA 808.

It was just a proof-of-concept demo, so it's pretty rough. It uploads a CSV of the pH reading and the GPS coordinate to Pastebin where it can then be brought into a more useful analysis tool, like Mapbox or OpenGIS.

<h3>Usage</h3>
Turn the switch to the on position. When the green LED is lit and the red is off, the unit has a valid GPS fix and the user can take a sample. Place the soil probe into the soil to be sampled and press the button. The LEDs will flash while a series of 100 readings are very quickly taken and averaged. The red LED will light and the green will turn off, indicating that the reading is being transmitted to the server. When the green LED is lit, the unit is ready to take another sample.

<h3>Research Questions</h3>
mapH was developed as a demonstration of the potential of custom hardware to serve the needs of developing country users in the area of climate smart agriculture. It was developed on the hypothesis that awareness of the relative pH differences of farmers' fields could enable more efficient and effective application of fertilizers and other inputs. Similar tools, scaled for developed country farmers, are available commercially on the same principle (and a review of the literature on the effectiveness of these in practice would be interesting in itself).

Unanswered questions regarding the demo hardware might include:

* Does it in fact accurately read soil pH levels?
* Is this in fact useful when compared with other tools available to farmers, specifically in developing country contexts (i.e., smallholder farmers with limited capital infrastructure)?
* Are there modifications that would make the device more useful?
* What is the best protocol for using the device (in terms of cleaning and caring for the probe, calibration, choosing a sample site, depth of sample, etc.)?
* How might a farmer use the data from the tool to make changes to their farming practices?

<h3>Errata</h3>
The v0.1 design erroneously routed Pin 3 from the pH sensor to D12 on the Arduino; it should have gone to A0 as in the v0.2.