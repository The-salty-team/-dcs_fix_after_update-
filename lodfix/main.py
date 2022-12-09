import string
import io
import os

class readFile:

    currdir = os.path.dirname(__file__)
    linenum = 0
    data = []

    def read(self,filename):
        file_path = os.path.join(self.currdir, filename)
        self.Flist = open(self.file_path, "r+")
        self.data = self.Flist.readlines()

    def editGraph(self):
        for x in self.data:
            self.linenum = self.linenum+1
            if "around_camera" in x:
                print(self.linenum)
                self.data[self.linenum-1] = "\taround_camera = 0;\n"
                self.data[self.linenum] = "\taround_objects = 0;\n"
            if "lodMult" in x:
                self.data[self.linenum]="\tlodMult = 0.5;\n"
        self.Flist.close()

    def write(self,filename):
        file_path = os.path.join(self.currdir, filename)
        self.Flist = open(self.file_path, "w+")
        self.Flist.writelines(self.data)


f = readFile()
subpath = "Config/graphics.lua"
f.read(subpath)
f.editGraph()
f.write(subpath)

subpath="VrScene.lua"
f.read(subpath)
subpath = "DemoScenes/VrScene.lua"
f.write(subpath)

