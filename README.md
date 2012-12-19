# Radio-Daemon

## General
### About
This is a project made by (or partially by) WSN-Team 2012 in the course CSD, which is part of the [Technology Transfer Alliance](http://ttaportal.org/).

### Purpose
To offer an uplink for wireless sensors in remote areas cut off from the Internet, a good way is to use the white space of radio band and transmit data over radio at an available frequency. A spectrum database (SDB) will be used to restore pairs of timeslot and frequency for the gateway at a specific geolocation to work accordingly.
In the gateway, a linux-based program is supposed to handle SDB-lookingup and radio transmission.

### Description
Radiodaemon is a background process used to establish/destroy radio link and open/close radio interface at specific times, which are acquired by querying spectrum database (SDB). In radiodaemon either of the two alternatives will be called to establish radio link: [radiotunnel](https://github.com/WSN-2012/radiotunnel) and soundmodem.

## Build & Install
### Prerequisites
To run radiodaemon you should have a linux-like OS, Voyage etc. Besides, radiotunnel and soundmodem should be installed in the system. More information on installation and configuration found in Manual for setting up environment for radiodaemon in gateway or base station and Dual-platform configuration in Voyage (available at [http://ttaportal.org/menu/projects/wsn/fall-2012/documents/](http://ttaportal.org/menu/projects/wsn/fall-2012/documents/)).

### Buidling
Follow the below steps to build it.

1.  `git clone https://github.com/WSN-2012/Radio-Daemon.git`
2.  `cd Radio-Daemon`
3.  `make`

## Starting & Stopping
Follow the below steps to start it.

1.  `cd Radio-Daemon`
2.  `./radiodaemon start`

Similiarly, to restart, stop or check the status of the daemon, run
`./radiodaemon stop` `./radiodaemon restart` or `./radiodaemon status`

## License
Copyright 2012 KTH

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
