#!/bin/bash 

./main & ./Trame_generators/odomGen & ./Trame_generators/gpsGen & ./Trame_generators/imuGen &./Trame_generators/pidGen &./Trame_generators/qrGen
