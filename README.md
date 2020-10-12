# Flight Project


"Flight Project" interprets code (in a made up language) written to control an open source aeroplane simulator.

Behind the scenes, "Flight Project" operates both a web server and a client; but from the point of the user - their variables simply always match the aeroplane's steering wheels and its different measurements.

Example code in the special language we're interpreting is found the ```./fly.txt``` file

It's a second-year CS project, by Nitsan and Hodaya, students at Bar-Ilan University.


## Installation

Compile our code:
```bash
g++ -std=c++14 *.cpp -o flight_project -pthread
```

Download [flight gear](https://www.flightgear.org/), the open source simulator we're working with.

After installation, configure FlightGear to use its api:
add these lines in *Flight Gear -> Settings -> Additional Settings*:

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

