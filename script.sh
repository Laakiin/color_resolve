#!/bin/bash
convert IMG* -crop 327x327+150+80 out.jpg && ./Debug/color_resolve >> COLORS_save.csv
