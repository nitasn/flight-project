# Flight Project


"Flight Project" interprets code (in a made up language) written to control an open source aeroplane simulator.

It's a second-year CS project, by Nitsan and Hodaya, students at Bar-Ilan University.

## Installation

Compile our code:
```bash
g++ -std=c++14 *.cpp -o flight_project -pthread
```

Download [flight gear](https://www.flightgear.org/), the open source simulator we're working with.

After installation, you'll have to configure flight gear to use our ports; add these lines in *Flight Gear -> Settings -> Additional Settings*:

```
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
--telnet=socket,in,10,127.0.0.1,5402,tcp
```

## Usage

Run our code first:
```bash
./flight_project fly.txt  # arg: code to control the aeroplane
```
Then start flight gear, choose an aeroplane, and hit "Fly" :)

