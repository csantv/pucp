import array
import numpy as np
from PIL import Image
import sys

def read_pgm(pgmf):
    """Return a raster of integers from a PGM as a list of lists."""
    assert pgmf.readline() == b'P5\n'
    #pgmf.readline()
    (width, height) = [int(i) for i in pgmf.readline().split()]
    depth = int(pgmf.readline())
    assert depth <= 255

    raster = []
    for y in range(height):
        row = []
        for y in range(width):
            row.append(ord(pgmf.read(1)))
        raster.append(row)
    return raster, width, height

if __name__ == "__main__":
    if (len(sys.argv) < 2):
        filename = './data/goldhill_gray.pgm'
    else:
        filename = sys.argv[1]

    #img = open(filename,'rb')
    #r, w, h = read_pgm(img)
    #img.close()
    img = Image.open(filename)

    hist, bins = np.histogram(np.array(img), bins=256, range=(0,255))
    h = np.fromfile('hist.raw', dtype='int32', sep="")

    #print(np.min(np.array(img)))
    #print(hist)
    #print(h)
    dist = np.linalg.norm(hist.reshape(256,1) - h.reshape(256,1))
    assert dist == 0.0
