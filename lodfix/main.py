import string
import io
import os

class readFile:

    currdir=os.path.dirname(__file__)
    subpath="Config/graphics.lua"
    file_path=os.path.join(currdir,subpath)
    Flist = open("graphics.lua", "r+")
    linenum = 0
    data = []

    def read(self):
        self.data = self.Flist.readlines()
        for x in self.data:
            self.linenum=self.linenum+1
            if "around_camera" in x:
                print(self.linenum)
                break
        self.data[self.linenum-1] ="around_camera = 100;"
        self.data[self.linenum] = "around_objects = 1000;"
        self.Flist.close()




    def write(self,asdf):
        self.Flist=open("graphics.lua", "w")
        self.Flist.writelines(self.data)
    def getId(self):
        return self.TweetData



f = readFile()
f.read()
print(f.data[13])
f.write("asdf")
