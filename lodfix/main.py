import string
import io
import os

class readFile:

    currdir = os.path.dirname(__file__)
    subpath = "Config/graphics.lua"
    file_path = os.path.join(currdir,subpath)
    linenum = 0
    data = []

    def read(self):
        self.Flist = open(self.file_path, "r+")
        self.data = self.Flist.readlines()
        for x in self.data:
            self.linenum = self.linenum+1
            if "around_camera" in x:
                print(self.linenum)
                break
        self.data[self.linenum-1] = "\taround_camera = 100;\n"
        self.data[self.linenum] = "\taround_objects = 1000;\n"
        self.Flist.close()


    def write(self):
        self.Flist = open(self.file_path, "w+")
        self.Flist.writelines(self.data)


f = readFile()
f.read()
f.write()
