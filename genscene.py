from numpy import random
import sys

def main():
    f= open("scenes/%s.sc"% sys.argv[1], "w+")
    
    xres = 1920
    yres = 1080
    objectnumber = int(sys.argv[2])/25
# AA,TR,RE
    f.write("antialiasing&OFF\n")
    f.write("transparencies&0\n")
    f.write("reflections&0\n")
    f.write("architecture&CPU\n")
    f.write("xresolution&%d\n" % xres)
    f.write("yresolution&%d\n" % yres)
    f.write("BVHacceleration&ON\n")
    f.write("eye&1000,500,-2000\n")
    f.write("ambientlight&0.1&1.0,1.0,1.0\n")
    f.write("specular&1\n")
    f.write("scenesize&%d\n" % (int(sys.argv[2])))
    f.write("/& LIGHTS FORMAT TYPE&POSITION&COLOR&Ip\n")
    f.write("light&500,500,-500&1.0,1.0,1.0&0.9\n")
    f.write("/& SPHERE FORMAT TYPE&POSITION&RADIUS&TYPEFILL&COLOR OR URL&KA&KN&KD&KS&FATT&01&02&03\n")
    f.write("/& CYLINDER FORMAT TYPE&POSITION&RADIUS&DIRECTION&D1&D2&TYPEFILL&COLOR OR URL&KA&KN&KD&KS&FATT&01&02&03\n")
    f.write("/& CONE FORMAT TYPE&POSITION&DIRECTION&D1&D2&TYPEFILL&COLOR OR URL&KA&KN&KD&KS&FATT&01&02&03&K1&K2\n")
    f.write("/& DISC FORMAT TYPE&POSITION&RADIUS&DIRECTION&TYPEFILL&COLOR OR URL&KA&KN&KD&KS&FATT&01&02&03\n")
    f.write("/& TRIANGLE Format TYPE&Rotation&Translation&TYPEFILL&COLOR OR URL&KA&KN&KD&KS&FATT&01&02&03&VERTEX/VERTEX/VERTEX\n")
    
    print(objectnumber) 
    
    for i in range(int(objectnumber)):
#SPHERES
        f.write("sphere&%d,%d,%d&%d&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(0, 60),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("sphere&%d,%d,%d&%d&C&%f,%f,%f&1&10&1&1&1&0&1&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(0, 60),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("sphere&%d,%d,%d&%d&C&%f,%f,%f&1&10&1&1&1&0&0&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(0, 60),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("sphere&%d,%d,%d&%d&C&%f,%f,%f&1&10&1&1&1&0.4&0.3&0.3\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(0, 60),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("sphere&%d,%d,%d&%d&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(0, 60),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

#CYL
        f.write("cylinder&%d,%d,%d&%d&%f,%f,%f&-25&25&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(10, 60),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cylinder&%d,%d,%d&%d&%f,%f,%f&-25&25&C&%f,%f,%f&1&10&1&1&1&0&1&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(10, 60),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cylinder&%d,%d,%d&%d&%f,%f,%f&-25&25&C&%f,%f,%f&1&10&1&1&1&0&0&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(10, 60),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cylinder&%d,%d,%d&%d&%f,%f,%f&-25&25&C&%f,%f,%f&1&10&1&1&1&0.4&0.3&0.3\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(10, 60),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cylinder&%d,%d,%d&%d&%f,%f,%f&-25&25&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(10, 60),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))    

#CONE
        f.write("cone&%d,%d,%d&%f,%f,%f&0&50&C&%f,%f,%f&1&10&1&1&1&1&0&0&3&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cone&%d,%d,%d&%f,%f,%f&0&50&C&%f,%f,%f&1&10&1&1&1&0&1&0&3&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cone&%d,%d,%d&%f,%f,%f&0&50&C&%f,%f,%f&1&10&1&1&1&0&0&1&3&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cone&%d,%d,%d&%f,%f,%f&0&50&C&%f,%f,%f&1&10&1&1&1&0.4&0.3&0.3&3&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("cone&%d,%d,%d&%f,%f,%f&0&50&C&%f,%f,%f&1&10&1&1&1&1&0&0&3&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))
  
#DISC
  
        f.write("disc&%d,%d,%d&%d&%f,%f,%f&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(30, 70),random.uniform(-1, 1), random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("disc&%d,%d,%d&%d&%f,%f,%f&C&%f,%f,%f&1&10&1&1&1&0&1&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(30,70),random.uniform(-1, 1), random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("disc&%d,%d,%d&%d&%f,%f,%f&C&%f,%f,%f&1&10&1&1&1&0&0&1\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(30,70),random.uniform(-1, 1), random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("disc&%d,%d,%d&%d&%f,%f,%f&C&%f,%f,%f&1&10&1&1&1&0.4&0.3&0.3\r\n" %(random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(30,70),random.uniform(-1, 1), random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

        f.write("disc&%d,%d,%d&%d&%f,%f,%f&C&%f,%f,%f&1&10&1&1&1&1&0&0\r\n" % (random.uniform(-100, xres),random.uniform(-100, yres),random.uniform(0, 10000),random.uniform(30,70),random.uniform(-1, 1), random.uniform(-1, 1),random.uniform(-1, 1),random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1)))

#TRIANGLE

        tmp1 = random.uniform(0, xres)
        tmp2 = random.uniform(0, yres)
        tmp3 = random.uniform(0, 10000)
        f.write("triangle&0,0,0&0,0,0&C&%f,%f,%f&1&1&1&1&1&1&0&0&%d,%d,%d/%d,%d,%d/%d,%d,%d/0,25,1000\r\n" % (random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1),tmp1,tmp2,tmp3,tmp1+random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50),tmp1-random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50)))

        tmp1 = random.uniform(0, xres)
        tmp2 = random.uniform(0, yres)
        tmp3 = random.uniform(0, 10000)
        f.write("triangle&0,0,0&0,0,0&C&%f,%f,%f&1&1&1&1&1&0&1&0&%d,%d,%d/%d,%d,%d/%d,%d,%d/0,25,1000\r\n" % (random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1),tmp1,tmp2,tmp3,tmp1+random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50),tmp1-random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50)))

        tmp1 = random.uniform(0, xres)
        tmp2 = random.uniform(0, yres)
        tmp3 = random.uniform(0, 10000)
        f.write("triangle&0,0,0&0,0,0&C&%f,%f,%f&1&1&1&0.3&1&0&0&1&%d,%d,%d/%d,%d,%d/%d,%d,%d/0,25,1000\r\n" % (random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1),tmp1,tmp2,tmp3,tmp1+random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50),tmp1-random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50)))

        tmp1 = random.uniform(0, xres)
        tmp2 = random.uniform(0, yres)
        tmp3 = random.uniform(0, 10000)
        f.write("triangle&0,0,0&0,0,0&C&%f,%f,%f&1&1&1&1&1&0.4&0.3&0.3&%d,%d,%d/%d,%d,%d/%d,%d,%d/0,25,1000\r\n" % (random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1),tmp1,tmp2,tmp3,tmp1+random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50),tmp1-random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50)))

        tmp1 = random.uniform(0, xres)
        tmp2 = random.uniform(0, yres)
        tmp3 = random.uniform(0, 10000)
        f.write("triangle&0,0,0&0,0,0&C&%f,%f,%f&1&1&1&1&1&1&0&0&%d,%d,%d/%d,%d,%d/%d,%d,%d/0,25,1000\r\n" % (random.uniform(0, 1),random.uniform(0, 1),random.uniform(0, 1),tmp1,tmp2,tmp3,tmp1+random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50),tmp1-random.uniform(20, 50),tmp2-random.uniform(20, 50),tmp3+random.uniform(20, 50)))

    f.close()


if __name__ == "__main__":

    main()
