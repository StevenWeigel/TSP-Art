#! /usr/bin/env python3
import os
import sys
# ---------------------------------------------------------------------------
# Original images from http://mrl.nyu.edu/~ajsecord/
# -> http://cs.nyu.edu/~ajsecord/npar2002/StipplingOriginals.zip
# ---------------------------------------------------------------------------

cmd = sys.executable

# os.system(cmd + " " + "./stippler.py ../data/flowers.jpg --save \
#            --n_point 20000 --n_iter 50 --pointsize 1.5 1.5 --figsize 6 \
#            --threshold 255 --force --interactive")


# ---------------------------------------------------------------------------
# These example use CC0 images
# ---------------------------------------------------------------------------
# os.system (cmd + " " + "./stippler.py ../data/leafs.jpg --save \
#             --n_point 20000 --n_iter 50 --pointsize 2.0 4.0 --figsize 8 \
#             --threshold 255 --force --interactive")

os.system(cmd + " " + "./stippler.py C:/Projects/Rougier-2017-master/data/leafs.jpg  --save \
          --n_point 10000 --n_iter 1 --pointsize 1.0 1.0 --figsize 10 \
              --force --display")