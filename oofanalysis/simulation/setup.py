# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007

import sys
import os

if "BNDEVEL" in os.environ:
    bndev=os.environ["BNDEVEL"]
    sys.path.extend([os.path.join(bndev,x) for x in ["bin", "lib", "lib/python2.7/site-packages"] ])
    
