# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007

import sys
import os

sys.path.append("..")
sys.path.append("../.libs")
sys.path.append("../../src/.libs")

if "BNDEVEL" in os.environ:
    bndev=os.environ["BNDEVEL"]
    sys.path.extend([os.path.join(bndev,x) for x in ["bin", "lib"] ])
    
