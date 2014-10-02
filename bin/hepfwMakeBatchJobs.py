#!/usr/bin/python

import os
import io
import sys
import math
import subprocess
import argparse
import time
import collections
import tempfile
import json


parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--inputFileList',  help='an integer for the accumulator')
parser.add_argument('--inputConfigFile',help='sum the integers (default: find the max)')

args = parser.parse_args()
print args.accumulate(args.integers)

